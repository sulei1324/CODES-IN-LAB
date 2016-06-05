#ifndef QT_MP_TEST_H
#define QT_MP_TEST_H

#include <QtGui/QMainWindow>
#include "ui_qt_mp_test.h"


class qt_mp_test : public QMainWindow
{
    Q_OBJECT

public:   
    qt_mp_test(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qt_mp_test();

private:
    Ui::qt_mp_testClass ui;
};

#endif // QT_MP_TEST_H
