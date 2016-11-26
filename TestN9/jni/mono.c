#include "mono.h"
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

MONO_API MonoImage* mono_image_open_from_data_with_name(
        char* data,
        uint32_t data_len,
        gboolean need_copy,
        MonoImageOpenStatus* status,
        gboolean refonly,
        const char* name)
{
    DEBUG_LOG("mono_image_open_from_data_with_name ...");
    return NULL;
}

MONO_API MonoAssembly* mono_assembly_load_from_full(
        MonoImage* image,
        const char* fname,
        int* status,
        gboolean refonly
        )
{
    DEBUG_LOG("mono_assembly_load_from_full ...");
    return NULL;
}




