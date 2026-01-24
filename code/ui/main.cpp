#include "main_window.h"
#include <QApplication>
#include <QByteArray>

int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", QByteArray("1")); // https://github.com/christian-mv/Warning-QT_DEVICE_PIXEL_RATIO-is-deprecated-....git
    QApplication a(argc, argv);
    MainWindow window;

#ifdef Q_OS_WASM
    window.showFullScreen();
#else
    window.showMaximized();
#endif

    return a.exec();
}

