#include "frame_ptr.h"

#include <chrono>
#include <string>

extern "C"
{
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavcodec/avcodec.h>
}

inline std::string averr(int ret){
    char str[100]={0};
    auto p = av_strerror(ret, str, 100);
    return str;
}

class audio_resample_t {
public:
    audio_resample_t(uint32_t channel_layout, AVSampleFormat format, uint32_t sample_rate, size_t sr)
        : sr(sr)
        , l(AV_CH_LAYOUT_MONO)
        , f(AV_SAMPLE_FMT_DBL)
        , sc{swr_alloc_set_opts(
            nullptr,
            l, f, sr,
            channel_layout, format, sample_rate, 0, nullptr
        ), [](SwrContext *p) { swr_free(&p); }}{
        swr_init(sc.get());
    }

    std::pair<ffmpeg::frame_ptr, std::chrono::microseconds> resample(ffmpeg::frame_ptr input_frame) {

        ffmpeg::frame_ptr resampled_frame{av_frame_alloc(), [](AVFrame *p) { av_frame_free(&p); }};
        av_frame_copy_props(resampled_frame.get(), input_frame.get());

        resampled_frame->sample_rate = sr;
        resampled_frame->channel_layout = l;
        resampled_frame->format = f;

        int64_t input_pts = input_frame->pts * (sr * input_frame->sample_rate) / 1000000;
        std::chrono::microseconds next_pts{  swr_next_pts(sc.get(), input_pts) * 1000000 / (sr * input_frame->sample_rate) };

        int ret = swr_convert_frame(sc.get(), resampled_frame.get(), input_frame.get());

        return {std::move(resampled_frame), next_pts};
    }

private:
    size_t sr;
    uint32_t l;
    AVSampleFormat f;
    std::unique_ptr<SwrContext, std::function<voi