/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#include "video_quality_test.h"

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

namespace webrtc {


VideoQualityTesthjy::VideoQualityTesthjy(
    std::unique_ptr<InjectionComponents> injection_components){
    RTC_LOG(LS_INFO) << "------ VideoQualityTest: ";
}

VideoQualityTesthjy::InjectionComponents::InjectionComponents() = default;

VideoQualityTesthjy::InjectionComponents::~InjectionComponents() = default;


void VideoQualityTesthjy::RunWithRenderers() {
    RTC_LOG(LS_INFO) << __FUNCTION__;

    std::unique_ptr<test::TestVideoCapturer> hjy_video_capture = test::CreateVideoCapturer(640, 480, 15, 0);
    std::unique_ptr<test::VideoRenderer> hjy_local_preview;

    // if (params_.video[0].enabled) {
    // Create local preview
    hjy_local_preview.reset(test::VideoRenderer::Create( "Local Preview", 640, 480));

    hjy_video_capture->AddOrUpdateSink(hjy_local_preview.get(),     // 用于添加或更新一个视频接收器
                                           rtc::VideoSinkWants());  // 指定视频接收器希望的（例如，帧的分辨率、帧率等）

    puts(">> Press ENTER to continue...");
    while (getc(stdin) != '\n' && !feof(stdin))
        ;  // NOLINT

}

}  // namespace webrtc
