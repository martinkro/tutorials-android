#include "elf_hook.h"
#include "elf_def.h"
#include "elf_helper.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include "module.h"

bool hook_export_function(
        const char* module_name,
        const char* function_name,
        void* new_addr,
        void** old_addr)
{
    bool result = false;
    if(module_name == NULL || function_name == NULL || new_addr == NULL)
    {
        return result;
    }

    void* handle = dlopen(module_name, RTLD_NOW);
    if (handle == NULL)
    {
        ERROR_LOG("dlopen %s fail", module_name);
        return result;
    }

    void* addr = dlsym(handle, function_name);
    if (addr == NULL)
    {
        ERROR_LOG("dlsym %s fail", function_name);
        dlclose(handle);
        return result;
    }

    soinfo* si = (soinfo*)handle;
    DEBUG_LOG("[1]image base:%08x", si->base);
    ElfW(Sym)* s = dlsym_handle_lookup(si, function_name);
    if (s != NULL)
    {
        ElfW(Addr) page_start = (ElfW(Addr))PAGE_START((ElfW(Addr))s);
        ElfW(Addr) page_end = (ElfW(Addr))PAGE_END((ElfW(Addr))s);
        size_t len = PAGE_SIZE;
        if ((ElfW(Addr))s + sizeof(s) > page_end)
        {
            len += PAGE_SIZE;
        }

        int prot;
        if (strcmp(module_name, "libdl.so") != 0)
        {
            prot = PROT_READ | PROT_WRITE | PROT_EXEC;
        }
        else
        {
            prot = PROT_READ|PROT_WRITE;
        }

        int i = mprotect((const void*)page_start, len, prot);
        if (i == 0)
        {
            if (old_addr != NULL)
            {
                *(ElfW(Addr)*)old_addr = s->st_value + si->base;
            }
            s->st_value = (ElfW(Addr))(new_addr) - si->base;
            result = true;
        }

    }

    dlclose(handle);

    return result;
}

bool hook_export_function2(
        const char* module_name,
        const char* function_name,
        void* new_addr,
        void** old_addr)
{
    bool result = false;
    uintptr_t image_base = get_image_base(module_name);
    if (image_base == 0)
    {
        return result;
    }

    void* handle = dlopen(module_name, RTLD_NOW);
    if (handle != NULL)
    {
        soinfo* si = (soinfo*)handle;
        DEBUG_LOG("[2]%s image base:%08x", module_name, si->base);
        dlclose(handle);
    }

    DEBUG_LOG("[2]%s image base:%08x", module_name, image_base);

    Elf32_Ehdr* hdr = (Elf32_Ehdr*)image_base;
    Elf32_Off section_offset = hdr->e_shoff;
    Elf32_Half section_number = hdr->e_shnum;
    Elf32_Half section_entry_size = hdr->e_shentsize;
    Elf32_Half section_str_idx = hdr->e_shstrndx;

    DEBUG_LOG("header:%04x,%04x,%08x,%08x,%08x,%08x,flags:%08x,header size:%04x",
            hdr->e_type,
            hdr->e_machine,
            hdr->e_version,
            hdr->e_entry,
            hdr->e_phoff,
            hdr->e_shoff,
            hdr->e_flags,
            hdr->e_ehsize
            );
    DEBUG_LOG("phentsize:%04x,phnum:%d, shentsize:%04x, shnum:%d,shstrndx:%d",
            hdr->e_phentsize,
            hdr->e_phnum,
            hdr->e_shentsize,
            hdr->e_shnum,
            hdr->e_shstrndx
    );

    DEBUG_LOG("%02x,%02x,%02x,%02x %02x",
            hdr->e_ident[EI_MAG0],
            hdr->e_ident[EI_MAG1],
            hdr->e_ident[EI_MAG2],
            hdr->e_ident[EI_MAG3],
            hdr->e_ident[EI_CLASS]
                         );

    DEBUG_LOG("section offset:%d, num:%d, size:%d, str_idx:%d", section_offset, section_number, section_entry_size, section_str_idx);


    Elf32_Shdr* section_header = (Elf32_Shdr*)(image_base + section_offset);
    Elf32_Shdr section_strtab = section_header[section_str_idx];
    Elf32_Half strtab_addr = section_strtab.sh_addr;
    const char* strtab = (const char*)(image_base + strtab_addr);
    DEBUG_LOG("strtab:%p", strtab_addr);
    Elf32_Half section_idx = 0;
    for (section_idx = 0; section_idx < section_number; section_idx++)
    {
        DEBUG_LOG("section name:%d,type:%d,addr:%08x,offset:%08x",
                section_header[section_idx].sh_name,
                section_header[section_idx].sh_type,
                section_header[section_idx].sh_addr,
                section_header[section_idx].sh_offset
                );

        //section_header = (Elf32_Shdr*)((uint8_t*)section_header + section_entry_size);
    }

    /*
     * .shstrtab  sh_type SHT_STRTAB
     */
    return result;
}
