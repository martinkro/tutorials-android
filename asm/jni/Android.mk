LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:=example
LOCAL_SRC_FILES:=example.c
include $(BUILD_SHARED_LIBRARY)