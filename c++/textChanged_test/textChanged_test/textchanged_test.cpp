#include "textchanged_test.h"

textChanged_test::textChanged_test(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.lineEdit, SIGNAL(textChanged( const QString & )), SLOT(change_label(const QString &)));
}

textChanged_test::~textChanged_test()
{

}

void textChanged_test::change_label(const QString &){
    ui.label->setText(ui.lineEdit->text());
}
