LOCAL_PATH := $(call my-dir)


#include $(CLEAR_VARS)
#LOCAL_MODULE:= mono
#LOCAL_SRC_FILES:=lib/$(TARGET_ARCH_ABI)/libmono.so
#include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := TestN9
LOCAL_SRC_FILES := TestN9.cpp elf_hook.c module.c elf_helper.c test.c
LOCAL_LDLIBS:= -llog
#LOCAL_SHARED_LIBRARIES:=mono

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_ARM_NEON := true
LOCAL_MODULE    := mono
LOCAL_SRC_FILES := mono.c arena.c.neon
LOCAL_LDLIBS:= -llog
LOCAL_SHARED_LIBRARIES:=TestN9
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_ARM_NEON := true
LOCAL_MODULE    := unpacker1
LOCAL_SRC_FILES := unpacker.c
LOCAL_LDLIBS:= -llog
LOCAL_SHARED_LIBRARIES:=TestN9
include $(BUILD_SHARED_LIBRARY)
