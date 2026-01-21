cmake_minimum_required(VERSION 3.16)
project(FreeNoiseMap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Enable Qt's automatic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Define source, header, UI, and resource files
set(PROJECT_SOURCES
    ui/main.cpp
    core/fnm_core_3D_segment.cpp
    core/fnm_core_gradient_color.cpp
    core/fnm_core_grid_settings.cpp
    core/fnm_core_noise_engine.cpp
    ui/fnm_ui_main_window.cpp
    ui/fnm_ui_qgraphics_item_abstract_point.cpp
    ui/fnm_ui_qgraphics_item_abstract_polyline.cpp
    ui/fnm_ui_qgraphics_item_barrier.cpp
    ui/fnm_ui_qgraphics_item_multiline_source.cpp
    ui/fnm_ui_qgraphics_item_point_receiver.cpp
    ui/fnm_ui_qgraphics_item_point_source.cpp
    ui/fnm_ui_qgraphics_item_polyline.cpp
    ui/fnm_ui_qgraphics_item_raster_pixmap_area.cpp
    ui/fnm_ui_qgraphics_item_shaded_line.cpp
    ui/fnm_ui_qgraphics_item_simple_text.cpp
    ui/fnm_ui_qgraphics_view.cpp
    ui/fnm_ui_receivers_grid.cpp
)

set(PROJECT_HEADERS
    core/fnm_core_3D_segment.h
    core/fnm_core_barrier_segment.h
    core/fnm_core_gradient_color.h
    core/fnm_core_grid_settings.h
    core/fnm_core_line_source_segment.h
    core/fnm_core_noise_engine.h
    core/fnm_core_point_receiver.h
    core/fnm_core_point_source.h
    core/fnm_core_point.h
    core/fnm_core_types_namespace.h
    ui/fnm_ui_main_window.h
    ui/fnm_ui_qgraphics_item_abstract_point.h
    ui/fnm_ui_qgraphics_item_abstract_polyline.h
    ui/fnm_ui_qgraphics_item_barrier.h
    ui/fnm_ui_qgraphics_item_multiline_source.h
    ui/fnm_ui_qgraphics_item_point_receiver.h
    ui/fnm_ui_qgraphics_item_point_source.h
    ui/fnm_ui_qgraphics_item_polyline.h
    ui/fnm_ui_qgraphics_item_raster_pixmap_area.h
    ui/fnm_ui_qgraphics_item_shaded_line.h
    ui/fnm_ui_qgraphics_item_simple_text.h
    ui/fnm_ui_qgraphics_view.h
    ui/fnm_ui_receivers_grid.h
)

set(PROJECT_FORMS
    ui/mainwindow.ui
)

set(PROJECT_RESOURCES
    ui/resources.qrc
)

# Create the executable
add_executable(FreeNoiseMap
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    ${PROJECT_RESOURCES}
)

# Link against Qt6
target_link_libraries(FreeNoiseMap PRIVATE Qt6::Widgets)

# Include the current directory for headers
target_include_directories(FreeNoiseMap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(FreeNoiseMap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)
target_include_directories(FreeNoiseMap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ui)
