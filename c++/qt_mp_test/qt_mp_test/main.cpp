#include "qt_mp_test.h"
#include <QtGui/QApplication>
#include <omp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_mp_test w;
    w.show();
    return a.exec();
}
