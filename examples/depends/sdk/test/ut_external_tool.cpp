#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "external_tool.h"

using posix::external_tool_t;

class uncovered_external_tool_t : public external_tool_t{
public:
    using external_tool_t::external_tool_t;
    using external_tool_t::arguments;
    using external_tool_t::execute;
};

TEST(external_tool, arguments){
    std::vector<std::string> args{"arg1", "arg2"};

    auto argv = uncovered_external_