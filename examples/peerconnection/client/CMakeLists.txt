cmake_minimum_required(VERSION 3.10)
project(PeerConnectionClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wno-deprecated-declarations)

message(STATUS "------ PeerConnectionClient")

# set(hxrtc_src ${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src)
# set(hxrtc_obj ${CMAKE_BINARY_DIR}/webrtc/obj)
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
# message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
# message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
# message(STATUS "hxrtc_src: ${hxrtc_src}")
# message(STATUS "hxrtc_obj: ${hxrtc_obj}")

# add_subdirectory(${hxrtc_src}/third_party/jsoncpp/source ${CMAKE_BINARY_DIR}/jsoncpp_build)
# add_subdirectory(abseil-cpp)
# add_subdirectory(${hxrtc_src}/third_party/abseil-cpp ${CMAKE_BINARY_DIR}/abseil_build)
include_directories(${hxrtc_src}/third_party/abseil-cpp)
# include_directories(${hxrtc_src})
include_directories(${hxrtc_src}/third_party/jsoncpp/source/include/)
# include_directories(${hxrtc_src}/api/video_codecs/)
# include_directories(${hxrtc_src}/third_party/boringssl/src/include/)
include_directories(${hxrtc_src}/out/mac/gen)
# include("${hxrtc_src}/third_party/abseil-cpp/install/lib/cmake/absl/abslConfig.cmake")

# include(${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs1.cmake)
# include(${CMAKE_BINARY_DIR}/webrtc/find_webrtc_libs2.cmake)
# message(STATUS "RTC_BASE_LIBS library: ${RTC_BASE_LIBS}")



find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})


# file(GLOB libs_api "${hxrtc_obj}/api/*.a")
# if(libs_api)
#     message(STATUS "libs_api library: ${libs_api}")
#     set(libs_api ${libs_api} PARENT_SCOPE)
# endif()

# file(GLOB libs_audio_device "${hxrtc_obj}/modules/audio_device/*.a")
# if(libs_audio_device)
#     message(STATUS "libs_audio_device library: ${libs_audio_device}")
#     set(libs_audio_device ${libs_audio_device} PARENT_SCOPE)
# endif()

# file(GLOB libs_audio_processing "${hxrtc_obj}/modules/audio_processing/*.a")
# if(libs_audio_processing)
#     message(STATUS "libs_audio_processing library: ${libs_audio_processing}")
#     set(libs_audio_processing ${libs_audio_processing} PARENT_SCOPE)
# endif()

# file(GLOB libs_abls "${CMAKE_BINARY_DIR}/lib/libabsl*.a")
# if(libs_abls)
#     message(STATUS "libs_abls library: ${libs_abls}")
#     set(libs_abls ${libs_api} PARENT_SCOPE)
# endif()

# file(GLOB libs_peerconnection_client
#     ${hxrtc_obj}/api/libaudio_options_api.a
#     ${hxrtc_obj}/api/libcreate_peerconnection_factory.a
#     ${hxrtc_obj}/api/libjingle_peerconnection_api.a
#     ${hxrtc_obj}/api/libmedia_stream_interface.a
#     ${hxrtc_obj}/api/librtp_sender_interface.a
#     ${hxrtc_obj}/api/audio_codecs/libaudio_codecs_api.a
#     ${hxrtc_obj}/api/task_queue/libpending_task_safety_flag.a
#     ${hxrtc_obj}/api/units/libtime_delta.a
#     ${hxrtc_obj}/api/video/libvideo_frame.a
#     ${hxrtc_obj}/api/video/libvideo_rtp_headers.a
#     ${hxrtc_obj}/api/video_codecs/libvideo_codecs_api.a
#     ${hxrtc_obj}/media/librtc_media_base.a
#     ${hxrtc_obj}/p2p/librtc_p2p.a
#     ${hxrtc_obj}/pc/libvideo_track_source.a
#     ${hxrtc_obj}/rtc_base/libasync_dns_resolver.a
#     ${hxrtc_obj}/rtc_base/libchecks.a
#     ${hxrtc_obj}/rtc_base/liblogging.a
#     ${hxrtc_obj}/rtc_base/libnet_helpers.a
#     ${hxrtc_obj}/rtc_base/librtc_certificate_generator.a
#     ${hxrtc_obj}/rtc_base/libssl.a
#     ${hxrtc_obj}/rtc_base/libstringutils.a
#     ${hxrtc_obj}/rtc_base/libthreading.a
#     ${hxrtc_obj}/rtc_base/third_party/sigslot/libsigslot.a
#     # ${hxrtc_obj}/system_wrappers/libfield_trial.a
# )
# if(libs_peerconnection_client)
#     message(STATUS "libs_peerconnection_client library: ${libs_peerconnection_client}")
#     set(libs_peerconnection_client ${libs_audio_processing} PARENT_SCOPE)
# endif()

