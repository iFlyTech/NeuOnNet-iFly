#include "extraction.h"
#include "version.h"
#include "birthday.h"
#include "options.h"
#include "sighandler.h"

#include "spdlog/spdlog.h"

#include <string>
#include <iostream>
#include <csignal>

#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {
    std::string media_filename;

    std::cout << std::string(argv[0]) << " :: " << mementor::version << " :: " << mementor::birthday << std::endl;
    namespace po = boost::program_options;
    po::options_description opt_desc("Options");
    opt_desc.add_options()
                ("help,h", "Produce this message")
                ("input-media,i", po::value(&media_filenam