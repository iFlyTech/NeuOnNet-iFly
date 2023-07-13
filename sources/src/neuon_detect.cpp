// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "version.h"
#include "birthday.h"
#include "logging.h"
#include "options.h"
#include "demo.h"
#include "license.h"
#include "interruption.h"
#include "signal_handler.h"
#include "extraction.h"
#include "model.h"
#include "tensorflow_api.h"
#include "tensorflow_static.h"
#include "tensorflow_dynamic.h"

#include <chrono>
#include <iostream>

#include <boost/filesystem.hpp>

int main(int argc, char **argv){
    std::string media_filename;
    std::string model_filename;

    std::string face_landmark_db("shape_predictor_68_face_landmarks.dat");
    std::string license_filename("neuon.key");

    std::cout << "neuon-detect :: " << version << " :: " << birthday << std::endl;
    namespace po = boost::program_options;
    po::options_description opt_desc( "Options" );
    opt_desc.add_options( )
                ( "help,h", "Produce this message" )
                ( "input-media,i", po::value(&media_filename)->required(), "Input media clip to detect A/V sync" )
                ( "model,m", po::value(&model_filename)->required(), "Input media clip to detect A/V sync" )
                ( "landmarks,l", po::value(&face_landmark_db)->required()->default_value(face_landmark_db), "Face landmarks DB")
                ( "license,", po::value(&license_filename), "License file")
        ;

    logging::verbosity = logging::verbosity_t::info;

    po::positional_options_description pos_opt_desc;
    po::variables_map varmap;
    if( !options::is_args_valid(argc, argv, opt_desc, pos_opt_desc, varmap, std::cerr, std::cout ) ) {
        retu