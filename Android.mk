LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := menu7bypass
LOCAL_SRC_FILES := native-lib.cpp memory.cpp hooks.cpp
LOCAL_LDLIBS    := -llog -landroid
LOCAL_CPPFLAGS  := -std=c++17 -fPIC
include $(BUILD_SHARED_LIBRARY)
