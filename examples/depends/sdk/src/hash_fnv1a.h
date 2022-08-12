#pragma once

#include <cstddef>
#include <cstdint>


namespace algorithm{
    namespace detail{
        constexpr std::uint32_t fnv1a_32(const char* s, std::size_t count) {