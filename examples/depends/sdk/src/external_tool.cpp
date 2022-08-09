#include "external_tool.h"

#include <algorithm>
#include <iterator>
#include <iostream>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

#include <boost/asio.hpp>

using namespace posix;

external_tool_t::external_tool_t(const std::string &exec)
    : exec(exec)
{
}

external_tool_t::exit_status_t external_tool_t::execute(const std::vector<std::string> &args, int pipe) {
    exit_status_t ret{};
    int status(0);

    child_pid = fork();
    if (child_pid_error == *child_pid) {
        ret.code = -1;
    } else if (child_pid_default == *child_pid) {

        dup2(pipe, STDOUT_FILENO);
        dup2(pipe, STDERR_FILENO);
        close(pipe);

        auto argv = arguments(exec, args);
        // Never returns in case of success, exit child process in case of failure
        