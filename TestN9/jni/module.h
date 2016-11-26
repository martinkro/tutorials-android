#ifndef TEST_MODULE_H
#define TEST_MODULE_H

#include <inttypes.h>
#ifdef __cplusplus
extern "C"{
#endif

uintptr_t get_image_base(const char* module_name);

#ifdef __cplusplus
}
#endif

#endif
