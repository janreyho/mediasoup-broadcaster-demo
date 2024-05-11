#define MSC_CLASS "MediaStreamTrackFactory"

#include <iostream>

#include "MediaSoupClientErrors.hpp"
#include "MediaStreamTrackFactory.hpp"
#include "pc/test/fake_audio_capture_module.h"
#include "pc/test/fake_periodic_video_track_source.h"
#include "pc/test/frame_generator_capturer_video_track_source.h"
#include "pc/test/fake_video_track_source.h"
#include "system_wrappers/include/clock.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/create_peerconnection_factory.h"
#include "api/video_codecs/builtin_video_decoder_factory.h"
#include "api/video_codecs/builtin_video_encoder_factory.h"

#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_decoder_factory_template.h"
#include "api/video_codecs/video_decoder_factory_template_dav1d_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_libvpx_vp8_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_libvpx_vp9_adapter.h"
#include "api/video_codecs/video_decoder_factory_template_open_h264_adapter.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "api/video_codecs/video_encoder_factory_template.h"
#include "api/video_codecs/video_encoder_factory_template_libaom_av1_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_libvpx_vp8_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_libvpx_vp9_adapter.h"
#include "api/video_codecs/video_encoder_factory_template_open_h264_adapter.h"


#include "video/video_quality_test.h"

#include <stdio.h>

#if defined(WEBRTC_WIN)
#include <conio.h>
#endif

#include <algorithm>
#include <deque>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "api/fec_controller_override.h"
#include "api/rtc_event_log_output_file.h"
#include "api/task_queue/default_task_queue_factory.h"
#include "api/task_queue/task_queue_base.h"
#include "api/test/create_frame_generator.h"
#include "api/video/builtin_video_bitrate_allocator_factory.h"
#include "api/video_codecs/video_encoder.h"
#include "call/fake_network_pipe.h"
#include "call/simulated_network.h"
#include "media/base/media_constants.h"
#include "media/engine/adm_helpers.h"
#include "media/engine/fake_video_codec_factory.h"
#include "media/engine/internal_encoder_factory.h"
#include "media/engine/simulcast_encoder_adapter.h"
#include "media/engine/webrtc_video_engine.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_mixer/audio_mixer_impl.h"
#include "modules/video_coding/codecs/h264/include/h264.h"
#include "modules/video_coding/codecs/multiplex/include/multiplex_decoder_adapter.h"
#include "modules/video_coding/codecs/multiplex/include/multiplex_encoder_adapter.h"
#include "modules/video_coding/codecs/vp8/include/vp8.h"
#include "modules/video_coding/codecs/vp9/include/vp9.h"
#include "modules/video_coding/utility/ivf_file_writer.h"
#include "rtc_base/strings/string_builder.h"
#include "rtc_base/task_queue_for_test.h"
#include "test/platform_video_capturer.h"
#include "test/test_flags.h"
#include "test/testsupport/file_utils.h"
#include "test/video_renderer.h"
#include "video/frame_dumping_decoder.h"
#ifdef WEBRTC_WIN
#include "modules/audio_device/include/audio_device_factory.h"
#endif
#include "test/video_test_constants.h"
#include "video/config/encoder_stream_factory.h"
#include "test/field_trial.h"
#include "test/gtest.h"
#include "test/run_test.h"

#include "video/video_quality_test.h"


using namespace mediasoupclient;

static rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory;

/* MediaStreamTrack holds reference to the threads of the PeerConnectionFactory.
 * Use plain pointers in order to avoid threads being destructed before tracks.
 */
// static rtc::Thread* networkThread;
// static rtc::Thread* signalingThread;
  std::unique_ptr<rtc::Thread> signalingThread;
// static rtc::Thread* workerThread;

