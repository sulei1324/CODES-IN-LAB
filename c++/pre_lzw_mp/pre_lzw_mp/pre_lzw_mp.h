#ifndef PRE_LZW_MP_H
#define PRE_LZW_MP_H

#include <QtGui/QMainWindow>
#include "ui_pre_lzw_mp.h"
#include<QThread>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QRegExp>
#include <FreeImage.h>
#include <QMutex>
#include <QDebug>
#include <QMutexLocker>
#include <omp.h>

class pre_lzw_mp : public QMainWindow
{
    Q_OBJECT

public:
    pre_lzw_mp(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~pre_lzw_mp();

public slots:
    void do_work();
    void enable_button();
    void do_lzw(QString);

private:
    Ui::pre_lzw_mpClass ui;
    QList<QString> pool;
    QString src;
    QString dst;
    int thread_num;
};

#endif // PRE_LZW_MP_H
