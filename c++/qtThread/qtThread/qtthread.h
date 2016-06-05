#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QtGui/QMainWindow>
#include "ui_qtthread.h"
#include <QString>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QString>
class qtThread : public QMainWindow
{
    Q_OBJECT
public:
    qtThread(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qtThread();
    void openThread();    
public slots:
    void do_job();

private:
    Ui::qtThreadClass ui;
    QList<QString> str_list;
};

class Mm: public QThread{
    Q_OBJECT
public:
    void run();
    

};


#endif // QTTHREAD_H
