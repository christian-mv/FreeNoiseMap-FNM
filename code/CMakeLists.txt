cmake_minimum_required(VERSION 3.16)
project(FreeNoiseMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_subdirectory(core)
add_subdirectory(ui)
