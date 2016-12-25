LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:=example
LOCAL_SRC_FILES:=example.c.arm test.c arm.c.arm 

ifneq (,$(filter armeabi armeabi-v7a,$(TARGET_ARCH_ABI)))
LOCAL_SRC_FILES += multiple.S
endif

#TARGET_CFLAGS:= -mthumb-interwork

#LOCAL_CFLAGS := -D__cplusplus -g -mfloat-abi=softfp -mfpu=neon -march=armv7a-a -mtune=cortex-a8

#TARGET_ARCH_ABI:=armeabi-v7a
#LOCAL_ARM_NEON := arm

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
#LOCAL_ARM_NEON: =true
endif

include $(BUILD_SHARED_LIBRARY)