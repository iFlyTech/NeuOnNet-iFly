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
        << " sync loss metric= " << std::setw(10) << result->mismatch_percentage << st