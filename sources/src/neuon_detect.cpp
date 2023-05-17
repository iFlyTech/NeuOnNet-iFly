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
    std::string media_filen