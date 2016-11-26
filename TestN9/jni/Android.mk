LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_MODULE    := mono
LOCAL_SRC_FILES := mono.c
LOCAL_LDLIBS:= -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := TestN9
LOCAL_SRC_FILES := TestN9.cpp elf_hook.c module.c elf_helper.c
LOCAL_LDLIBS:= -llog
#LOCAL_SHARED_LIBRARIES:=mono

include $(BUILD_SHARED_LIBRARY)
