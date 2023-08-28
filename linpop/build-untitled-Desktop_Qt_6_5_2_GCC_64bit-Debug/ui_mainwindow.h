/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget_friendList;
    QPushButton *pushButton_addFriend;
    QPushButton *pushButton_startChat;
    QPushButton *pushButton_sendFile;
    QLabel *label_userWelcome;
    QPushButton *pushButton_deleteFriend;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(745, 474);
        MainWindow->setMinimumSize(QSize(320, 474));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        listWidget_friendList = new QListWidget(centralwidget);
        listWidget_friendList->setObjectName("listWidget_friendList");
        listWidget_friendList->setGeometry(QRect(10, 50, 281, 371));
        pushButton_addFriend = new QPushButton(centralwidget);
        pushButton_addFriend->setObjectName("pushButton_addFriend");
        pushButton_addFriend->setGeometry(QRect(310, 90, 111, 41));
        pushButton_addFriend->setStyleSheet(QString::fromUtf8("background-color: #eee;\n"
"color: black;\n"
"border: 1px solid #555;\n"
"padding: 10px 20px;\n"
"font-size: 16px;\n"
"font-weight: bold;"));
        pushButton_startChat = new QPushButton(centralwidget);
        pushButton_startChat->setObjectName("pushButton_startChat");
        pushButton_startChat->setGeometry(QRect(10, 410, 281, 41));
        pushButton_startChat->setStyleSheet(QString::fromUtf8("background-color: #fff;\n"
"color: black;\n"
"border: 1px solid gray;\n"
"padding: 10px 20px;\n"
"font-size: 16px;\n"
"font-weight: bold;"));
        pushButton_sendFile = new QPushButton(centralwidget);
        pushButton_sendFile->setObjectName("pushButton_sendFile");
        pushButton_sendFile->setGeometry(QRect(310, 330, 111, 41));
        pushButton_sendFile->setStyleSheet(QString::fromUtf8("background-color: #eee;\n"
"color: black;\n"
"border: 1px solid #555;\n"
"padding: 10px 20px;\n"
"font-size: 16px;\n"
"font-weight: bold;"));
        label_userWelcome = new QLabel(centralwidget);
        label_userWelcome->setObjectName("label_userWelcome");
        label_userWelcome->setGeometry(QRect(310, 10, 341, 41));
        label_userWelcome->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"color: #333;\n"
"background-color: #fff;\n"
"text-align: center;"));
        pushButton_deleteFriend = new QPushButton(centralwidget);
        pushButton_deleteFriend->setObjectName("pushButton_deleteFriend");
        pushButton_deleteFriend->setGeometry(QRect(310, 170, 111, 41));
        pushButton_deleteFriend->setStyleSheet(QString::fromUtf8("background-color: #eee;\n"
"color: black;\n"
"border: 1px solid #555;\n"
"padding: 10px 20px;\n"
"font-size: 16px;\n"
"font-weight: bold;"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 250, 111, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: #eee;\n"
"color: black;\n"
"border: 1px solid #555;\n"
"padding: 10px 20px;\n"
"font-size: 16px;\n"
"font-weight: bold;"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 221, 31));
        label->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"color: #333;\n"
"background-color: #fff;\n"
"text-align: center;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(440, 80, 291, 301));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(310, 400, 431, 41));
        label_3->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"color: #333;\n"
"background-color: #fff;\n"
"text-align: center;"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_addFriend->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        pushButton_startChat->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257\344\274\232\350\257\235", nullptr));
        pushButton_sendFile->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_userWelcome->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_deleteFriend->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272\345\210\227\350\241\250:", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
