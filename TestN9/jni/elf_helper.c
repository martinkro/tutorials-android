#include "elf_helper.h"
#include "log.h"

#include <string.h>

ElfW(Sym)* dlsym_handle_lookup(soinfo* si, const char* name)
{
    ElfW(Sym)* symtab = si->symtab;
    const char* strtab = si->strtab;

    DEBUG_LOG("symtab addr:%p", symtab);
    DEBUG_LOG("strtab addr:%p", strtab);

    unsigned int i;
    for (i = 0; i < si->nbucket; i++)
    {
        unsigned int n = 0;
        for (n = si->bucket[i]; n != 0; n = si->chain[n])
        {
            ElfW(Sym)* s = symtab + n;
            if (strcmp(strtab + s->st_name, name)) continue;
            switch(ELF_ST_BIND(s->st_info)){
            case STB_GLOBAL:
            case STB_WEAK:
                if (s->st_shndx == SHN_UNDEF){
                    continue;
                }
                return s;
            }
        }
    }

    return NULL;
}

void phdr_table_get_dynamic_section(const Elf32_Phdr* phdr_table,
        int phdr_count,
        Elf32_Addr load_bias,
        Elf32_Dyn** dynamic,
        size_t* dynamic_count,
        Elf32_Word* dynamic_flags)
{
    const Elf32_Phdr* phdr = phdr_table;
    const Elf32_Phdr* phdr_limit = phdr + phdr_count;
    for (phdr = phdr_table; phdr < phdr_limit; phdr++)
    {
        if (phdr->p_type != PT_DYNAMIC){
            continue;
        }
        *dynamic = (Elf32_Dyn*)(load_bias + phdr->p_vaddr);
        if (dynamic_count)
        {
            *dynamic_count = (unsigned)(phdr->p_memsz / 8);
        }
        if (dynamic_flags){
            *dynamic_flags = phdr->p_flags;
        }
        return;
    }
    *dynamic = NULL;
    if (dynamic_count)
    {
        *dynamic_count = 0;
    }
}
