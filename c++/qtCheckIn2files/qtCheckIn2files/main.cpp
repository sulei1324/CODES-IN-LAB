
#include <QtCore/QCoreApplication>
#include <QString>
#include <QList>
#include <QDir>
#include <QChar>
#include <QRegExp>
#include <QStringList>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int b = 0;
    QString src1_str = "G:\\sulei\\workplace\\vs\\qtCheckIn2files\\qtCheckIn2files\\Resources\\src1";
    QString src2_str = "G:\\sulei\\workplace\\vs\\qtCheckIn2files\\qtCheckIn2files\\Resources\\src2";
    QDir src1(src1_str);
    QDir src2(src2_str);
    QString re_src2_str = "^\\d{5}\\.\\w*";
    QRegExp re_src1("^\\d{5}$");
    QRegExp re_src2(re_src2_str);
    src1.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    src2.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QStringList files_name_src1 = src1.entryList();
    QStringList files_name_src2 = src2.entryList();
    QStringList files_name_src1_serials;
    QStringList files_name_src2_serials;
    //std::cout<<files_name_src1.size()<<std::endl;
    //std::cout<<files_name_src2.size()<<std::endl;
    //for(int i = 0; i < files_name_src1.size(); i ++){
    //    QString tmp = files_name_src1.at(i);
    //    std::cout<<qPrintable(tmp)<<std::endl;
    //}
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
    //for(int i = 0; i < files_name_src2_serials.size(); i ++){
    //    QString tmp = files_name_src2_serials.at(i);
    //    std::cout<<qPrintable(tmp)<<std::endl;
    //} 
    std::cout<<"Lost Serials: "<<std::endl;
    for(int i = 0; i < files_name_src1_serials.size(); i ++){
        QString tmp = files_name_src1_serials.at(i);
        if(!files_name_src2_serials.contains(tmp)){
            std::cout<<qPrintable(tmp)<<std::endl;
        }
    }   
    std::cin>>b;
    return a.exec();
}
