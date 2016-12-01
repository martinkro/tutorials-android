#include <stdio.h>
#include <android/log.h>

void test_func()
{
    __android_log_print(ANDROID_LOG_DEBUG, "demo1", "test func");
}