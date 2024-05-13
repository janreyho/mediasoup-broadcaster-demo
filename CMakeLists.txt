cmake_minimum_required(VERSION 3.8)

project(broadcaster LANGUAGES CXX)

if(WIN32)
    add_definitions(-DWEBRTC_WIN)
elseif(APPLE)
    add_definitions(-DWEBRTC_MAC -DWEBRTC_POSIX)
elseif(UNIX)
    add_definitions(-DWEBRTC_POSIX)
endif()

# Set version number.
set(broadcaster_VERSION_MAJOR 0)
set(broadcaster_VERSION_MINOR 1)

# C++ standard requirements.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -v -Wall -stdlib=libc++")		# v:显示详细信息  Wall:启用所有编译器警告
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")						# debug开启调试, cmake -DCMAKE_BUILD_TYPE=Debug /path/to/source
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")				# release 

message("\n=========== mediasoup-broadcaster-demo Build Configuration ===========\n")
message(STATUS "LIBWEBRTC_INCLUDE_PATH : " ${LIBWEBRTC_INCLUDE_PATH})
message(STATUS "LIBWEBRTC_BINARY_PATH  : " ${LIBWEBRTC_BINARY_PATH})
message(STATUS "OPENSSL_INCLUDE_DIR    : " ${OPENSSL_INCLUDE_DIR})
message(STATUS "CMAKE_USE_OPENSSL      : " ${CMAKE_USE_OPENSSL})
message("")

# Add some compile flags to our source files.
set_source_files_properties(${SOURCE_FILES}
	PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic)

# Create target.
add_executable(${PROJECT_NAME} ${SOURCES})

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

	target_link_libraries(${PROJECT_NAME} PUBLIC
		${APPLICATION_SERVICES}
		${AUDIO_TOOLBOX}
		${AV_FOUNDATION}
		${CORE_AUDIO}
		${CORE_FOUNDATION}
		${CORE_MEDIA}
		${CORE_VIDEO}
		${CORE_SERVICES}

		${APPKIT_FRAMEWORK} 
		${CORE_MEDIA_FRAMEWORK} 
		${VIDEO_TOOLBOX_FRAMEWORK}
		${QUARTZ_CORE_LIBRARY}
		${ICUCORE_LIBRARY}
		${METAL_LIBRARY} 
		${METALKIT_LIBRARY} 
		${SECURITY_LIBRARY}
		${AUDIO_UNIT_LIBRARY}
		${OPENGL_LIBRARIES}

	)
endif(APPLE)

include(FetchContent)

# message(STATUS "\nFetching mediasoupclient...\n")
# FetchContent_Declare(
#   mediasoupclient
#   GIT_REPOSITORY git@github.com:janreyho/libmediasoupclient.git
#   GIT_TAG m120
# )
# FetchContent_MakeAvailable(mediasoupclient)

# message(STATUS "Fetching cpr...\n")
# FetchContent_Declare(
# 	cpr
# 	GIT_REPOSITORY https://github.com/whoshuu/cpr
# 	GIT_TAG 1.4.0
# )
# FetchContent_MakeAvailable(cpr)

file(GLOB WebrtcSDK
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/WebRTC.framework
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideoframebuffer_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideocapture_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideocodec_objc.a
  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libbase_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libnative_api.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libnative_video.a

  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libdefault_codec_factory_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libaom_av1_encoder.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvp8.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvp9.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libfile_logger_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libmediasource_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libdav1d_decoder.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/modules/video_coding/codecs/av1/libdav1d_decoder.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideotoolbox_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideorendereradapter_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideosource_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libwrapped_native_codec_objc.a

  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libhelpers_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libmediaconstraints_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libaudio_device_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libbase_native_additions_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libcallback_logger_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libmedia_constraints.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libobjc_audio_device_module.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvideo_toolbox_cc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libvpx_codec_constants.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libmetal_objc.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/sdk/libpeerconnectionfactory_base_objc.a
  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/rtc_base/liblogging.a
  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/rtc_base/liblog_sinks.a

  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/audio/libaudio.a
  /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/api/librtc_event_log_output_file.a
  # /Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/rtc_base/libfile_rotating_stream.a
)

# 使变量在整个项目中可用
set(WebrtcSDK ${WebrtcSDK} CACHE INTERNAL "List of WebRTC SDK Libraries")

# 链接 WebRTC 库
find_library(WEBRTC_LIB NAMES webrtc PATHS "/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj" NO_DEFAULT_PATH)
file(GLOB RTC_BASE_LIBS "/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/out/mac/obj/rtc_base/*.a") # 遍历 rtc_base 所有库文件

target_sources(${PROJECT_NAME} PRIVATE
	src/Broadcaster.cpp
	src/main.cpp
	src/MediaStreamTrackFactory.cpp
)

# Private (implementation) header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Source Dependencies.
add_subdirectory(deps/libwebrtc "${CMAKE_CURRENT_BINARY_DIR}/libwebrtc")
add_subdirectory(deps/libmediasoupclient "${CMAKE_CURRENT_BINARY_DIR}/libmediasoupclient")
add_subdirectory(deps/cpr "${CMAKE_CURRENT_BINARY_DIR}/cpr")

# Public (interface) headers from dependencies.
target_include_directories(${PROJECT_NAME} PUBLIC
	${mediasoupclient_SOURCE_DIR}/include
	${cpr_SOURCE_DIR}/include
	"${PROJECT_SOURCE_DIR}/deps/libwebrtc"
	"/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/sdk/objc/base/"
)

# WebRTC 头文件路径
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/sdk/objc/base/")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/third_party/boringssl/")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/third_party/libyuv/include/")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/sdk/objc/")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/sdk/objc/base")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/")
include_directories("/Users/hejiayi/Desktop/8_haoxinyun/gitlab/hxrtc/hxrtc/src/third_party/googletest/src/googletest/include")
# Public (interface) dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC
	${LIBWEBRTC_BINARY_PATH}/libwebrtc${CMAKE_STATIC_LIBRARY_SUFFIX}
	${WebrtcSDK}

	${RTC_BASE_LIBS}
	${WEBRTC_LIB}
	cpr
	mediasoupclient
	webrtc_broadcaster
)

