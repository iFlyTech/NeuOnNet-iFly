// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "source.h"

#include <condition_variable>
#include <map>
#include <list>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

source_t::source_t(const std::string &filename, consumer video, consumer audio)
: dmx{new ffmpeg::demuxer(filename)}
{
    setup(*dmx, video, audio);
}

source_t::~source_t() = default;

void source_t::setup(ffmpeg::demuxer& dmx, const consumer &video, const consumer &audio) {
    auto tracks = dmx.tracks();
    //assert(tracks.size() == 2 && "Single Audio / Video streams only");

    for (auto &&track : tracks) {

        if(track.parameters.codec_type == AVMEDIA_TYPE_VIDEO){
            vdec = std::make_shared<ffmpeg::decoder>(track.parameters);
            decoders[track.index] = vdec;
            consumers[track.index] = video;
        } else if(track.parameters.codec_type == AVMEDIA_TYPE_AUDIO){
       