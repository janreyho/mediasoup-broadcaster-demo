cmake_minimum_required(VERSION 3.10)

# add_subdirectory(loghello)

if(WIN32)
    add_subdirectory(peerconnection/server)
elseif(APPLE)
elseif(UNIX)
    # add_subdirectory(${hxrtc_src}/third_party/jsoncpp/source ${CMAKE_BINARY_DIR}/jsoncpp_build)
    add_subdirectory(${hxrtc_src}/third_party/abseil-cpp ${CMAKE_BINARY_DIR}/abseil_build)
    add_subdirectory(peerconnection/server)
    add_subdirectory(peerconnection/client)
endif()



set(WebrtcSDK ${WebrtcSDK} PARENT_SCOPE)
