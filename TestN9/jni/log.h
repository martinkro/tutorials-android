#ifndef TEST_LOG_H
#define TEST_LOG_H

#include <android/log.h>

#define DEBUG_LOG(...) __android_log_print(ANDROID_LOG_DEBUG, "testn9", __VA_ARGS__)
#define ERROR_LOG(...) __android_log_print(ANDROID_LOG_DEBUG, "testn9", __VA_ARGS__)

#endif
