// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "decoder.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"

#include <cassert>
#include <chrono>

extern "C"{
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
}

using namespace ffmpeg;

decoder::decoder(const AVCodecParameters &codecpar) {
    dec_ctx_deleter_t dec_ctx_deleter = [](AVCodecContext *p) {
        avcodec_free_context(&p);
    };
    const AVCodec *i_codec = avcodec_find_decoder(codecpar.codec_id);
    dec_ctx = dec_ctx_ptr(avcodec_alloc_context3(i_codec), dec_ctx_deleter);
    int err = avcodec_parameters_to_context(dec_ctx.get(