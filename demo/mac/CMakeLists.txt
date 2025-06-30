cmake_minimum_required(VERSION 3.8)

project(macDemo LANGUAGES CXX)
message(STATUS "demo/mac")

if(WIN32)
elseif(APPLE)
elseif(UNIX)

	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GLIB REQUIRED glib-2.0)
	include_directories(${GLIB_INCLUDE_DIRS})
	link_directories(${GLIB_LIBRARY_DIRS})

	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
	include_directories(${GTK3_INCLUDE_DIRS})
	link_directories(${GTK3_LIBRARY_DIRS})

	include_directories(${hxrtc_src}/third_party/jsoncpp/source/include/)
	include_directories(${hxrtc_src}/out/mac/gen)
	set(SOURCE_FILES
		${hxrtc_src}/test/linux/video_renderer_linux.cc
		${hxrtc_src}/test/linux/glx_renderer.cc
		${hxrtc_src}/test/run_test.cc
	    ${hxrtc_src}/rtc_base/synchronization/sequence_checker_internal.cc
	)
endif()


# Create target.
add_executable(${PROJECT_NAME}
	src/Broadcaster.cpp
	src/main.cpp
	src/MediaStreamTrackFactory.cpp
	${SOURCE_FILES}
	# ${LIBCXX_SOURCES}
)


# Private (implementation) header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
# Public (interface) headers from dependencies.
target_include_directories(${PROJECT_NAME} PUBLIC
	${mediasoupclient_SOURCE_DIR}/include
	${cpr_SOURCE_DIR}/include
	"${PROJECT_SOURCE_DIR}/sdk/libwebrtc"
	"${PROJECT_SOURCE_DIR}/thirdparty/hxrtc/src/sdk/objc/base/"
)

set(system_libs)
if(WIN32)
    list(APPEND system_libs
        msvcprt.lib
        winmm.lib
        ws2_32.lib
        secur32.lib
        crypt32.lib
        crypt32.lib
        iphlpapi.lib
    )
elseif(APPLE)
	list(APPEND system_libs
		${AppleSDK}
	)
elseif(UNIX)
	find_package(OpenSSL REQUIRED)
	list(APPEND system_libs
		# ${CMAKE_BINARY_DIR}/webrtc/obj/third_party/abseil-cpp/absl/strings/string_view/string_view.o
		# ${CMAKE_BINARY_DIR}/webrtc/obj/api/librtp_parameters.a
		# -lc++				# 不是 -lstdc++， 原因：链接 libc++，而不是 libstdc++：
		# -lc++abi
		# -lssl
		# -lcrypto
		${CMAKE_BINARY_DIR}/lib/libjsoncpp-d.a
		# /usr/lib/llvm-10/lib/libc++.a
		# /usr/lib/llvm-10/lib/libc++abi.a
		-lGL         # OpenGL 库
		-lX11        # X11 库（GLX 依赖 X11）
		${CMAKE_DL_LIBS}  # 自动链接 libdl
		${GLIB_LIBRARIES}
		${GTK3_LIBRARIES}
		# ${hxrtc_obj}/stats/librtc_stats.a  # 不生效?
		resolv
		# pthread
		-lpthread
		# ${hxrtc_obj}/rtc_base/libthreading.a
		cpr
	)
endif()

target_link_libraries(${PROJECT_NAME}
	${WebrtcSDK}
	${RTC_BASE_LIBS}
	${WEBRTC_LIB}
	cpr
	mediasoupclient
	webrtc_broadcaster
	# ${libhxprotocol}
	# ${libhxprotocol_libz}
	${system_libs}
)


if(WIN32)
elseif(APPLE)
elseif(UNIX)
	# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition") 
	target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated-declarations)
	set_target_properties(${PROJECT_NAME} PROPERTIES TESTONLY TRUE)
endif()