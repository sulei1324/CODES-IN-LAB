#include "qt_mp_test.h"
#include <omp.h>

qt_mp_test::qt_mp_test(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
}

qt_mp_test::~qt_mp_test()
{

}