static void createFactory()
{
	// networkThread   = rtc::Thread::Create().release();
	signalingThread = rtc::Thread::CreateWithSocketServer();
	// workerThread    = rtc::Thread::Create().release();

	// networkThread->SetName("network_thread", nullptr);
	signalingThread->SetName("signaling_thread", nullptr);
	// workerThread->SetName("worker_thread", nullptr);

	// if (!networkThread->Start() || !signalingThread->Start() || !workerThread->Start())
	if(!signalingThread->Start())
	{
		MSC_THROW_INVALID_STATE_ERROR("thread start errored");
	}

	webrtc::PeerConnectionInterface::RTCConfiguration config;

	auto fakeAudioCaptureModule = FakeAudioCaptureModule::Create();
	if (!fakeAudioCaptureModule)
	{
		MSC_THROW_INVALID_STATE_ERROR("audio capture module creation errored");
	}

	factory = webrtc::CreatePeerConnectionFactory(
	  nullptr,
	  nullptr,
	  signalingThread.get(),
	  fakeAudioCaptureModule,
	  webrtc::CreateBuiltinAudioEncoderFactory(),
	  webrtc::CreateBuiltinAudioDecoderFactory(),
	//   webrtc::CreateBuiltinVideoEncoderFactory(),
	//   webrtc::CreateBuiltinVideoDecoderFactory(),
      std::make_unique<webrtc::VideoEncoderFactoryTemplate<
          webrtc::LibvpxVp8EncoderTemplateAdapter,
          webrtc::LibvpxVp9EncoderTemplateAdapter,
          webrtc::OpenH264EncoderTemplateAdapter,
          webrtc::LibaomAv1EncoderTemplateAdapter>>(),
      std::make_unique<webrtc::VideoDecoderFactoryTemplate<
          webrtc::LibvpxVp8DecoderTemplateAdapter,
          webrtc::LibvpxVp9DecoderTemplateAdapter,
          webrtc::OpenH264DecoderTemplateAdapter,
          webrtc::Dav1dDecoderTemplateAdapter>>(),
	  nullptr /*audio_mixer*/,
	  nullptr /*audio_processing*/);

	if (!factory)
	{
		MSC_THROW_ERROR("error ocurred creating peerconnection factory");
	}
}

// Audio track creation.
rtc::scoped_refptr<webrtc::AudioTrackInterface> createAudioTrack(const std::string& label)
{
	if (!factory)
		createFactory();

	cricket::AudioOptions options;
	options.highpass_filter = false;

	rtc::scoped_refptr<webrtc::AudioSourceInterface> source = factory->CreateAudioSource(options);

	return factory->CreateAudioTrack(label, source.get());
}

// Video track creation.
rtc::scoped_refptr<webrtc::VideoTrackInterface> createVideoTrack(const std::string& /*label*/)
{
	if (!factory)
		createFactory();

	auto* videoTrackSource =
	  new rtc::RefCountedObject<webrtc::FakePeriodicVideoTrackSource>(false /* remote */);

	return factory->CreateVideoTrack(rtc::CreateRandomUuid(), videoTrackSource);
}



namespace webrtc {
void Loopback() {     // 可以采集渲染成功
    RTC_LOG(LS_INFO) << __FUNCTION__;

    std::unique_ptr<test::TestVideoCapturer> hjy_video_capture = test::CreateVideoCapturer(640, 480, 15, 0);
    std::unique_ptr<test::VideoRenderer> hjy_local_preview;

    hjy_local_preview.reset(test::VideoRenderer::Create( "Local Preview", 640, 480));

    hjy_video_capture->AddOrUpdateSink(hjy_local_preview.get(),     // 用于添加或更新一个视频接收器
                                           rtc::VideoSinkWants());  // 指定视频接收器希望的（例如，帧的分辨率、帧率等）
	
	puts(">> Press ENTER to continue...");
    while (getc(stdin) != '\n' && !feof(stdin))
        ;  // NOLINT
}
}


rtc::scoped_refptr<webrtc::VideoTrackInterface> createSquaresVideoTrack(const std::string& /*label*/)
{
	if (!factory)
		createFactory();

	std::cout << "[INFO] getting frame generator" << std::endl;
	auto videoTrackSource = rtc::make_ref_counted<webrtc::FrameGeneratorCapturerVideoTrackSource>(
	  webrtc::FrameGeneratorCapturerVideoTrackSource::Config(), webrtc::Clock::GetRealTimeClock(), false);
	// videoTrackSource->Start();

	webrtc::test::RunTest(webrtc::Loopback);

	std::cout << "[INFO] creating video track" << std::endl;
	return factory->CreateVideoTrack(videoTrackSource, rtc::CreateRandomUuid());
	// return factory->CreateVideoTrack(webrtc::FakeVideoTrackSource::Create(), rtc::CreateRandomUuid());
}
