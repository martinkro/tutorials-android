#ifndef TEST_ELF_HELPER_H
#define TEST_ELF_HELPER_H

#include <unistd.h>
#include <sys/types.h>
#include <elf.h>

#undef PAGE_SHIFT
#undef PAGE_SIZE
#undef PAGE_MASK

#define PAGE_SHIFT 12
#define PAGE_SIZE (1UL << PAGE_SHIFT)    /* 4K 4096 */
#define PAGE_MASK (~(PAGE_SIZE-1))



#define PAGE_START(x)  ((x) & PAGE_MASK)
#define PAGE_OFFSET(x) ((x) & ~PAGE_MASK)
#define PAGE_END(x)    PAGE_START((x) + (PAGE_SIZE-1))

#if defined(__LP64__)
#define ElfW(what) Elf64_##what
#define ELFW(what) ELF64_##what
#else
//#define ElfW(what) Elf32_##what
//#define ELFW(what) ELF32_##what
#define ELFT(type) Elf32_##type
#define ElfW(type) Elf32_ ## type
#endif

// Android uses RELA for aarch64 and x86_64. mips64 still uses REL.
#if defined(__aarch64__) || defined(__x86_64__)
#define USE_RELA 1
#endif

#define SOINFO_NAME_LEN 128

struct _soinfo;
typedef struct _soinfo soinfo;

ElfW(Sym)* dlsym_handle_lookup(soinfo* si, const char* name);

void phdr_table_get_dynamic_section(const Elf32_Phdr* phdr_table,
        int phdr_count,
        Elf32_Addr load_bias,
        Elf32_Dyn** dynamic,
        size_t* dynamic_count,
        Elf32_Word* dynamic_flags);

struct _soinfo
{
    char name[SOINFO_NAME_LEN];
    const ElfW(Phdr)* phdr;
    size_t phnum;
    ElfW(Addr) entry;
    ElfW(Addr) base;
    size_t size;

    #ifndef __LP64__
    uint32_t unused1;  // DO NOT USE, maintained for compatibility.
    #endif

    ElfW(Dyn)* dynamic;

    #ifndef __LP64__
    uint32_t unused2; // DO NOT USE, maintained for compatibility
    uint32_t unused3; // DO NOT USE, maintained for compatibility
    #endif

    soinfo* next;
    unsigned flags;

    const char* strtab;
    ElfW(Sym)* symtab;

    size_t nbucket;
    size_t nchain;
    unsigned* bucket;
    unsigned* chain;

    /* 分界点，只有上面几个数据结构符合安卓源码的定义*/
    unsigned* placeholder;
};


#ifndef DT_INIT_ARRAY
#define DT_INIT_ARRAY      25
#endif

#ifndef DT_FINI_ARRAY
#define DT_FINI_ARRAY      26
#endif

#ifndef DT_INIT_ARRAYSZ
#define DT_INIT_ARRAYSZ    27
#endif

#ifndef DT_FINI_ARRAYSZ
#define DT_FINI_ARRAYSZ    28
#endif

#ifndef DT_PREINIT_ARRAY
#define DT_PREINIT_ARRAY   32
#endif

#ifndef DT_PREINIT_ARRAYSZ
#define DT_PREINIT_ARRAYSZ 33
#endif

#endif
