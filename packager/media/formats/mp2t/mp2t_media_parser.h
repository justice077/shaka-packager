// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_MP2T_MEDIA_PARSER_H_
#define MEDIA_FORMATS_MP2T_MP2T_MEDIA_PARSER_H_

#include <deque>
#include <map>
#include <memory>

#include "packager/base/memory/ref_counted.h"
#include "packager/media/base/byte_queue.h"
#include "packager/media/base/media_parser.h"
#include "packager/media/base/stream_info.h"

namespace shaka {
namespace media {

class MediaSample;

namespace mp2t {

class PidState;
class TsPacket;
class TsSection;

typedef std::deque<scoped_refptr<MediaSample> > SampleQueue;

class Mp2tMediaParser : public MediaParser {
 public:
  Mp2tMediaParser();
  ~Mp2tMediaParser() override;

  /// @name MediaParser implementation overrides.
  /// @{
  void Init(const InitCB& init_cb,
            const NewSampleCB& new_sample_cb,
            KeySource* decryption_key_source) override;
  bool Flush() override WARN_UNUSED_RESULT;
  bool Parse(const uint8_t* buf, int size) override WARN_UNUSED_RESULT;
  /// @}

 private:
  typedef std::map<int, std::unique_ptr<PidState>> PidMap;

  // Callback invoked to register a Program Map Table.
  // Note: Does nothing if the PID is already registered.
  void RegisterPmt(int program_number, int pmt_pid);

  // Callback invoked to register a PES pid.
  // Possible values for |media_type| are defined in:
  // ISO-13818.1 / ITU H.222 Table 2.34 "Media type assignments".
  // |pes_pid| is part of the Program Map Table refered by |pmt_pid|.
  void RegisterPes(int pmt_pid, int pes_pid, int media_type);

  // Callback invoked each time the audio/video decoder configuration is
  // changed.
  void OnNewStreamInfo(const scoped_refptr<StreamInfo>& new_stream_info);

  // Callback invoked by the ES media parser
  // to emit a new audio/video access unit.
  void OnEmitSample(uint32_t pes_pid,
                    const scoped_refptr<MediaSample>& new_sample);

  // Invoke the initialization callback if needed.
  bool FinishInitializationIfNeeded();

  bool EmitRemainingSamples();

  /// Set the value of the "SBR in mime-type" flag which leads to sample rate
  /// doubling. Default value is false.
  void set_sbr_in_mime_type(bool sbr_in_mimetype) {
    sbr_in_mimetype_ = sbr_in_mimetype; }

  // List of callbacks.
  InitCB init_cb_;
  NewSampleCB new_sample_cb_;

  bool sbr_in_mimetype_;

  // Bytes of the TS media.
  ByteQueue ts_byte_queue_;

  // List of PIDs and their states.
  PidMap pids_;

  // Whether |init_cb_| has been invoked.
  bool is_initialized_;

  DISALLOW_COPY_AND_ASSIGN(Mp2tMediaParser);
};

}  // namespace mp2t
}  // namespace media
}  // namespace shaka

#endif
