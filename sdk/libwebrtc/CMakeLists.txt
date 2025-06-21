set(SOURCE_FILES
	api/test/create_frame_generator.cc
	media/base/fake_frame_source.cc
	pc/test/fake_audio_capture_module.cc
	rtc_base/task_queue_for_test.cc
	test/frame_generator.cc
	test/frame_generator_capturer.cc
	test/frame_utils.cc
	test/test_video_capturer.cc
	test/testsupport/ivf_video_frame_generator.cc
	# test/testsupport/file_utils.cc
	test/testsupport/file_utils_override.cc
	
	test/vcm_capturer.cc 
	test/test_video_capturer.cc 
	test/video_renderer.cc 
	test/gl/gl_renderer.cc 
	test/platform_video_capturer.cc 
	video/video_quality_test.cc
	audio/audio_state.cc
)


if(APPLE)
		set(SOURCE_FILES ${SOURCE_FILES}
		test/testsupport/ios_file_utils.mm
		test/testsupport/mac_file_utils.mm
        test/mac/hx_runder.mm
		test/mac/run_test.mm
        test/mac/video_renderer_mac.mm
        test/mac_capturer.mm
    )
elseif(WIN32)
    list(APPEND SOURCE_FILES
        # 添加Windows特定的源文件
        test/windows/some_windows_file.cc
    )
elseif(UNIX)
    list(APPEND SOURCE_FILES
        # 添加Linux特定的源文件
        # test/linux/some_linux_file.cc
    )
endif()

# Create target.
add_library(webrtc_broadcaster STATIC ${SOURCE_FILES})

# Private (implementation) header files.
target_include_directories(webrtc_broadcaster PRIVATE 
	${PROJECT_SOURCE_DIR}/sdk/libwebrtc
	${LIBWEBRTC_INCLUDE_PATH}/sdk/objc/base/
	${LIBWEBRTC_INCLUDE_PATH}/sdk/objc/
	${LIBWEBRTC_INCLUDE_PATH}/third_party/googletest/src/googletest/include
)

# Public (interface) headers from dependencies.
target_include_directories(webrtc_broadcaster PUBLIC
	"${LIBWEBRTC_INCLUDE_PATH}"
	"${LIBWEBRTC_INCLUDE_PATH}/third_party/abseil-cpp"
)

# Compile definitions for libwebrtc.
target_compile_definitions(webrtc_broadcaster PUBLIC
	$<$<NOT:$<PLATFORM_ID:Windows>>:WEBRTC_POSIX>
	$<$<PLATFORM_ID:Windows>:WEBRTC_WIN>
	$<$<PLATFORM_ID:Darwin>:WEBRTC_MAC>
)

