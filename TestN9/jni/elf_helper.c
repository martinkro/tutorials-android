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
