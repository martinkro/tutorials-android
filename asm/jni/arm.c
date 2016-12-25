#include <jni.h>

#if defined(__arm__)
/*
static int my_arm(int dummy)
{
    __asm__ __volatile__(
        "movw r0,#1001\n"
        "movw r12,#2020\n"
        "add r0,r0,r12\n"
        "vdup.32 q0,r0\n"
        "bx lr"
    );
    return dummy;
}

jstring stringTest(JNIEnv* env, jobject thiz)
{
    my_arm(0);
    return (*env)->NewStringUTF(env, "Hello");
}
*/
#endif

jstring getABI(JNIEnv* env, jobject thiz)
{
    #if defined(__arm__)
        #if defined(__ARM_ARCH_7A__)
            #if defined(__ARM_NEON__)
                #if defined(__ARM_PCS_VFP)
                    #define ABI "armeabi-v7a/neon(hard-float)"
                #else
                    #define ABI "armeabi-v7a/neon"
                #endif
            #else
                #if defined(__ARM_PCS_VFP)
                    #define ABI "armeabi-v7a(hard-float)"
                #else
                    #define ABI "armeabi-v7a"
                #endif
            #endif
        #else
            #define ABI "armeabi"
        #endif
    #elif defined(__i386__)
        #define ABI "x86"
    #elif defined(__x86_64__)
        #define ABI "x86_64"
    #elif defined(__mips64)
        #define ABI "mips64"
    #elif defined(__mips__)
        #define ABI "mips"
    #elif defined(__aarch64__)
        #define ABI "arm64-v8a"
    #else
        #define ABI "unknown"
    #endif
    return (*env)->NewStringUTF(env, "Hell "ABI".");
}