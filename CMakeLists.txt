cmake_minimum_required(VERSION 3.10)

project(img3_contours LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(img3
    src/main.cpp
    src/geometry.cpp
    src/contour_io.cpp
    src/characteristic.cpp
    src/contour_features.cpp
    src/compare.cpp
)

target_include_directories(img3 PRIVATE include)
