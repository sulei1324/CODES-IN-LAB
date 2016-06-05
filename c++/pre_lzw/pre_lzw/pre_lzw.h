#ifndef PRE_LZW_H
#define PRE_LZW_H

#include <QtGui/QMainWindow>
#include "ui_pre_lzw.h"
#include <QString>
#include <QDir>
#include <QList>
#include <QRegExp>


class pre_lzw : public QMainWindow
{
    Q_OBJECT

public:
    pre_lzw(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~pre_lzw();

public slots:
    void do_work();
    void enable_button();

private:
    Ui::pre_lzwClass ui;
    void do_lzw(const QDir &);
};

#endif // PRE_LZW_H
