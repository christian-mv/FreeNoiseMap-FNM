#include "widget.h"
#include <QApplication>
#include "dynamic_matrix.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MATRIX_OF_DOUBLES matriz = DynamicMatrix::createMatrixOfDoubles(5,10);


    return a.exec();
}
