#ifndef TEST_MONO_H
#define TEST_MONO_H

#include <inttypes.h>

#define MONO_API __attribute__((visibility("default")))

struct _MonoImage
{
    uint32_t size;
};

struct _MonoImageOpenStatus
{
    uint32_t size;
};

struct _MonoAssembly
{
    uint32_t size;
};

typedef struct _MonoImage MonoImage;
typedef struct _MonoImageOpenStatus MonoImageOpenStatus;
typedef struct _MonoAssembly MonoAssembly;

typedef uint32_t guint32;
typedef int gboolean;

typedef MonoImage*(*pfn_mono_image_open_from_data_with_name)(char* data,guint32 data_len,gboolean need_copy,MonoImageOpenStatus* status,gboolean refonly,const char* name);
typedef MonoAssembly* (*pfn_mono_assembly_load_from_full)(MonoImage* image,const char* name,int* status,gboolean refonly);

#ifdef __cplusplus
extern "C"{
#endif

MONO_API MonoImage* mono_image_open_from_data_with_name(
        char* data,
        uint32_t data_len,
        gboolean need_copy,
        MonoImageOpenStatus* status,
        gboolean refonly,
        const char* name);

MONO_API MonoAssembly* mono_assembly_load_from_full(
        MonoImage* image,
        const char* fname,
        int* status,
        gboolean refonly
        );

#ifdef __cplusplus
}
#endif



#endif
