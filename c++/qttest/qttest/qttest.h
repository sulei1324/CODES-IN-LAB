#ifndef QTTEST_H
#define QTTEST_H

#include <QtGui/QMainWindow>
#include "ui_qttest.h"
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QTest>
#include <QThread>
#include <QList>
#include <omp.h>
#include <iostream>
using namespace std;
class qttest : public QMainWindow
{
    Q_OBJECT

public:
    qttest(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qttest();
    void appendTextList(QString &s1);
private:
    Ui::qttestClass ui;
    QTimer *timer1;
    QTime *time;
    QList<QString> *text_list;
    int showed_num;
    //omp_lock_t *lock1;

signals:
    void textListChanged();
    
public slots:
    void on_pushButton_clicked();
    void showTime();
    void showText1();



};

class Thread1: public QThread{
public:
    void run();
    void setWidget(qttest *q1){q = q1;}
private:
    qttest *q;
};
#endif // QTTEST_H
