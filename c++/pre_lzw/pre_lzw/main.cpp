#include "pre_lzw.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pre_lzw w;
    w.show();
    return a.exec();
}
