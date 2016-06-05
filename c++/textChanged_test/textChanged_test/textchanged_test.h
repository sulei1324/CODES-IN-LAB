#ifndef TEXTCHANGED_TEST_H
#define TEXTCHANGED_TEST_H

#include <QtGui/QMainWindow>
#include "ui_textchanged_test.h"
#include <QString>
class textChanged_test : public QMainWindow
{
    Q_OBJECT

public:
    textChanged_test(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~textChanged_test();


public slots:
    void change_label(const QString &);
    
    
private:
    Ui::textChanged_testClass ui;
    


};

#endif // TEXTCHANGED_TEST_H
