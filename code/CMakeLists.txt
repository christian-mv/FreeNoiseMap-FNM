cmake_minimum_required(VERSION 3.16)
project(FreeNoiseMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Eigen
add_library(Eigen3 INTERFACE)
target_include_directories(Eigen3 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)

# Compiler Optimizations for Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-O3 -march=native -DNDEBUG -DEIGEN_NO_DEBUG)
    elseif(MSVC)
        add_compile_options(/O2 /Ob2 /Oi /Ot /Oy /GL)
        add_compile_definitions(NDEBUG EIGEN_NO_DEBUG)
    endif()
endif()

add_subdirectory(core)
add_subdirectory(ui)
