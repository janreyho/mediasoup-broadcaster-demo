cmake_minimum_required(VERSION 3.8)

project(hxSDK LANGUAGES CXX)

if(WIN32)
    add_definitions(-DWEBRTC_WIN)
elseif(APPLE)
    add_definitions(-DWEBRTC_MAC -DWEBRTC_POSIX)
    set(OPENSSL_INCLUDE_DIR "/opt/homebrew/Cellar/openssl@3/3.2.1/include/")
elseif(UNIX)
    add_definitions(-DWEBRTC_POSIX)
    set(OPENSSL_INCLUDE_DIR "/usr/include/openssl")
endif()

# Set version number.
set(hxSDK_VERSION_MAJOR 0)
set(hxSDK_VERSION_MINOR 1)

# C++ standard requirements.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -v -Wall -stdlib=libc++")		# v:显示详细信息  Wall:启用所有编译器警告
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")						# debug开启调试, cmake -DCMAKE_BUILD_TYPE=Debug /path/to/source
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")				# release 

set(LIBWEBRTC_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/")
set(LIBWEBRTC_BINARY_PATH "${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/")
set(CMAKE_USE_OPENSSL ON)

# Add some compile flags to our source files.
set_source_files_properties(${SOURCE_FILES}
	PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic)

# 添加 apple 相关 framework
find_library(APPKIT_FRAMEWORK AppKit)


find_library(VIDEO_TOOLBOX_FRAMEWORK VideoToolbox)
find_library(SECURITY_LIBRARY Security)
find_library(METALKIT_LIBRARY MetalKit)
find_library(METAL_LIBRARY Metal)
find_library(AUDIO_UNIT_LIBRARY AudioUnit)
find_library(QUARTZ_CORE_LIBRARY QuartzCore)
find_library(ICUCORE_LIBRARY icucore)
find_package(OpenGL REQUIRED)

# Extra libs required in order to use Apple media devices.
if(APPLE)
	find_library(APPLICATION_SERVICES ApplicationServices)
	find_library(AUDIO_TOOLBOX AudioToolbox)
	find_library(AV_FOUNDATION AVFoundation)
	find_library(CORE_AUDIO CoreAudio)
	find_library(CORE_FOUNDATION Foundation)
	find_library(CORE_MEDIA CoreMedia)
	find_library(CORE_VIDEO CoreVideo)
	find_library(CORE_SERVICES CoreServices)
endif(APPLE)


file(GLOB WebrtcSDK
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/WebRTC.framework
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideoframebuffer_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideocapture_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideocodec_objc.a
  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libbase_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libnative_api.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libnative_video.a

  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libdefault_codec_factory_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libaom_av1_encoder.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvp8.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvp9.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libfile_logger_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libmediasource_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libdav1d_decoder.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/modules/video_coding/codecs/av1/libdav1d_decoder.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideotoolbox_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideorendereradapter_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideosource_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libwrapped_native_codec_objc.a

  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libhelpers_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libmediaconstraints_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libaudio_device_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libbase_native_additions_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libcallback_logger_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libmedia_constraints.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libobjc_audio_device_module.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvideo_toolbox_cc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libvpx_codec_constants.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libmetal_objc.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/sdk/libpeerconnectionfactory_base_objc.a
  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/rtc_base/liblogging.a
  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/rtc_base/liblog_sinks.a

  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/audio/libaudio.a
  ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/api/librtc_event_log_output_file.a
  # ${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/rtc_base/libfile_rotating_stream.a
)

# 使变量在整个项目中可用
set(WebrtcSDK ${WebrtcSDK} CACHE INTERNAL "List of WebRTC SDK Libraries")

# 链接 WebRTC 库
find_library(WEBRTC_LIB NAMES webrtc PATHS "${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj" NO_DEFAULT_PATH)
file(GLOB RTC_BASE_LIBS "${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/rtc_base/*.a") # 遍历 rtc_base 所有库文件



# Source Dependencies.
add_subdirectory(sdk/libwebrtc "${CMAKE_CURRENT_BINARY_DIR}/libwebrtc")
add_subdirectory(sdk/libmediasoupclient "${CMAKE_CURRENT_BINARY_DIR}/libmediasoupclient")
add_subdirectory(sdk/cpr "${CMAKE_CURRENT_BINARY_DIR}/cpr")


# WebRTC 头文件路径
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/sdk/objc/base/")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/boringssl/")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/libyuv/include/")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/sdk/objc/")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/sdk/objc/base")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/googletest/src/googletest/include")



if(APPLE)
  # 添加 apple 相关 framework
  find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)                                         # 链接 Core Foundation 框架å
  # 添加 apple 相关 framework
  find_library(APPKIT_FRAMEWORK AppKit)
  find_library(VIDEO_TOOLBOX VideoToolbox)
  find_library(AUDIO_TOOLBOX AudioToolbox)
  find_library(SECURITY_LIBRARY Security)
  find_library(METALKIT_LIBRARY MetalKit)
  find_library(METAL_LIBRARY Metal)
  find_library(AUDIO_UNIT_LIBRARY AudioUnit)
  find_library(QUARTZ_CORE_LIBRARY QuartzCore)
  find_library(ICUCORE_LIBRARY icucore)
  find_package(OpenGL REQUIRED)
	find_library(APPLICATION_SERVICES ApplicationServices)

	find_library(AV_FOUNDATION AVFoundation)
	find_library(CORE_AUDIO CoreAudio)
	find_library(CORE_FOUNDATION Foundation)
	find_library(CORE_MEDIA CoreMedia)
	find_library(CORE_VIDEO CoreVideo)
	find_library(CORE_SERVICES CoreServices)

  file(GLOB AppleSDK
    ${CORE_MEDIA_FRAMEWORK} 
    ${APPKIT_FRAMEWORK}
    ${VIDEO_TOOLBOX}
    ${AUDIO_TOOLBOX}
    ${SECURITY_LIBRARY}
    ${METALKIT_LIBRARY} 
    ${METAL_LIBRARY} 
    ${AUDIO_UNIT_LIBRARY}
    ${QUARTZ_CORE_LIBRARY}
    ${ICUCORE_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${APPLICATION_SERVICES}
    ${AV_FOUNDATION}
    ${CORE_AUDIO}
    ${CORE_FOUNDATION}
    ${CORE_MEDIA}
    ${CORE_VIDEO}
    ${CORE_SERVICES}
  )
  set(AppleSDK ${AppleSDK} CACHE INTERNAL "List of WebRTC SDK Libraries")
elseif(UNIX)
    add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/jsoncpp/source ${CMAKE_BINARY_DIR}/jsoncpp_build)
    add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/abseil-cpp ${CMAKE_BINARY_DIR}/abseil_build)

    link_directories("${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++")
    link_directories("${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++abi")
    # 查找 libc++ 和 libc++abi 的对象文件
    include_directories("${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++/libc++")
    include_directories("${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++abi/libc++abi")
    file(GLOB LIBCXX_OBJECTS "${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++/libc++/*.o")
    file(GLOB LIBCXXABI_OBJECTS "${LIBWEBRTC_BINARY_PATH}/buildtools/third_party/libc++abi/libc++abi/*.o")

    message(STATUS "LIBCXX_OBJECTS library: ${LIBCXX_OBJECTS}")
    message(STATUS "LIBCXXABI_OBJECTS library: ${LIBCXXABI_OBJECTS}")
    message(STATUS "LIBWEBRTC_BINARY_PATH library: ${LIBWEBRTC_BINARY_PATH}")
endif()

add_subdirectory(demo/mac)
