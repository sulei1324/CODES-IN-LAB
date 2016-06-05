/********************************************************************************
** Form generated from reading UI file 'pre_map.ui'
**
** Created: Fri Jun 3 22:09:18 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRE_MAP_H
#define UI_PRE_MAP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pre_mapClass
{
public:
    QAction *actionSrc;
    QAction *actionDst;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_8;
    QLCDNumber *lcdNumber;
    QLabel *label_9;
    QLineEdit *lineEdit_9;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pre_mapClass)
    {
        if (pre_mapClass->objectName().isEmpty())
            pre_mapClass->setObjectName(QString::fromUtf8("pre_mapClass"));
        pre_mapClass->resize(800, 360);
        pre_mapClass->setMinimumSize(QSize(800, 360));
        pre_mapClass->setMaximumSize(QSize(800, 360));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        pre_mapClass->setFont(font);
        actionSrc = new QAction(pre_mapClass);
        actionSrc->setObjectName(QString::fromUtf8("actionSrc"));
        actionDst = new QAction(pre_mapClass);
        actionDst->setObjectName(QString::fromUtf8("actionDst"));
        centralWidget = new QWidget(pre_mapClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 361, 301));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(20, 0, 10, 10);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pushButton->setFont(font1);

        gridLayout->addWidget(pushButton, 13, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 7, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFocusPolicy(Qt::StrongFocus);
        lineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);

        gridLayout->addWidget(lineEdit, 3, 3, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        lineEdit_7 = new QLineEdit(gridLayoutWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 9, 3, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);

        gridLayout->addWidget(label, 3, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 5, 3, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 6, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 4, 3, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 7, 3, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 9, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 12, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 12, 3, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 8, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 10, 1, 1, 1);

        lineEdit_6 = new QLineEdit(gridLayoutWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 8, 3, 1, 1);

        lineEdit_8 = new QLineEdit(gridLayoutWidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        gridLayout->addWidget(lineEdit_8, 10, 3, 1, 1);

        lcdNumber = new QLCDNumber(gridLayoutWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setLineWidth(1);
        lcdNumber->setNumDigits(10);
        lcdNumber->setProperty("intValue", QVariant(0));

        gridLayout->addWidget(lcdNumber, 13, 3, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 11, 1, 1, 1);

        lineEdit_9 = new QLineEdit(gridLayoutWidget);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        gridLayout->addWidget(lineEdit_9, 11, 3, 1, 1);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(360, 0, 431, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setUndoRedoEnabled(false);
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        pre_mapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(pre_mapClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        pre_mapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pre_mapClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        pre_mapClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(pre_mapClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        pre_mapClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSrc);
        menuFile->addAction(actionDst);

        retranslateUi(pre_mapClass);

        QMetaObject::connectSlotsByName(pre_mapClass);
    } // setupUi

    void retranslateUi(QMainWindow *pre_mapClass)
    {
        pre_mapClass->setWindowTitle(QApplication::translate("pre_mapClass", "pre_map", 0, QApplication::UnicodeUTF8));
        actionSrc->setText(QApplication::translate("pre_mapClass", "src", 0, QApplication::UnicodeUTF8));
        actionDst->setText(QApplication::translate("pre_mapClass", "dst", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("pre_mapClass", "Check Files", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("pre_mapClass", "Project Thickness:", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("pre_mapClass", "test_", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("pre_mapClass", "End Serial:", 0, QApplication::UnicodeUTF8));
        lineEdit_7->setText(QApplication::translate("pre_mapClass", "3", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("pre_mapClass", "Image Pre-name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("pre_mapClass", "Image Suf-name:", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("pre_mapClass", "4530", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setText(QApplication::translate("pre_mapClass", "4560", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("pre_mapClass", "Start Serial:", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("pre_mapClass", "_mon.tif", 0, QApplication::UnicodeUTF8));
        lineEdit_5->setText(QApplication::translate("pre_mapClass", "3", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("pre_mapClass", "Rolling Ball Radius:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("pre_mapClass", "Thread Number:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("pre_mapClass", "Resize Radio:", 0, QApplication::UnicodeUTF8));
        lineEdit_6->setText(QApplication::translate("pre_mapClass", "2", 0, QApplication::UnicodeUTF8));
        lineEdit_8->setText(QApplication::translate("pre_mapClass", "0.1", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("pre_mapClass", "Brightness:", 0, QApplication::UnicodeUTF8));
        lineEdit_9->setText(QApplication::translate("pre_mapClass", "40", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("pre_mapClass", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pre_mapClass: public Ui_pre_mapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRE_MAP_H
