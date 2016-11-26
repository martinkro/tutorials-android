#ifndef TEST_ELF_HOOK_H
#define TEST_ELF_HOOK_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

bool hook_export_function(
        const char* module_name,
        const char* function_name,
        void* new_addr,
        void** old_addr);

bool hook_export_function2(
        const char* module_name,
        const char* function_name,
        void* new_addr,
        void** old_addr);

#ifdef __cplusplus
}
#endif

#endif
