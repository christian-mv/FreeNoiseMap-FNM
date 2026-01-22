cmake_minimum_required(VERSION 3.16)
project(FreeNoiseMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Eigen
add_library(Eigen3 INTERFACE)
target_include_directories(Eigen3 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)

add_subdirectory(core)
add_subdirectory(ui)
