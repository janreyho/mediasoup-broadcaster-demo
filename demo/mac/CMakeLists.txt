cmake_minimum_required(VERSION 3.8)

project(macDemo LANGUAGES CXX)
message(STATUS "demo/mac")

# Create target.
add_executable(${PROJECT_NAME}
	src/Broadcaster.cpp
	src/main.cpp
	src/MediaStreamTrackFactory.cpp
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
	# find_package(absl REQUIRED)
	# list(APPEND system_libs
	# 	OpenSSL::SSL
	# 	OpenSSL::Crypto
	# 	absl::strings
	# 	absl::string_view
	# 	absl::base
	# 	absl::flags           # 注释，则报 很多 找不到 absl::flags_internal
	# 	absl::flags_parse     # absl 和 WEBRTC_LIB 都打开，则报 重复定义 absl::raw_log_internal
	# 	# ${CMAKE_BINARY_DIR}/webrtc/obj/third_party/abseil-cpp/absl/strings/string_view/string_view.o
	# 	${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src/out/mac/obj/api/librtp_parameters.a
	# )

	list(APPEND system_libs
		# ${CMAKE_BINARY_DIR}/webrtc/obj/third_party/boringssl/libboringssl.a
		# ${CMAKE_SOURCE_DIR}/sdk/hxProtocol/third_party/openssl/prebuild/linux/x86_64/libcrypto.a
		# ${CMAKE_SOURCE_DIR}/sdk/hxProtocol/third_party/openssl/prebuild/linux/x86_64/libssl.a
		absl::strings
		# absl::string_view
		absl::base
		absl::flags           # 注释，则报 很多 找不到 absl::flags_internal
		absl::flags_parse     # absl 和 WEBRTC_LIB 都打开，则报 重复定义 absl::raw_log_internal
		# ${CMAKE_BINARY_DIR}/webrtc/obj/third_party/abseil-cpp/absl/strings/string_view/string_view.o
		# eXosip2
		# osip2
		# osipparser2
		${OSIP2_LIB} 
		${EXOSIP2_LIB}
		${OSIPPARSER2_LIB}
		# ${CMAKE_BINARY_DIR}/webrtc/obj/api/librtp_parameters.a
		# -lc++				# 不是 -lstdc++， 原因：链接 libc++，而不是 libstdc++：
		# -lc++abi
		-lssl
		-lcrypto
		${CMAKE_BINARY_DIR}/lib/libjsoncpp-d.a
		-lGL         # OpenGL 库
		-lX11        # X11 库（GLX 依赖 X11）
		${GLIB_LIBRARIES}
		${GTK3_LIBRARIES}
		resolv
		pthread
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
	${LIBCXX_OBJECTS} 
  	${LIBCXXABI_OBJECTS}
	${system_libs}
)

if(WIN32)
elseif(APPLE)
elseif(UNIX)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition") 
	target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated-declarations)
	set_target_properties(${PROJECT_NAME} PROPERTIES TESTONLY TRUE)
endif()