#pragma once

#include "http_error_code.h"
#include "response.h"
#include "transport_error.h"

#include <cstdint>
#include <map>
#include <string>
#include <memory>
#include <mutex>

#include <curl/curl.h>

namespace http{
    class curl_t {
    public:
        explicit curl_t(const std::string &base_url);

        response_t post(const std::string &url, const std::string &body = std::string(), const std::map<std::string, std::string> &headers = std::map<std::string, std::string>());
        response_t get(const std::string &url, const std::map<std::string, 