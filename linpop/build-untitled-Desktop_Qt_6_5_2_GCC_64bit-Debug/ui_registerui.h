/********************************************************************************
** Form generated from reading UI file 'registerui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERUI_H
#define UI_REGISTERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerui
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *registerui)
    {
        if (registerui->objectName().isEmpty())
            registerui->setObjectName("registerui");
        registerui->resize(630, 320);
        registerui->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(registerui);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(420, 84, 171, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 10pt \"Candara\";"));
        lineEdit_2 = new QLineEdit(registerui);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(420, 134, 171, 31));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 10pt \"Candara\";"));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        lineEdit_3 = new QLineEdit(registerui);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(420, 184, 171, 31));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);\n"
"border:1px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 10pt \"Candara\";"));
        lineEdit_3->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(registerui);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 240, 89, 25));
        pushButton->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 12pt \"Candara\";"));
        pushButton_2 = new QPushButton(registerui);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(500, 240, 89, 25));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:2px groove gray;border-radius:\n"
"7px;padding:2px 4px;\n"
"font: 12pt \"Candara\";"));
        label = new QLabel(registerui);
        label->setObjectName("label");
        label->setGeometry(QRect(340, 90, 67, 17));
        QFont font;
        font.setFamilies({QString::fromUtf8("Umpush")});
        font.setPointSize(13);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(registerui);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 140, 67, 17));
        label_2->setFont(font);
        label_3 = new QLabel(registerui);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(340, 190, 71, 17));
        label_3->setFont(font);
        label_4 = new QLabel(registerui);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(420, 20, 111, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Sawasdee")});
        font1.setPointSize(22);
        font1.setBold(true);
        label_4->setFont(font1);
        label_5 = new QLabel(registerui);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 40, 291, 221));

        retranslateUi(registerui);

        QMetaObject::connectSlotsByName(registerui);
    } // setupUi

    void retranslateUi(QWidget *registerui)
    {
        registerui->setWindowTitle(QCoreApplication::translate("registerui", "Form", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("registerui", "Enter your username", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("registerui", "Enter your password", nullptr));
        lineEdit_3->setText(QString());
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("registerui", "Confirm your password", nullptr));
        pushButton->setText(QCoreApplication::translate("registerui", "\350\277\224\345\233\236", nullptr));
        pushButton_2->setText(QCoreApplication::translate("registerui", "\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("registerui", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("registerui", "\345\257\206\347\240\201:", nullptr));
        label_3->setText(QCoreApplication::translate("registerui", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        label_4->setText(QCoreApplication::translate("registerui", "Register", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class registerui: public Ui_registerui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERUI_H
