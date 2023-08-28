/********************************************************************************
** Form generated from reading UI file 'guichatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUICHATWINDOW_H
#define UI_GUICHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiChatWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser_msgShow;
    QPushButton *pushButton_sendMsg;
    QLineEdit *lineEdit_msgEdit;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *GuiChatWindow)
    {
        if (GuiChatWindow->objectName().isEmpty())
            GuiChatWindow->setObjectName("GuiChatWindow");
        GuiChatWindow->resize(568, 559);
        GuiChatWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(GuiChatWindow);
        centralwidget->setObjectName("centralwidget");
        textBrowser_msgShow = new QTextBrowser(centralwidget);
        textBrowser_msgShow->setObjectName("textBrowser_msgShow");
        textBrowser_msgShow->setGeometry(QRect(10, 10, 541, 351));
        textBrowser_msgShow->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;"));
        pushButton_sendMsg = new QPushButton(centralwidget);
        pushButton_sendMsg->setObjectName("pushButton_sendMsg");
        pushButton_sendMsg->setGeometry(QRect(460, 490, 89, 25));
        pushButton_sendMsg->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"background-color: rgb(247, 247, 247);\n"
"font: 12pt \"Candara\";"));
        lineEdit_msgEdit = new QLineEdit(centralwidget);
        lineEdit_msgEdit->setObjectName("lineEdit_msgEdit");
        lineEdit_msgEdit->setGeometry(QRect(10, 380, 541, 91));
        lineEdit_msgEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;"));
        GuiChatWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GuiChatWindow);
        statusbar->setObjectName("statusbar");
        GuiChatWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(GuiChatWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 568, 22));
        GuiChatWindow->setMenuBar(menubar);

        retranslateUi(GuiChatWindow);

        QMetaObject::connectSlotsByName(GuiChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GuiChatWindow)
    {
        GuiChatWindow->setWindowTitle(QCoreApplication::translate("GuiChatWindow", "MainWindow", nullptr));
        pushButton_sendMsg->setText(QCoreApplication::translate("GuiChatWindow", "\345\217\221\351\200\201", nullptr));
        lineEdit_msgEdit->setPlaceholderText(QCoreApplication::translate("GuiChatWindow", "Type message here...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuiChatWindow: public Ui_GuiChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUICHATWINDOW_H
