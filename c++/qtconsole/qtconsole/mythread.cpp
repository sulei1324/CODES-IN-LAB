#include <mythread.h>

void MyThread::run(){
    (*mtx).lock();
    *m += 10;
    *m -= 3;
    std::cout<<thread_name.toStdString()<<": "<<*m<<std::endl;
    (*mtx).unlock();
}

MyThread::MyThread(){
    m = 0;
    mtx = 0;
    thread_name = "";
}

MyThread::~MyThread(){
}

MyThread::MyThread(int *x, const QString &n, QMutex *mu){
    m = x;
    mtx = mu;
    thread_name = n;
}

