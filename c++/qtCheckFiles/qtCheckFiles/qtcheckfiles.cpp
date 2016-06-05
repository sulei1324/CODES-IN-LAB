#include "qtcheckfiles.h"
#include <QDir>
#include <QString> 
#include <QChar>
#include <QRegExp>
#include <QDebug>



qtCheckFiles::qtCheckFiles(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), src_address(""), postfix("")
{
    ui.setupUi(this);
    connect(ui.lineEdit, SIGNAL(textChanged( const QString &)), SLOT(get_file_address( const QString &)));
    connect(ui.lineEdit_2, SIGNAL(textChanged( const QString &)), SLOT(get_file_postfix( const QString &)));
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(find_lost_serials()));
}

qtCheckFiles::~qtCheckFiles()
{

}

void qtCheckFiles::get_file_address(const QString & b){
    src_address = b;

}

void qtCheckFiles::get_file_postfix(const QString & a){
    postfix = a;

}

void qtCheckFiles::find_lost_serials(){
     int b = 0;
     int c = 0;
     int choosen_file_num = 0;
     int tmp = 0;
     QString output("<p>Lost serials are: </p>");
     QDir dir(src_address);
     QString re_str = "\\d{5}\\";
     re_str.append(postfix);
     dir.setFilter(QDir::Files | QDir::NoSymLinks);
     dir.setSorting(QDir::Name);
     QRegExp re(re_str);    
     QFileInfoList list = dir.entryInfoList();
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         if(re.exactMatch(fileInfo.fileName())){
            tmp = fileInfo.fileName().left(5).toInt();
            if(choosen_file_num == 0){
                b = tmp;
            } else if(b != tmp){
                QString s;
                QString e;
                output.append("<p>");
                output.append(s.setNum(b));
                output.append(" --- ");
                output.append(e.setNum(tmp - 1));
                output.append("</p>");
                b = tmp;
            }
            choosen_file_num += 1;
            b += 1;
         }
         
         
     }          
    ui.textBrowser->setText(output);

}
