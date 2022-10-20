#include "version.h"
#include "birthday.h"
#include "options.h"
#include "interruption.h"
#include "sighandler.h"
#include "extraction.h"

#include "neuon/neuon_c.h"

#include "spdlog/spdlog.h"

#include <chrono>
#include <iostream>
#include <iomanip>

struct statistic_t {
    uint64_t nosync_samples{};
    uint64_t sync_samples{};
};

void print_result(neuon_user_data_t* user_data, const neuon_outcome_t *result) {
    static uint64_t counter = 0;
    std::cout << "#" << std::setw(10) << counter++
        << " pts= "<< std::setw(10) << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::microseconds(result->pts)).count()
        << " sync loss metric= " << std::setw(10) << result->mismatch_percentage << std::endl;
    statistic_t& statistic = *reinterpret_cast<statistic_t*>(user_data->opaque);
    if(result->mismatch_percentage > 0.5){
        statistic.nosync_samples++;
    } else {
        statistic.sync_samples++;
    }
};

void log_error(neuon_logging_t *log, const char *str){
    SPDLOG_ERROR(str);
}

void log_info(neuon_logging_t *log, const char *str) {
    SPDLOG_INFO(str);
}

void log_debug(neuon_logging_t *log, const char *str) {
    SPDLOG_DEBUG(str);
}

int main(int argc, char **argv) {
    std::string media_filename;
    std::string model_filename("model.pb");
    std::string norma_filename("normale.json");

    std::string face_landmark_db_filename("shape_predictor_68_face_landmarks.dat");
    std::string license_filename("neuon.key");

    std::cout << "neuon-sample :: " << neuon_sample::version << " :: " << neuon_sample::birthday << std::endl;
    namespace po = boost::program_options;
    po::options_description opt_desc("Options");
    opt_desc.add_options()
                ("help,h", "Produce this message")
                ("input-media,i", po::value(&media_filename)->required(), "Input media clip t