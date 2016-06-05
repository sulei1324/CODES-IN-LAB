#ifndef BOUTTONMARKER_H
#define BOUTTONMARKER_H

#include <QtGui/QMainWindow>
#include "ui_bouttonmarker.h"

class BouttonMarker : public QMainWindow
{
    Q_OBJECT

public:
    BouttonMarker(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~BouttonMarker();

private:
    Ui::BouttonMarkerClass ui;
};

#endif // BOUTTONMARKER_H
