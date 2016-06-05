#include "qtcheckfiles.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtCheckFiles w;
    w.show();
    return a.exec();
}
