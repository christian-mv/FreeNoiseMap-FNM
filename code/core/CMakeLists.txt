add_library(core STATIC
    segment.cpp
    segment.h
    barrier_segment.cpp
    barrier_segment.h
    gradient_color.cpp
    gradient_color.h
    grid_settings.cpp
    grid_settings.h
    line_source_segment.cpp
    line_source_segment.h
    noise_engine.cpp
    noise_engine.h
    point.cpp
    point.h
    point_receiver.cpp
    point_receiver.h
    point_source.cpp
    point_source.h
    types_namespace.h
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
