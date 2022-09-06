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
        , 