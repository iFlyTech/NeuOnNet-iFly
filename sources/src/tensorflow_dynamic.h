
#pragma once

#include "tensorflow_api.h"

#include <memory>
#include <vector>
#include <string>

namespace boost{
    namespace dll{
        class shared_library;
    }
}

namespace tensorflow{
    class dynamic_backend_t : public tensorflow::api_t, protected tensorflow::impl_t{
    public:
        explicit dynamic_backend_t(const std::string& shared_lib_path);

        graph_ptr TF_NewGraph() override;
        import_graph_def_options_ptr TF_NewImportGraphDefOptions() override;
        session_options_ptr TF_NewSessionOptions() override;
        status_ptr TF_NewStatus() override;

        TF_Code TF_GetCode(status_ptr &s);
        const char *TF_Message(status_ptr &s);

        buffer_ptr TF_NewBufferFromString(const void *proto, size_t proto_len) override;
        session_ptr TF_NewSession(graph_ptr &graph,
                                  const session_options_ptr &opts,
                                  status_ptr &status) override;
        const char *TF_Message(const status_ptr &s) override;
        void TF_GraphImportGraphDef(graph_ptr &graph, const buffer_ptr &graph_def,
                                    const import_graph_def_options_ptr &options, status_ptr &status) override;
        TF_Operation *TF_GraphOperationByName(graph_ptr &graph, const char *oper_name) override;
        tensor_ptr TF_AllocateTensor(TF_DataType, const int64_t *dims, int num_dims, size_t len) override;
        void TF_SessionRun(session_ptr &session, const buffer_ptr &run_options,
                           const TF_Output *inputs, const tensor_ptr *input_values, int ninputs,
                           const TF_Output *outputs, tensor_ptr *output_values, int noutputs,
                           const TF_Operation *const *target_opers, int ntargets,
                           buffer_ptr &run_metadata, status_ptr &status) override;
        void *TF_TensorData(const tensor_ptr &) override;
        size_t TF_TensorByteSize(const tensor_ptr &) override;

    private:
       using impl_t::unbox_ptr_collection;

    private:
        std::shared_ptr<boost::dll::shared_library> library{};
    };
}