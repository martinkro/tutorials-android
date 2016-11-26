#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "log.h"
#include "mono.h"
#include "elf_hook.h"


#define JNIREG_CLASS "com/personal/util/Native"

pfn_mono_image_open_from_data_with_name origin_mono_image_open_from_data_with_name = NULL;

MonoImage* my_mono_image_open_from_data_with_name(
        char* data,
        uint32_t data_len,
        gboolean need_copy,
        MonoImageOpenStatus* status,
        gboolean refonly,
        const char* name)
{
    DEBUG_LOG("my mono image open from data with name ...");
    if (origin_mono_image_open_from_data_with_name != NULL)
    {
        return origin_mono_image_open_from_data_with_name(data, data_len,need_copy,status,refonly,name);
    }

    return NULL;
}

void call_test()
{
    void* handle = dlopen("libmono.so", RTLD_NOW);
    if (handle)
    {
        void* addr = dlsym(handle, "mono_image_open_from_data_with_name");
        DEBUG_LOG("function addr:%p:%p", handle,addr);
        pfn_mono_image_open_from_data_with_name pfn = (pfn_mono_image_open_from_data_with_name)addr;
        pfn(NULL,0,0,0,0,0);
        dlclose(handle);
    }
}

void test_dlopen(JNIEnv* env, jclass clazz)
{
    DEBUG_LOG("test dlopen");
    call_test();

    bool ret = hook_export_function("libmono.so",
            "mono_image_open_from_data_with_name",
            (void*)my_mono_image_open_from_data_with_name,
            (void**)&origin_mono_image_open_from_data_with_name
    );

    DEBUG_LOG("hook %s", ret?"success":"fail");

    // mono_image_open_from_data_with_name(NULL,0,0,0,0,0);
    call_test();

}

static JNINativeMethod g_native_methods[] = {
        {"testDlopen", "()V", (void*)test_dlopen}
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) == JNI_OK)
    {
        jclass clazz = env->FindClass(JNIREG_CLASS);
        if (clazz != NULL)
        {
            if (env->RegisterNatives(clazz, g_native_methods,sizeof(g_native_methods)/sizeof(g_native_methods[0])) >= 0)
            {
                DEBUG_LOG("register native methos success.");
            }
            else
            {
                ERROR_LOG("register native methos fail.");
            }
        }
    }
    return JNI_VERSION_1_4;
}
