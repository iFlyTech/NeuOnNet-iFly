#include "demuxer.h"

#include "spdlog/spdlog.h"

#include <cassert>
#include <algorithm>

ffmpeg::demuxer::demuxer(const std::string &filename) {
    av_register_all();

    AVFormatContext *tmp_ctx(nullptr);
    int err = avformat_open_input(&tmp_ctx, filename.c_str(), NULL, NULL);
    assert(err == 0);
    SPDLOG_DEBUG("Opened demuxer context with return code ", err);
    dmx_ctx = dmx_ctx_ptr(tmp_ctx, [](AVFormatContext *p) {
        avformat_close_input(&p);
    });
    dmx_ctx->flags |= AVFMT_FLAG_GENPTS;

    err = avformat_find_stream_info(dmx_ctx.get(), NULL);
    SPDLOG_DEBUG("Detected streams info with return code {}", err);

    av_dump_format(dmx_ctx.get(), 0, filename.c_str(), false);

    start_time = std::chrono::microseconds(av_rescale_q(dmx_ctx->start_time, {1, AV_TIME_BASE}, access_unit_adapter::Microseconds));
}

std::vector<ffmpeg::track_adapter> ffmpeg::demuxer::tracks() const {
    std::vector<track_adapter> ret;
    std::transform(dmx_ctx->streams, dmx_ctx->streams + dmx_ctx