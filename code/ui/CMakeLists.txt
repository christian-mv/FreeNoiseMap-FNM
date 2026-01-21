set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(PROJECT_SOURCES
    main.cpp
    main_window.cpp
    qgraphics_items/abstract_point.cpp
    qgraphics_items/abstract_polyline.cpp
    qgraphics_items/barrier.cpp
    qgraphics_items/multiline_source.cpp
    qgraphics_items/point_receiver.cpp
    qgraphics_items/point_source.cpp
    qgraphics_items/polyline.cpp
    qgraphics_items/raster_pixmap_area.cpp
    qgraphics_items/shaded_line.cpp
    qgraphics_items/simple_text.cpp
    qgraphics_view.cpp
    receivers_grid.cpp
)

set(PROJECT_HEADERS
    main_window.h
    qgraphics_items/abstract_point.h
    qgraphics_items/abstract_polyline.h
    qgraphics_items/barrier.h
    qgraphics_items/multiline_source.h
    qgraphics_items/point_receiver.h
    qgraphics_items/point_source.h
    qgraphics_items/polyline.h
    qgraphics_items/raster_pixmap_area.h
    qgraphics_items/shaded_line.h
    qgraphics_items/simple_text.h
    qgraphics_view.h
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
