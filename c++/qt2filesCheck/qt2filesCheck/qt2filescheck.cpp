#include "qt2filescheck.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QDir>
#include <QChar>
#include <QRegExp>
#include <QStringList>

qt2filesCheck::qt2filesCheck(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), result("")
{
    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(checkFilesIn2File()));
    connect(ui.pushButton_2, SIGNAL(clicked()), SLOT(saveResult()));
}

qt2filesCheck::~qt2filesCheck()
{

}

void qt2filesCheck::checkFilesIn2File(){
    QString src1_str = ui.lineEdit->text();
    QString src2_str = ui.lineEdit_2->text();
    QDir src1(src1_str);
    QDir src2(src2_str);
    QString lostnum;
    int num = 0;
    QString re_src2_str = "^\\d{5}\\.\\w*";
    QRegExp re_src1("^\\d{5}$");
    QRegExp re_src2(re_src2_str);
    src1.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    src2.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QStringList files_name_src1 = src1.entryList();
    QStringList files_name_src2 = src2.entryList();
    QStringList files_name_src1_serials;
    QStringList files_name_src2_serials;    
     for(int i = 0; i < files_name_src1.size(); i ++){
        QString tmp = files_name_src1.at(i);
        if(re_src1.exactMatch(tmp)){
            files_name_src1_serials<<tmp.left(5);
        }
    }    
    for(int i = 0; i < files_name_src2.size(); i ++){
        QString tmp = files_name_src2.at(i);
        if(re_src2.exactMatch(tmp)){
            files_name_src2_serials<<tmp.left(5);
        }
    }
    result.append("Lost Serials: \r\n");
    for(int i = 0; i < files_name_src1_serials.size(); i ++){
        QString tmp = files_name_src1_serials.at(i);
        if(!files_name_src2_serials.contains(tmp)){
            result.append(tmp);
            result.append("\r\n");
            num ++;
        }
    }
    if(num == 0){
        result = "There is no file lost. ";
    }else{
        result = "There are " + lostnum.setNum(num) + " files lost. \r\n" + result;
    }
    ui.textBrowser->setText(result);


}

void qt2filesCheck::saveResult(){
    QFileDialog *filedialog = new QFileDialog(this);
    QString filename = filedialog->getSaveFileName(this, tr("Save File"), "./lostserials.txt", tr("text (*.txt)"));;   
    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly);
    QTextStream text(file);
    text<<result;
    text.flush();
    file->close();


}