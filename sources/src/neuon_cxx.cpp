#include "neuon_cxx.h"

#include "face_detection.h"
#include "speech_detection.h"
#include "composer.h"
#include "configuration.h"

neuon::neuon_t::neuon_t(std::unique_ptr<neuon::face_detection_t> face_detection, std::unique_ptr<neuon::speech_detection_t> speech_detection, std::unique_ptr<neuon::composer_t> composer)
    : face_detection(std::move(face_detection))
    , speech_detection(std::move(speech_detection))
    , composer(std::move(composer)) {

}
neuon::neuon_t::~neuon_t() = default;

void neuon::neuon_t::put(const neuon::audio_sample_t &sample) {
    std::vector<double> frame(sample.samples, 0.0);
    for (int