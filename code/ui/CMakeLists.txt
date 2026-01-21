set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(PROJECT_SOURCES
    main.cpp
    main_window.cpp
    qgraphics_items/qgraphics_item_abstract_point.cpp
    qgraphics_items/qgraphics_item_abstract_polyline.cpp
    qgraphics_items/qgraphics_item_barrier.cpp
    qgraphics_items/qgraphics_item_multiline_source.cpp
    qgraphics_items/qgraphics_item_point_receiver.cpp
    qgraphics_items/qgraphics_item_point_source.cpp
    qgraphics_items/qgraphics_item_polyline.cpp
    qgraphics_items/qgraphics_item_raster_pixmap_area.cpp
    qgraphics_items/qgraphics_item_shaded_line.cpp
    qgraphics_items/qgraphics_item_simple_text.cpp
    qgraphics_view.cpp
    receivers_grid.cpp
)

set(PROJECT_HEADERS
    main_window.h
    qgraphics_items/qgraphics_item_abstract_point.h
    qgraphics_items/qgraphics_item_abstract_polyline.h
    qgraphics_items/qgraphics_item_barrier.h
    qgraphics_items/qgraphics_item_multiline_source.h
    qgraphics_items/qgraphics_item_point_receiver.h
    qgraphics_items/qgraphics_item_point_source.h
    qgraphics_items/qgraphics_item_polyline.h
    qgraphics_items/qgraphics_item_raster_pixmap_area.h
    qgraphics_items/qgraphics_item_shaded_line.h
    qgraphics_items/qgraphics_item_simple_text.h
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
