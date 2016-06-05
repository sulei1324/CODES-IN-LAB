#include "pre_lzw_mp.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pre_lzw_mp w;
    w.show();
    return a.exec();
}
