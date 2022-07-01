
#include <functional>
#include <memory>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace ffmpeg{
    class track_adapter {
    public:
        explicit track_adapter(const AVStream &stream);

    private:
        std::unique_ptr<AVCodecParameters, std::function<void(AVCodecParam