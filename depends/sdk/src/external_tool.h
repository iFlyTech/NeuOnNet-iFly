#pragma once

#include <string>
#include <vector>
#include <future>

#include <boost/optional.hpp>

namespace posix{
    class external_tool_t {
        static const pid_t child_pid_default{0};
        static const pid_t chil