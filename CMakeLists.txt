cmake_minimum_required(VERSION 3.8)

project(hxSDK LANGUAGES CXX)

set(hxrtc_src ${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src)
set(hxrtc_obj ${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj)

if(WIN32)
    add_definitions(-DWEBRTC_WIN)
elseif(APPLE)
    add_definitions(-DWEBRTC_MAC -DWEBRTC_POSIX)
    set(OPENSSL_INCLUDE_DIR "/opt/homebrew/Cellar/openssl@3/3.2.1/include/")
elseif(UNIX)
    add_definitions(-DWEBRTC_POSIX)
    set(OPENSSL_INCLUDE_DIR "/usr/include/openssl")
endif()

if(WIN32)
    set(lib_obj ".obj")
    set(lib_lib ".lib")
    set(lib_webrtc "webrtc.lib")
    set(GN_COMMAND "--ide=vs2022 --args=\"${gn_args}\"")
else()
    set(lib_obj ".o")
    set(lib_lib ".a")
    set(lib_webrtc "libwebrtc.a")
    # set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE PATH "WebRTC clang" FORCE)
    # set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE PATH "WebRTC clang++" FORCE)
 
    # set(CMAKE_C_COMPILER "${hxrtc_src}/third_party/llvm-build/Release+Asserts/bin/clang" CACHE PATH "WebRTC clang" FORCE)
    # set(CMAKE_CXX_COMPILER "${hxrtc_src}/third_party/llvm-build/Release+Asserts/bin/clang++" CACHE PATH "WebRTC clang++" FORCE)
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    # set(GN_COMMAND "--args=\"${gn_args}\"")
    # set(OPENGL_gl_LIBRARY "/usr/lib/x86_64-linux-gnu/libGL.so")
    # set(OPENGL_glx_LIBRARY "/usr/lib/x86_64-linux-gnu/libGLX.so")
    # 关闭相对路径优化
    # target_compile_options(your_target PRIVATE -fno-dwarf2-cfi-asm -fno-debug-types-section)
    # # 关闭 Split DWARF（若无需优化）
    # set(CMAKE_DEBUG_SPLIT OFF)  # 或 set(USE_DEBUG_FISSION FALSE)

    # set(LIBCXX_SOURCE_DIR "${hxrtc_src}/third_party/libc++/src")
    # set(LIBCXX_BINARY_DIR "${hxrtc_obj}/buildtools/third_party/libc++/libc++")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fno-lto")   # 禁用 DWO 调试信息优化
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-lto")
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

# 生成一个查找库的脚本
file(WRITE ${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs1.cmake "
    # find_library(WEBRTC_LIB NAMES webrtc PATHS "${hxrtc_obj}" NO_DEFAULT_PATH)
    file(GLOB WEBRTC_LIB \"${hxrtc_obj}/${lib_webrtc}\")
    if(WEBRTC_LIB)
        message(STATUS \"Found WEBRTC_LIB library: ${WEBRTC_LIB}\")
    endif()

    file(GLOB BORINGSSL_LIB \"${hxrtc_obj}/third_party/boringssl/libboringssl${lib_lib}\")
    if(BORINGSSL_LIB)
        message(STATUS \"Found BORINGSSL_LIB library: ${BORINGSSL_LIB}\")
    endif()
")

# 创建一个 CMake 脚本，用于查找已编译的库
file(WRITE ${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs2.cmake "
    file(GLOB RTC_BASE_LIBS \"${hxrtc_obj}/rtc_base/*${lib_lib}\")
    if(RTC_BASE_LIBS)
        message(STATUS \"RTC_BASE_LIBS library: \${RTC_BASE_LIBS}\")
        set(RTC_BASE_LIBS \${RTC_BASE_LIBS} PARENT_SCOPE)
    endif()

    file(GLOB WebrtcSDK
    \"${hxrtc_obj}/sdk/libvideoframebuffer_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideocapture_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideocodec_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libnative_api${lib_lib}\"
    \"${hxrtc_obj}/sdk/libnative_video${lib_lib}\"
    \"${hxrtc_obj}/sdk/libdefault_codec_factory_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libaom_av1_encoder${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvp8${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvp9${lib_lib}\"
    \"${hxrtc_obj}/sdk/libfile_logger_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libmediasource_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libdav1d_decoder${lib_lib}\"
    \"${hxrtc_obj}/modules/video_coding/codecs/av1/libdav1d_decoder${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideotoolbox_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideorendereradapter_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideosource_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libwrapped_native_codec_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libmediaconstraints_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libaudio_device_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libbase_native_additions_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libcallback_logger_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libmedia_constraints${lib_lib}\"
    \"${hxrtc_obj}/sdk/libobjc_audio_device_module${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvideo_toolbox_cc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libvpx_codec_constants${lib_lib}\"
    \"${hxrtc_obj}/sdk/libmetal_objc${lib_lib}\"
    \"${hxrtc_obj}/sdk/libpeerconnectionfactory_base_objc${lib_lib}\"
    \"${hxrtc_obj}/api/librtc_event_log_output_file${lib_lib}\"
    )
    # 使变量在整个项目中可用
    if(WebrtcSDK)
        set(WebrtcSDK \${WebrtcSDK} CACHE INTERNAL \"List of WebRTC SDK Libraries\")
    endif()
  ")
# 添加一个目标来执行查找库文件的脚本
add_custom_target(
    find_webrtc_libs2 ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs2.cmake
    # DEPENDS build_webrtc
    COMMENT "Finding WebRTC libraries"
)
add_custom_target(
    find_webrtc_libs1 ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs1.cmake
    # DEPENDS build_webrtc
    COMMENT "Finding WebRTC libraries"
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
    # add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/libc++/src ${CMAKE_BINARY_DIR}/libc++)
    # add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/third_party/libc++abi/src ${CMAKE_BINARY_DIR}/libc++abi)

    # link_directories("${hxrtc_obj}/buildtools/third_party/libc++")
    # link_directories("${hxrtc_obj}/buildtools/third_party/libc++abi")
    # # 查找 libc++ 和 libc++abi 的对象文件
    # include_directories("${hxrtc_src}/buildtools/third_party/libc++/libc++")
    # include_directories("${hxrtc_src}/buildtools/third_party/libc++abi/libc++abi")
    file(GLOB LIBCXX_OBJECTS
        "${hxrtc_obj}/buildtools/third_party/libc++/libc++/*.o"
        "${hxrtc_obj}/buildtools/third_party/libc++/libc++/*.dwo"
    )
    file(GLOB LIBCXXABI_OBJECTS "${hxrtc_obj}/buildtools/third_party/libc++abi/libc++abi/*.o")

    message(STATUS "LIBCXX_OBJECTS library: ${LIBCXX_OBJECTS}")
    message(STATUS "LIBCXXABI_OBJECTS library: ${LIBCXXABI_OBJECTS}")
    message(STATUS "LIBWEBRTC_BINARY_PATH library: ${LIBWEBRTC_BINARY_PATH}")
endif()

add_subdirectory(demo/mac)
