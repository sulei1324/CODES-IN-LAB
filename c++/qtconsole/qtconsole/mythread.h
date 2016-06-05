#include <QThread>
#include <QtCore/QCoreApplication>
#include <QDir>
#include <iostream>
#include <QString> 
#include <QChar>
#include <QRegExp>
#include <QList>
#include <QMutex>
#include <QList>
#include <QtGui/QApplication>
#include <QtGui/QLabel>


 class MyThread : public QThread
 {
 public:
    MyThread();
    MyThread(int *, const QString &, QMutex *);
    ~MyThread();
    void run();
    QString thread_name;
    int *m;
    QMutex *mtx;
};
