cmake_minimum_required(VERSION 3.10)
project(PeerConnectionServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "------ PeerConnectionServer")

# set(hxrtc_src ${CMAKE_SOURCE_DIR}/thirdparty/hxrtc/src)
# set(hxrtc_obj ${CMAKE_BINARY_DIR}/webrtc/obj)
# message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
# message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
# message(STATUS "hxrtc_src: ${hxrtc_src}")
# message(STATUS "hxrtc_obj: ${hxrtc_obj}")


# add_subdirectory(abseil-cpp)
# include_directories(${hxrtc_src}/third_party/abseil-cpp)
include_directories(${hxrtc_src})
# include("${hxrtc_src}/third_party/abseil-cpp/install/lib/cmake/absl/abslConfig.cmake")

message(STATUS "RTC_BASE_LIBS library: ${RTC_BASE_LIBS}")


# 设置源文件
set(SOURCE_FILES
  data_socket.cc
  main.cc
  peer_channel.cc
  utils.cc
  ${hxrtc_src}/rtc_base/string_encode.cc
)
# 创建可执行文件
add_executable(peerconnection_server ${SOURCE_FILES})

# 链接库
target_link_libraries(peerconnection_server
    ${WEBRTC_LIB} 

#   rtc_base_checks
#   rtc_base_stringutils
#   system_wrappers_field_trial
    # ${hxrtc_obj}/rtc_base/libchecks.a
    # ${hxrtc_obj}/rtc_base/libstringutils.a
    # ${hxrtc_obj}/system_wrappers/libfield_trial.a

    ${LIBCXX_OBJECTS} 
    ${LIBCXXABI_OBJECTS}
    -lX11
    # ${hxrtc_obj}/api/libfield_trials.a
#   test_field_trial

    absl::flags
    absl::flags_parse
    absl::flags_usage
    # ${hxrtc_src}/third_party/abseil-cpp/install/lib/libabsl_flags.a
    # ${hxrtc_src}/third_party/abseil-cpp/install/lib/libabsl_flags_parse.a
    # ${hxrtc_src}/third_party/abseil-cpp/install/lib/libabsl_flags_usage.a
    # ${hxrtc_src}/third_party/abseil-cpp/install/lib/libabsl_flags_internal.a
    ${RTC_BASE_LIBS}

)

# # 添加包含目录（如果有必要）
# target_include_directories(peerconnection_server PRIVATE
#   ${CMAKE_SOURCE_DIR}/peerconnection/server
#   ${CMAKE_SOURCE_DIR}/../rtc_base
#   ${CMAKE_SOURCE_DIR}/../system_wrappers
#   ${CMAKE_SOURCE_DIR}/../test
#   ${CMAKE_SOURCE_DIR}/third_party/abseil-cpp
# )

# 设置 testonly 为 true（如果需要，可以通过添加一个自定义属性）
set_target_properties(peerconnection_server PROPERTIES TESTONLY TRUE)
