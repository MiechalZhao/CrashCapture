ROOT_PATH := $(call my-dir)
include $(ROOT_PATH)/breakpad/Android.mk

LOCAL_PATH := $(ROOT_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE    := crashcapture
LOCAL_SRC_FILES := native_crash_capture.cpp
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES += breakpad_client

include $(BUILD_SHARED_LIBRARY)