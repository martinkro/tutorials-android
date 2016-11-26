#include "elf_hook.h"
#include "elf_def.h"
#include "elf_helper.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>

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
    return result;
}
