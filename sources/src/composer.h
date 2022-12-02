#pragma once

#include <map>
#include <functional>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>

#include "dlib/array2d.h"
#include "dlib/array.h"
#include "dlib/image_processing.h"

namespace neuon {

    class composer_t {

        template<typename T>
        T clamp(T v, T min, T max) {
            if (v < min) return min;
            if (v > max) return max;
            return v;
        }

    public:
        using handler_t = std::function<
            void(const dlib::matrix<uint8_t> &,
                 const std::chrono::microseconds &,
                 const std::chrono::microseconds &,
                 const dlib::matrix<double> &,
                 const std::chrono::microseconds &,
                 const std::chrono::microseconds &
            )>;

        const size_t frames;
        const size_t samples;

        composer_t(size_t frames, size_t samples, const handler_t &handler)
            : frames(frames)
  