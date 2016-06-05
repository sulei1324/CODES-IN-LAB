/********************************************************************************
** Form generated from reading UI file 'qt2filescheck.ui'
**
** Created: Fri Oct 23 20:38:10 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT2FILESCHECK_H
#define UI_QT2FILESCHECK_H

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

class Ui_qt2filesCheckClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt2filesCheckClass)
    {
        if (qt2filesCheckClass->objectName().isEmpty())
            qt2filesCheckClass->setObjectName(QString::fromUtf8("qt2filesCheckClass"));
        qt2filesCheckClass->resize(636, 513);
        centralWidget = new QWidget(qt2filesCheckClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 160, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 160, 40));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 30, 400, 40));
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 80, 400, 40));
        lineEdit_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 140, 581, 271));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 420, 90, 30));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 420, 90, 30));
        qt2filesCheckClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qt2filesCheckClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 636, 23));
        qt2filesCheckClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt2filesCheckClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qt2filesCheckClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qt2filesCheckClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qt2filesCheckClass->setStatusBar(statusBar);

        retranslateUi(qt2filesCheckClass);

        QMetaObject::connectSlotsByName(qt2filesCheckClass);
    } // setupUi

    void retranslateUi(QMainWindow *qt2filesCheckClass)
    {
        qt2filesCheckClass->setWindowTitle(QApplication::translate("qt2filesCheckClass", "qt2filesCheck", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qt2filesCheckClass", "The file uploaded", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("qt2filesCheckClass", "The file in RawData", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("qt2filesCheckClass", "Check", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("qt2filesCheckClass", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt2filesCheckClass: public Ui_qt2filesCheckClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT2FILESCHECK_H
