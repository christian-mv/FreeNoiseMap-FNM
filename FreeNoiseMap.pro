
QT       += core gui widgets

TARGET = freeNoiseMap
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
    grid_settings.cpp \
    minimal_acoustic_barrier.cpp \
    my_qgraphics_acoustic_barrier_item.cpp \
    my_qgraphics_multiline_source_item.cpp \
    receivers_grid.cpp \
    single_receiver.cpp \
    gradientcolor.cpp \
    mainwindow.cpp \
    noise_engine.cpp \
    mygraphicsview.cpp \
    pointsourcepixmap.cpp \
    myrasterpixmapitemarea.cpp \
    mygraphicsshadedlineitem.cpp \
    myqgraphicssimpletextitem.cpp \
    minimal_point_source.cpp \
    minimal_line_source.h.cpp

HEADERS += \
    minimal_acoustic_barrier.h \
    my_qgraphics_acoustic_barrier_item.h \
    my_qgraphics_multiline_source_item.h \
    receivers_grid.h \
    grid_settings.h \
    single_receiver.h \
    gradientcolor.h \
    noise_engine.h \
    mainwindow.h \
    mygraphicsview.h \
    pointsourcepixmapitem.h \
    myrasterpixmapitemarea.h \
    mygraphicsshadedlineitem.h \
    myqgraphicssimpletextitem.h \
    fnm_types.h \
    minimal_point_source.h \
    minimal_line_source.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
