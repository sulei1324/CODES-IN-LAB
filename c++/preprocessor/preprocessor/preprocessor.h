#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <QtGui/QMainWindow>
#include "ui_preprocessor.h"
#include <QThread>
#include <QDebug>
#include "my_tar.h"
#include <string>
#include <cv.h>
#include <highgui.h>

class preprocessor : public QMainWindow
{
    Q_OBJECT

public:
    preprocessor(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~preprocessor();

private slots:
    void changeButton();


private:
    Ui::preprocessorClass ui;
};


#endif // PREPROCESSOR_H
