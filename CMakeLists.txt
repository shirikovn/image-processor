cmake_minimum_required(VERSION 3.10)

project(image-processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(utils)
include_directories(filters)
include_directories(filters/filters_impl)
include_directories(image/bmp)
include_directories(image/pixel)

add_executable(
    image_processor
    
    utils/parser.cpp

    image/bmp/bitmap.cpp
    image/pixel/pixel.cpp

    filters/filter_source.cpp
    filters/filters_impl/grayscale.cpp
    filters/filters_impl/negative.cpp
    filters/filters_impl/sharpening.cpp
    filters/filters_impl/edge_detection.cpp
    filters/filters_impl/crop.cpp
    filters/filters_impl/gaussian_blur.cpp
    filters/filters_impl/chess_brigthness.cpp

    image_processor.cpp
)
