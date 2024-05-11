/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef VIDEO_VIDEO_QUALITY_TEST_H_
#define VIDEO_VIDEO_QUALITY_TEST_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "api/fec_controller.h"
#include "api/rtc_event_log/rtc_event_log_factory.h"
#include "api/task_queue/task_queue_base.h"
#include "api/task_queue/task_queue_factory.h"
#include "api/test/frame_generator_interface.h"
#include "api/test/video_quality_test_fixture.h"
#include "api/video/video_bitrate_allocator_factory.h"
#include "call/fake_network_pipe.h"
#include "media/engine/internal_decoder_factory.h"
#include "media/engine/internal_encoder_factory.h"
#include "test/call_test.h"
#include "test/layer_filtering_transport.h"
#include "video/video_analyzer.h"
#ifdef WEBRTC_WIN
#include "modules/audio_device/win/core_audio_utility_win.h"
#include "rtc_base/win/scoped_com_initializer.h"
#endif

namespace webrtc {

class VideoQualityTesthjy {
 public:

//  struct Params {
//     struct CallConfig {
//       bool send_side_bwe = false;
//       bool generic_descriptor = false;
//       bool dependency_descriptor = false;
//       BitrateConstraints call_bitrate_config;
//       int num_thumbnails = 0;
//       // Indicates if secondary_(video|ss|screenshare) structures are used.
//       bool dual_video = false;
//     } call;
//     struct Video {
//       bool enabled = false;
//       size_t width = 640;
//       size_t height = 480;
//       int32_t fps = 30;
//       int min_bitrate_bps = 50;
//       int target_bitrate_bps = 800;
//       int max_bitrate_bps = 800;
//       bool suspend_below_min_bitrate = false;
//       std::string codec = "VP8";
//       int num_temporal_layers = 1;
//       int selected_tl = -1;
//       int min_transmit_bps = 0;
//       bool ulpfec = false;
//       bool flexfec = false;
//       bool automatic_scaling = false;
//       std::string clip_path;  // "Generator" to generate frames instead.
//       size_t capture_device_index = 0;
//       CodecParameterMap sdp_params;
//       double encoder_overshoot_factor = 0.0;
//     } video[2];
//   };

  struct InjectionComponents {
    InjectionComponents();
    ~InjectionComponents();

  };

  explicit VideoQualityTesthjy(std::unique_ptr<InjectionComponents> injection_components);

//   void RunWithAnalyzer(const Params& params) override;
  void RunWithRenderers();

};

}  // namespace webrtc

#endif  // VIDEO_VIDEO_QUALITY_TEST_H_
