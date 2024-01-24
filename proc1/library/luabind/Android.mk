LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := luabind_static

LOCAL_MODULE_FILENAME := libluabind

LOCAL_SRC_FILES := src/class.cpp \
    src/class_info.cpp \
    src/class_registry.cpp \
    src/class_rep.cpp \
    src/create_class.cpp \
    src/error.cpp \
    src/exception_handler.cpp \
    src/function.cpp \
    src/function_introspection.cpp \
    src/inheritance.cpp \
    src/link_compatibility.cpp \
    src/object_rep.cpp \
    src/open.cpp \
    src/operator.cpp \
    src/pcall.cpp \
    src/scope.cpp \
    src/set_package_preload.cpp \
    src/stack_content_by_name.cpp \
    src/weak_ref.cpp \
    src/wrapper_base.cpp

    
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
    	$(LOCAL_PATH)/../boost_inc \
	$(LOCAL_PATH)/../lua                

LOCAL_CPPFLAGS := -frtti -fexceptions


include $(BUILD_STATIC_LIBRARY)
