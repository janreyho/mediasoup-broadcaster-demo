#include "Broadcaster.hpp"
// #include "mediasoupclient.hpp"
#include <cpr/cpr.h>
#include <csignal> // sigsuspend()
#include <cstdlib>
#include <iostream>
#include <string>

#include <stdio.h>

#if defined(WEBRTC_WIN)
#include <conio.h>
#endif

// #include <algorithm>
// #include <deque>
// #include <map>
// #include <memory>
// #include <string>
// #include <vector>

// #include "api/fec_controller_override.h"
// #include "api/rtc_event_log_output_file.h"
// #include "api/task_queue/default_task_queue_factory.h"
// #include "api/task_queue/task_queue_base.h"
// #include "api/test/create_frame_generator.h"
// #include "api/video/builtin_video_bitrate_allocator_factory.h"
// #include "api/video_codecs/video_encoder.h"
// #include "call/fake_network_pipe.h"
// #include "call/simulated_network.h"
// #include "media/base/media_constants.h"
// #include "media/engine/adm_helpers.h"
// #include "media/engine/fake_video_codec_factory.h"
// #include "media/engine/internal_encoder_factory.h"
// #include "media/engine/simulcast_encoder_adapter.h"
// #include "media/engine/webrtc_video_engine.h"
// #include "modules/audio_device/include/audio_device.h"
// #include "modules/audio_mixer/audio_mixer_impl.h"
// #include "modules/video_coding/codecs/h264/include/h264.h"
// #include "modules/video_coding/codecs/multiplex/include/multiplex_decoder_adapter.h"
// #include "modules/video_coding/codecs/multiplex/include/multiplex_encoder_adapter.h"
// #include "modules/video_coding/codecs/vp8/include/vp8.h"
// #include "modules/video_coding/codecs/vp9/include/vp9.h"
// #include "modules/video_coding/utility/ivf_file_writer.h"
// #include "rtc_base/strings/string_builder.h"
// #include "rtc_base/task_queue_for_test.h"
// #include "test/platform_video_capturer.h"
// #include "test/test_flags.h"
// #include "test/testsupport/file_utils.h"
// #include "test/video_renderer.h"
// #include "video/frame_dumping_decoder.h"
#ifdef WEBRTC_WIN
#include "modules/audio_device/include/audio_device_factory.h"
#endif
// #include "test/video_test_constants.h"
// #include "video/config/encoder_stream_factory.h"
// #include "test/field_trial.h"
// #include "test/gtest.h"
// #include "test/run_test.h"

// #include "video/video_quality_test.h"


using json = nlohmann::json;

void signalHandler(int signum)
{
	std::cout << "[INFO] interrupt signal (" << signum << ") received" << std::endl;

	std::cout << "[INFO] leaving!" << std::endl;

	std::exit(signum);
}

// namespace webrtc {
// void Loopback22() {     // 可以采集渲染成功
//     RTC_LOG(LS_INFO) << __FUNCTION__;

//     std::unique_ptr<test::TestVideoCapturer> hjy_video_capture = test::CreateVideoCapturer(640, 480, 15, 0);
//     std::unique_ptr<test::VideoRenderer> hjy_local_preview;

//     hjy_local_preview.reset(test::VideoRenderer::Create( "Local Preview", 640, 480));

//     hjy_video_capture->AddOrUpdateSink(hjy_local_preview.get(),     // 用于添加或更新一个视频接收器
//                                            rtc::VideoSinkWants());  // 指定视频接收器希望的（例如，帧的分辨率、帧率等）

//     puts(">> Press ENTER to continue...");
//     while (getc(stdin) != '\n' && !feof(stdin))
//         ;  // NOLINT
// }
// }

int main(int /*argc*/, char* /*argv*/[])
{
	// webrtc::test::RunTest(webrtc::Loopback22);
	// Register signal SIGINT and signal handler.
	signal(SIGINT, signalHandler);

	// Retrieve configuration from environment variables.
	const char* envServerUrl    = std::getenv("SERVER_URL");
	const char* envRoomId       = std::getenv("ROOM_ID");
	const char* envEnableAudio  = std::getenv("ENABLE_AUDIO");
	const char* envUseSimulcast = std::getenv("USE_SIMULCAST");
	const char* envWebrtcDebug  = std::getenv("WEBRTC_DEBUG");
	const char* envVerifySsl    = std::getenv("VERIFY_SSL");

	if (envServerUrl == nullptr)
	{
		std::cerr << "[ERROR] missing 'SERVER_URL' environment variable" << std::endl;

		return 1;
	}

	if (envRoomId == nullptr)
	{
		std::cerr << "[ERROR] missing 'ROOM_ID' environment variable" << std::endl;

		return 1;
	}

	std::string baseUrl = envServerUrl;
	baseUrl.append("/rooms/").append(envRoomId);

	bool enableAudio = true;

	if (envEnableAudio && std::string(envEnableAudio) == "false")
		enableAudio = false;

	bool useSimulcast = true;

	if (envUseSimulcast && std::string(envUseSimulcast) == "false")
		useSimulcast = false;

	bool verifySsl = true;
	if (envVerifySsl && std::string(envVerifySsl) == "false")
		verifySsl = false;

	// Set RTC logging severity.
	if (envWebrtcDebug)
	{
		if (std::string(envWebrtcDebug) == "info")
			rtc::LogMessage::LogToDebug(rtc::LoggingSeverity::LS_INFO);
		else if (std::string(envWebrtcDebug) == "warn")
			rtc::LogMessage::LogToDebug(rtc::LoggingSeverity::LS_WARNING);
		else if (std::string(envWebrtcDebug) == "error")
			rtc::LogMessage::LogToDebug(rtc::LoggingSeverity::LS_ERROR);
	}

	rtc::LogMessage::LogToDebug(rtc::LoggingSeverity::LS_Network);
	auto logLevel = mediasoupclient::Logger::LogLevel::LOG_DEBUG;
	mediasoupclient::Logger::SetLogLevel(logLevel);
	mediasoupclient::Logger::SetDefaultHandler();

	// Initilize mediasoupclient.
	mediasoupclient::Initialize();

	std::cout << "[INFO] welcome to mediasoup broadcaster app!\n" << std::endl;

	std::cout << "[INFO] verifying that room '" << envRoomId << "' exists..." << std::endl;
	auto r = cpr::GetAsync(cpr::Url{ baseUrl }, cpr::VerifySsl{ verifySsl }).get();

	if (r.status_code != 200)
	{
		std::cerr << "[ERROR] unable to retrieve room info"
		          << " [status code:" << r.status_code << ", body:\"" << r.text << "\"]" << std::endl;

		return 1;
	}
	else
	{
		std::cout << "[INFO] found room" << envRoomId << std::endl;
	}

	auto response = nlohmann::json::parse(r.text);

	Broadcaster broadcaster;

	broadcaster.Start(baseUrl, enableAudio, useSimulcast, response, verifySsl);

	std::cout << "[INFO] press Ctrl+C or Cmd+C to leave..." << std::endl;

	while (true)
	{
		std::cin.get();
	}

	return 0;
}
