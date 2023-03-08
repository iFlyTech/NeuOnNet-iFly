// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "model.h"

#include <boost/numeric/ublas/tensor.hpp>

using neuon::model_t;

model_t::model_t(std::shared_ptr<tensorflow::api_t> api, const std::vector<uint8_t>& model_payload, const normalization_t& normalization )
: api(api)
, graph(api->TF_NewGraph())
, normalization(normalization){

    tensorflow::buffer_ptr buf(api->TF_NewBufferFromString(model_payload.data(), model_payload.size()));

    tensorflow::import_graph_def_options_ptr opts( api->TF_NewImportGraphDefOptions());

    tensorflow::status_ptr status( api->TF_NewStatus());

    api->TF_GraphImportGraphDef(graph, buf, opts, status);

    tensorflow::session_options_ptr session_opts(api->TF_NewSessionOptions());

    session = api->TF_NewSession(graph, session_opts, status);
}

model_t::~model_t() = default;

std::vector<float> model_t::predict(const dlib::matrix<uint8_t> &x_video, const std::vector<int64_t>& video_dims, const dlib::matrix<double> &x_audio, const std::vector<int64_t>& audio_dims ) {
    static const std::string input_layer_video_name = "input_1";
    static const std::string input_layer_audio_name = "input_2";
    static const std::string output_layer_name = "lambda_1/Sqrt";

    std::vector<TF_Output> inputs{{api->TF_GraphOperationByName(graph, input_layer_video_name.c_str()), 0}, {api->TF_