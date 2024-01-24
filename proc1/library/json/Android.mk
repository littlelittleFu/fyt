LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Json_static

LOCAL_MODULE_FILENAME := libJson

LOCAL_SRC_FILES := json_reader.cpp json_value.cpp json_writer.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/json

LOCAL_C_INCLUDES := $(LOCAL_PATH)/json

LOCAL_CPPFLAGS := -fexceptions -DTIXML_USE_STL

include $(BUILD_STATIC_LIBRARY)
