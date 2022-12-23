#pragma once

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>

#include <fstream>

namespace neuon{
    class face_detection_t {
    public:
        face_detection_t(size_t mouth_width, size_t mouth_height, std::ifstream &db)
            : mouth_width(mouth_width)
            , mouth_height(mouth_height) {
            dlib::deserialize(sp, db);
        }

        dlib::array2d<uint8_t> detect(const dlib::array2d<uint8_t> &img) {

            auto dets = detector(img);
            if (dets.size() == 1) {
                dlib::full_object_detection shape = sp(img, dets[0]);

                auto left_most_x = shape.part(48).x();
                auto right_most_x = shape.part(54).x();

                auto top_most_y = shape.part(52).y();
                a