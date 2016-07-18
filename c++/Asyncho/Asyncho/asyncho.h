#ifndef ASYNCHO_H
#define ASYNCHO_H

#include <QtGui/QMainWindow>
#include "ui_asyncho.h"
#include <iostream>
#include <tiffio.h>
#include <time.h>
#include <omp.h>
using namespace std;

class Asyncho : public QMainWindow
{
    Q_OBJECT

public:
    Asyncho(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Asyncho();
    void emitImageNeed(QString workType);

public slots:
    void readImages(QString workType);
    void doWork(QString workType);

signals:
    void needImages(QString workType);
    void readCompleted(QString workType);

private:
    Ui::AsynchoClass ui;
};

#endif // ASYNCHO_H
