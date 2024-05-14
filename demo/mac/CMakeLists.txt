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