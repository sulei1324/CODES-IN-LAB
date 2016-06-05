#ifndef QTSCROLLAREA_H
#define QTSCROLLAREA_H

#include <QtGui/QMainWindow>
#include "ui_qtscrollarea.h"

class qtscrollarea : public QMainWindow
{
    Q_OBJECT

public:
    qtscrollarea(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qtscrollarea();

private:
    Ui::qtscrollareaClass ui;
};

#endif // QTSCROLLAREA_H
