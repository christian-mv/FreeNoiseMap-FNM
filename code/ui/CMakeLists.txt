set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(PROJECT_SOURCES
    main.cpp
    main_window.cpp
    qgraphics_items/abstract_point_item.cpp
    qgraphics_items/abstract_polyline_item.cpp
    qgraphics_items/barrier_item.cpp
    qgraphics_items/multiline_source_item.cpp
    qgraphics_items/point_receiver_item.cpp
    qgraphics_items/point_source_item.cpp
    qgraphics_items/polyline_item.cpp
    qgraphics_items/raster_pixmap_area_item.cpp
    qgraphics_items/shaded_line_item.cpp
    qgraphics_items/simple_text_item.cpp
    fnm_view.cpp
    receivers_grid.cpp
)

set(PROJECT_HEADERS
    main_window.h
    qgraphics_items/abstract_point_item.h
    qgraphics_items/abstract_polyline_item.h
    qgraphics_items/barrier_item.h
    qgraphics_items/multiline_source_item.h
    qgraphics_items/point_receiver_item.h
    qgraphics_items/point_source_item.h
    qgraphics_items/polyline_item.h
    qgraphics_items/raster_pixmap_area_item.h
    qgraphics_items/shaded_line_item.h
    qgraphics_items/simple_text_item.h
    fnm_view.h
    receivers_grid.h
)

set(PROJECT_FORMS
    mainwindow.ui
)

set(PROJECT_RESOURCES
    resources.qrc
)

add_executable(FreeNoiseMap
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    ${PROJECT_RESOURCES}
)

target_link_libraries(FreeNoiseMap PRIVATE Qt6::Widgets core)

target_include_directories(FreeNoiseMap PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
)