# 设置源文件
set(SOURCE_FILES
  conductor.cc
  defaults.cc
  peer_connection_client.cc
#   utils.cc
  linux/main.cc
  linux/main_wnd.cc
  linux/main_wnd.h
#   ${hxrtc_src}/api/video_codecs/sdp_video_format.cc
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

    ${hxrtc_src}/rtc_base/checks.cc

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
# 创建可执行文件
add_executable(peerconnection_client ${SOURCE_FILES})

# 链接库
target_link_libraries(peerconnection_client
    ${WEBRTC_LIB}     # 关闭则报 很多 boringssl、openssl的错误
    # ${hxrtc_obj}/third_party/boringssl/libboringssl.a      # 下面这些无法解决 ssl相关函数报错
    # ${hxrtc_src}/third_party/boringssl/src/build/crypto/libcrypto.a
    # ${hxrtc_src}/third_party/boringssl/src/build/ssl/libssl.a
    # ${hxrtc_src}/third_party/boringssl/src/build/libpki.a
    # ${hxrtc_src}/third_party/boringssl/src/build/decrepit/libdecrepit.a
    # ${LIBCXX_OBJECTS} 
    # ${LIBCXXABI_OBJECTS}

    # ${hxrtc_obj}/api/libfield_trials.a
#   test_field_trial
    absl::flags           # 注释，则报 很多 找不到 absl::flags_internal
    absl::flags_parse     # absl 和 WEBRTC_LIB 都打开，则报 重复定义 absl::raw_log_internal
    absl::flags_usage
    absl::strings
    X11
    # Threads::Threads           # 添加 pthread 库
    # -lpthread
    # ssl crypto
    ${CMAKE_DL_LIBS}  # 自动链接 libdl

    # absl::flags_internal  # 打开 也报 重复定义 absl::raw_log_internal     下面均无法解决 absl 报错
    # ${hxrtc_obj}/third_party/abseil-cpp/absl/flags/flag_internal/flag.o
    # ${CMAKE_BINARY_DIR}/lib/libabsl_flags_reflection-d.a
    # ${CMAKE_BINARY_DIR}/lib/libabsl_flags_commandlineflag-d.a
    # ${libs_abls}
    # -Wl,--exclude-libs,absl::flags
    # -Wl,--exclude-libs,absl::flags_parse
    # -Wl,--exclude-libs,absl::flags_usage

    # ${BORINGSSL_LIB}
    # ${RTC_BASE_LIBS}
    ${GLIB_LIBRARIES}
    ${GTK3_LIBRARIES}

    # jsoncpp_lib
    # ${hxrtc_obj}/api/libjingle_peerconnection_api.a
    # ${hxrtc_obj}/api/audio_codecs/libbuiltin_audio_decoder_factory.a
    # ${hxrtc_obj}/api/audio_codecs/libbuiltin_audio_encoder_factory.a
    # ${hxrtc_obj}/api/video/libvideo_frame.a
    # ${hxrtc_obj}/api/video/libvideo_rtp_headers.a
    # ## ../api/video_codecs
    # ${hxrtc_obj}/media/librtc_audio_video.a
    # ${hxrtc_obj}/media/libcodec.a

    # ${hxrtc_obj}/third_party/jsoncpp/jsoncpp/json_reader.o
    # ${hxrtc_obj}/third_party/jsoncpp/jsoncpp/json_value.o
    # ${hxrtc_obj}/third_party/jsoncpp/jsoncpp/json_writer.o
    # ${hxrtc_obj}/rtc_base/rtc_json/json.o
    # ${hxrtc_obj}/api/libcreate_peerconnection_factory.a
    # ${libs_api}
    # ${libs_audio_device}
    # ${libs_audio_processing}
    # ${libs_peerconnection_client}
    # ${hxrtc_obj}/modules/audio_processing/libapi.a
    # ${hxrtc_obj}/modules/video_capture/libvideo_capture_module.a
    # "../pc:libjingle_peerconnection",
    # "../rtc_base:rtc_json",
    # "../test:video_test_common",
    # ${hxrtc_src}/third_party/jsoncpp/source/build/lib/libjsoncpp.a
    ${CMAKE_BINARY_DIR}/lib/libjsoncpp-d.a
    # ${hxrtc_obj}/api/video_codecs/libvideo_codecs_api.a
)

# 设置链接器选项
set_target_properties(peerconnection_client PROPERTIES LINK_FLAGS "-Wl,--allow-multiple-definition")   # 不再报错 重复定义
# set_target_properties(peerconnection_client PROPERTIES LINK_FLAGS "-Wl,--exclude-libs,libabsl_raw_logging_internal-d.a")

# 设置编译选项
target_compile_options(peerconnection_client PRIVATE -Wno-deprecated-declarations)

# 设置 testonly 为 true（如果需要，可以通过添加一个自定义属性）
set_target_properties(peerconnection_client PROPERTIES TESTONLY TRUE)
# set_target_properties(peerconnection_client PROPERTIES LINK_FLAGS "-Wl,--exclude-libs,ALL")


