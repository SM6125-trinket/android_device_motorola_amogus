LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libgbp_shim.cpp
LOCAL_SHARED_LIBRARIES := libgui_vendor libutils
LOCAL_MODULE := libgbp_shim
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := both
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libcamera_shim.cpp
LOCAL_MODULE := libcamera_shim
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := both
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libsensors_shim.cpp
LOCAL_HEADER_LIBRARIES := libutils_headers
LOCAL_MODULE := libsensors_shim
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := both
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := libtime_genoff.c
LOCAL_MODULE := libtime_genoff
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := both
include $(BUILD_SHARED_LIBRARY)
