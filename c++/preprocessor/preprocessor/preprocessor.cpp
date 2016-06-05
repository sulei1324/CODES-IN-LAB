#include "preprocessor.h"
#include <QString>

preprocessor::preprocessor(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(changeButton()));
    ui.label->setText("dddd");
    qDebug()<<(ui.label->parentWidget() == ui.tab);
}

preprocessor::~preprocessor()
{

}


void preprocessor::changeButton(){
    QString s("aaaa");
    ui.pushButton->setText(s);

}
