#include "widget.h"
#include <QApplication>
#include "my_personal_tools.h"
#include <QtDebug>
#include <QScrollArea>
#include "gradientcolor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();

}
