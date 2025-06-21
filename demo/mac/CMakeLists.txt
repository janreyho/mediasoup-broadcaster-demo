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

	include_directories(${hxrtc_src}/third_party/abseil-cpp)
	include_directories(${hxrtc_src}/third_party/jsoncpp/source/include/)
	include_directories(${hxrtc_src}/out/mac/gen)
	set(SOURCE_FILES
		${hxrtc_src}/rtc_base/thread.cc
		${hxrtc_src}/rtc_base/log_sinks.cc
		${hxrtc_src}/rtc_base/file_rotating_stream.cc
		${hxrtc_src}/rtc_base/logging.cc
		${hxrtc_src}/rtc_base/system/file_wrapper.cc
		${hxrtc_src}/rtc_base/network/received_packet.cc
		${hxrtc_src}/test/linux/video_renderer_linux.cc
		${hxrtc_src}/test/linux/glx_renderer.cc
		${hxrtc_src}/test/run_test.cc
		${hxrtc_src}/stats/rtc_stats_report.cc
		${hxrtc_src}/stats/rtc_stats.cc
		${hxrtc_src}/common_video/video_frame_buffer.cc
		${hxrtc_src}/rtc_base/task_queue.cc
		${hxrtc_src}/api/units/time_delta.cc

		${hxrtc_src}/api/rtp_parameters.cc
	    ${hxrtc_src}/api/jsep.cc
		${hxrtc_src}/pc/jsep_session_description.cc
	
		${hxrtc_src}/rtc_base/string_encode.cc
	    ${hxrtc_src}/rtc_base/strings/json.cc
	    ${hxrtc_src}/api/video_codecs/sdp_video_format.cc
	    ${hxrtc_src}/modules/video_coding/svc/scalability_mode_util.cc
	    ${hxrtc_src}/api/video_codecs/av1_profile.cc
	    ${hxrtc_src}/api/video_codecs/vp9_profile.cc
	    ${hxrtc_src}/api/video_codecs/h264_profile_level_id.cc
	    ${hxrtc_src}/api/video_codecs/video_codec.cc
	    ${hxrtc_src}/rtc_base/string_to_number.cc
	    ${hxrtc_src}/rtc_base/socket_address.cc
	    ${hxrtc_src}/rtc_base/strings/string_builder.cc
	    ${hxrtc_src}/rtc_base/ip_address.cc
	    ${hxrtc_src}/rtc_base/string_utils.cc
	    ${hxrtc_src}/rtc_base/net_helpers.cc
	    ${hxrtc_src}/api/jsep.cc
	
	    ${hxrtc_src}/test/vcm_capturer.cc
	    ${hxrtc_src}/test/test_video_capturer.cc
	    ${hxrtc_src}/media/base/video_adapter.cc
	    ${hxrtc_src}/api/video/video_frame.cc
		
	    ${hxrtc_src}/system_wrappers/source/field_trial.cc  # 不是${hxrtc_src}/third_party/webrtc_overrides/field_trial.cc
	    ${hxrtc_src}/api/rtp_parameters.cc
	    ${hxrtc_src}/media/base/codec.cc
	    ${hxrtc_src}/rtc_base/synchronization/sequence_checker_internal.cc
	    ${hxrtc_src}/api/create_peerconnection_factory.cc
		
	    ${hxrtc_src}/pc/jsep_session_description.cc
	    ${hxrtc_src}/api/candidate.cc
	    ${hxrtc_src}/rtc_base/helpers.cc
	    ${hxrtc_src}/pc/session_description.cc
	    ${hxrtc_src}/pc/jsep_ice_candidate.cc
	    ${hxrtc_src}/api/jsep_ice_candidate.cc
	    ${hxrtc_src}/pc/webrtc_sdp.cc
	    ${hxrtc_src}/pc/simulcast_sdp_serializer.cc
	    ${hxrtc_src}/pc/simulcast_description.cc
	    ${hxrtc_src}/pc/media_protocol_names.cc
	    ${hxrtc_src}/media/base/rid_description.cc
		${hxrtc_src}/media/base/sdp_video_format_utils.cc
	    ${hxrtc_src}/modules/rtp_rtcp/include/rtp_rtcp_defines.cc
	
	    ${hxrtc_src}/media/base/stream_params.cc
	    ${hxrtc_src}/p2p/base/transport_description.cc
	    ${hxrtc_src}/rtc_base/ssl_fingerprint.cc
	    ${hxrtc_src}/rtc_base/message_digest.cc
	    ${hxrtc_src}/rtc_base/openssl_digest.cc
	
	    ${hxrtc_src}/p2p/base/port.cc
	    ${hxrtc_src}/api/transport/stun.cc
	    ${hxrtc_src}/system_wrappers/source/metrics.cc
	    ${hxrtc_src}/rtc_base/byte_buffer.cc
	
	    ${hxrtc_src}/rtc_base/network.cc
	    ${hxrtc_src}/rtc_base/network_constants.cc
	    ${hxrtc_src}/p2p/base/connection.cc
	    ${hxrtc_src}/p2p/base/stun_request.cc
	)
endif()


# Create target.
add_executable(${PROJECT_NAME}
	src/Broadcaster.cpp
	src/main.cpp
	src/MediaStreamTrackFactory.cpp
	${SOURCE_FILES}
)

add_dependencies(${PROJECT_NAME} find_webrtc_libs1)
add_dependencies(${PROJECT_NAME} find_webrtc_libs2)
include(${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs1.cmake)
include(${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs2.cmake)

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
		absl::strings
		# absl::string_view
		absl::base
		absl::flags           # 注释，则报 很多 找不到 absl::flags_internal
		absl::flags_parse     # absl 和 WEBRTC_LIB 都打开，则报 重复定义 absl::raw_log_internal
		# ${CMAKE_BINARY_DIR}/webrtc/obj/third_party/abseil-cpp/absl/strings/string_view/string_view.o
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
		# ${hxrtc_obj}/stats/librtc_stats.a  # 不生效?
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