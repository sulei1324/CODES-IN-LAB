#ifndef QTCHECKFILES_H
#define QTCHECKFILES_H

#include <QtGui/QMainWindow>
#include "ui_qtcheckfiles.h"

class qtCheckFiles : public QMainWindow
{
    Q_OBJECT

public:
    qtCheckFiles(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qtCheckFiles();
    
public slots:
    void get_file_address(const QString &);
    void get_file_postfix(const QString &);
    void find_lost_serials();

private:
    Ui::qtCheckFilesClass ui;
    QString src_address;
    QString postfix;
};

#endif // QTCHECKFILES_H
