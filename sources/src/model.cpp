// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "model.h"

#include <boost/numeric/ublas/tensor.hpp>

using neuon::model_t;

model_t::model_t(std::shared_ptr<tensorflow::api_t> api, const std::ve