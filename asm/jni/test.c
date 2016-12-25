#include <jni.h>

#if defined(__arm__)
static int my_thumb(int dummy)
{
    __asm__ __volatile__(
        "movw r0,#1001\n"
        "movw r12,#2020\n"
        "add r0,r0,r12\n"
        "bx lr"
    );
    return dummy;
}

int armFunction(int input);
jstring stringFromJNI(JNIEnv* env, jobject thiz)
{
    my_thumb(0);
    armFunction(10);
    return (*env)->NewStringUTF(env,"Hello from JNI!");
}

#endif