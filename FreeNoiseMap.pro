
QT       += core gui widgets

TARGET = FreeNoiseMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++14

SOURCES += \
    fnm_core_3D_segment.cpp \
    fnm_core_gradient_color.cpp \
    fnm_core_grid_settings.cpp \
    fnm_core_noise_engine.cpp \
    fnm_ui_main_window.cpp \
    fnm_ui_qgraphics_item_abstract_point.cpp \
    fnm_ui_qgraphics_item_abstract_polyline.cpp \
    fnm_ui_qgraphics_item_barrier.cpp \
    fnm_ui_qgraphics_item_multiline_source.cpp \
    fnm_ui_qgraphics_item_point_source.cpp \
    fnm_ui_qgraphics_item_polyline.cpp \
    fnm_ui_qgraphics_item_raster_pixmap_area.cpp \
    fnm_ui_qgraphics_item_shaded_line.cpp \
    fnm_ui_qgraphics_item_simple_text.cpp \
    fnm_ui_qgraphics_view.cpp \
    fnm_ui_receivers_grid.cpp \
        main.cpp

HEADERS += \
    fnm_core_3D_segment.h \
    fnm_core_barrier_segment.h \
    fnm_core_gradient_color.h \
    fnm_core_grid_settings.h \
    fnm_core_line_source_segment.h \
    fnm_core_noise_engine.h \
    fnm_core_point.h \
    fnm_core_point_source.h \
    fnm_core_single_receiver.h \
    fnm_core_types_namespace.h \
    fnm_ui_main_window.h \
    fnm_ui_qgraphics_item_abstract_point.h \
    fnm_ui_qgraphics_item_abstract_polyline.h \
    fnm_ui_qgraphics_item_barrier.h \
    fnm_ui_qgraphics_item_multiline_source.h \
    fnm_ui_qgraphics_item_point_source.h \
    fnm_ui_qgraphics_item_polyline.h \
    fnm_ui_qgraphics_item_raster_pixmap_area.h \
    fnm_ui_qgraphics_item_shaded_line.h \
    fnm_ui_qgraphics_item_simple_text.h \
    fnm_ui_qgraphics_view.h \
    fnm_ui_receivers_grid.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
