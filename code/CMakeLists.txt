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
    main.cpp
    fnm_core_3D_segment.cpp
    fnm_core_gradient_color.cpp
    fnm_core_grid_settings.cpp
    fnm_core_noise_engine.cpp
    fnm_ui_main_window.cpp
    fnm_ui_qgraphics_item_abstract_point.cpp
    fnm_ui_qgraphics_item_abstract_polyline.cpp
    fnm_ui_qgraphics_item_barrier.cpp
    fnm_ui_qgraphics_item_multiline_source.cpp
    fnm_ui_qgraphics_item_point_receiver.cpp
    fnm_ui_qgraphics_item_point_source.cpp
    fnm_ui_qgraphics_item_polyline.cpp
    fnm_ui_qgraphics_item_raster_pixmap_area.cpp
    fnm_ui_qgraphics_item_shaded_line.cpp
    fnm_ui_qgraphics_item_simple_text.cpp
    fnm_ui_qgraphics_view.cpp
    fnm_ui_receivers_grid.cpp
)

set(PROJECT_HEADERS
    fnm_core_3D_segment.h
    fnm_core_barrier_segment.h
    fnm_core_gradient_color.h
    fnm_core_grid_settings.h
    fnm_core_line_source_segment.h
    fnm_core_noise_engine.h
    fnm_core_point_receiver.h
    fnm_core_point_source.h
    fnm_core_point.h
    fnm_core_types_namespace.h
    fnm_ui_main_window.h
    fnm_ui_qgraphics_item_abstract_point.h
    fnm_ui_qgraphics_item_abstract_polyline.h
    fnm_ui_qgraphics_item_barrier.h
    fnm_ui_qgraphics_item_multiline_source.h
    fnm_ui_qgraphics_item_point_receiver.h
    fnm_ui_qgraphics_item_point_source.h
    fnm_ui_qgraphics_item_polyline.h
    fnm_ui_qgraphics_item_raster_pixmap_area.h
    fnm_ui_qgraphics_item_shaded_line.h
    fnm_ui_qgraphics_item_simple_text.h
    fnm_ui_qgraphics_view.h
    fnm_ui_receivers_grid.h
)

set(PROJECT_FORMS
    mainwindow.ui
)

set(PROJECT_RESOURCES
    resources.qrc
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
