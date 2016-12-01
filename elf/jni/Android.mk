LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello
LOCAL_SRC_FILES := hello.c
#LOCAL_LDLIBS:= -llog
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_MODULE    := demo1
LOCAL_SRC_FILES := demo1.c
LOCAL_LDLIBS:= -llog
include $(BUILD_SHARED_LIBRARY)