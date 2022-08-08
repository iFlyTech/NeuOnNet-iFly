#pragma once

#include "access_unit_adapter.h"
#include "interruption.h"
#include "track_adapter.h"

#include <map>
#include <vector>


typedef std::function<void(AVFormatContext *p)> dmx_ctx_deleter_t;
typedef std::unique_ptr<AVFormatContext, dmx_ctx_deleter_t> dmx_ctx_ptr;

namespace ffmpeg {
    class demuxer {
        typedef std::function<void(AVFormatContext *p)> dmx_ctx_deleter_t;
        typedef std::unique_ptr<AVFormatContext, dmx_ctx_deleter_t> dmx_ctx