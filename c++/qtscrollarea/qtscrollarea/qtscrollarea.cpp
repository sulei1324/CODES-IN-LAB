#include "qtscrollarea.h"

qtscrollarea::qtscrollarea(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    ui.label->setText("<p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>1</p><p>0</p>");
}

qtscrollarea::~qtscrollarea()
{

}
