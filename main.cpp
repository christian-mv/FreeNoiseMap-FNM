#include "fnm_ui_main_window.h"
#include <QApplication>
#include <QByteArray>

int main(int argc, char *argv[])
{

    qputenv("QT_SCALE_FACTOR", QByteArray("1")); // https://github.com/christian-mv/Warning-QT_DEVICE_PIXEL_RATIO-is-deprecated-....git
    QApplication a(argc, argv);
    MainWindow window;

    window.showMaximized();       

    return a.exec();
}

