/********************************************************************************
** Form generated from reading UI file 'receivefile.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEFILE_H
#define UI_RECEIVEFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_receivefile
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *receivefile)
    {
        if (receivefile->objectName().isEmpty())
            receivefile->setObjectName("receivefile");
        receivefile->resize(400, 300);
        receivefile->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label = new QLabel(receivefile);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 40, 171, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sawasdee")});
        font.setPointSize(22);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(receivefile);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 140, 291, 31));
        label_2->setStyleSheet(QString::fromUtf8("font-family: Arial, sans-serif;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"color: #333;\n"
"background-color: #fff;\n"
"text-align: center;"));

        retranslateUi(receivefile);

        QMetaObject::connectSlotsByName(receivefile);
    } // setupUi

    void retranslateUi(QWidget *receivefile)
    {
        receivefile->setWindowTitle(QCoreApplication::translate("receivefile", "Form", nullptr));
        label->setText(QCoreApplication::translate("receivefile", "Receive Files", nullptr));
        label_2->setText(QCoreApplication::translate("receivefile", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class receivefile: public Ui_receivefile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEFILE_H
