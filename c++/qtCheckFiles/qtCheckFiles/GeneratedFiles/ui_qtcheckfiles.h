/********************************************************************************
** Form generated from reading UI file 'qtcheckfiles.ui'
**
** Created: Sat Sep 5 16:05:27 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCHECKFILES_H
#define UI_QTCHECKFILES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtCheckFilesClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtCheckFilesClass)
    {
        if (qtCheckFilesClass->objectName().isEmpty())
            qtCheckFilesClass->setObjectName(QString::fromUtf8("qtCheckFilesClass"));
        qtCheckFilesClass->resize(846, 512);
        centralWidget = new QWidget(qtCheckFilesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 25, 300, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 105, 300, 40));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(420, 30, 360, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        lineEdit->setFont(font1);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(420, 110, 360, 30));
        lineEdit_2->setFont(font1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(670, 420, 120, 30));
        pushButton->setFont(font1);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 160, 640, 290));
        qtCheckFilesClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtCheckFilesClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 846, 23));
        qtCheckFilesClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtCheckFilesClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qtCheckFilesClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtCheckFilesClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qtCheckFilesClass->setStatusBar(statusBar);

        retranslateUi(qtCheckFilesClass);

        QMetaObject::connectSlotsByName(qtCheckFilesClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtCheckFilesClass)
    {
        qtCheckFilesClass->setWindowTitle(QApplication::translate("qtCheckFilesClass", "qtCheckFiles", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qtCheckFilesClass", "Input the file address for checking", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("qtCheckFilesClass", "Input the postfix of the file name", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("qtCheckFilesClass", "Check", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtCheckFilesClass: public Ui_qtCheckFilesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCHECKFILES_H
