#include "textchanged_test.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    textChanged_test w;
    w.show();
    return a.exec();
}
