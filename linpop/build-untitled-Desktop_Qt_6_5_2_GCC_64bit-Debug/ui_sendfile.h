/********************************************************************************
** Form generated from reading UI file 'sendfile.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILE_H
#define UI_SENDFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sendFile
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QWidget *sendFile)
    {
        if (sendFile->objectName().isEmpty())
            sendFile->setObjectName("sendFile");
        sendFile->resize(400, 285);
        sendFile->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(sendFile);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 170, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 12pt \"Candara\";"));
        pushButton_2 = new QPushButton(sendFile);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(220, 170, 91, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 12pt \"Candara\";"));
        label_2 = new QLabel(sendFile);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 30, 121, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sawasdee")});
        font.setPointSize(22);
        font.setBold(true);
        label_2->setFont(font);
        label = new QLabel(sendFile);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 100, 311, 31));
        label->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"color: #333;\n"
"background-color: #fff;\n"
"text-align: center;"));

        retranslateUi(sendFile);

        QMetaObject::connectSlotsByName(sendFile);
    } // setupUi

    void retranslateUi(QWidget *sendFile)
    {
        sendFile->setWindowTitle(QCoreApplication::translate("sendFile", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("sendFile", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("sendFile", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_2->setText(QCoreApplication::translate("sendFile", "Send File", nullptr));
        label->setText(QCoreApplication::translate("sendFile", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sendFile: public Ui_sendFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILE_H
