/********************************************************************************
** Form generated from reading UI file 'guiuserlist.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIUSERLIST_H
#define UI_GUIUSERLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiUserList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *GuiUserList)
    {
        if (GuiUserList->objectName().isEmpty())
            GuiUserList->setObjectName("GuiUserList");
        GuiUserList->resize(268, 453);
        gridLayout = new QGridLayout(GuiUserList);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        pushButton = new QPushButton(GuiUserList);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(26, 16777215));

        horizontalLayout->addWidget(pushButton);

        lineEdit = new QLineEdit(GuiUserList);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lineEdit);

        pushButton_2 = new QPushButton(GuiUserList);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        treeWidget = new QTreeWidget(GuiUserList);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(GuiUserList);

        QMetaObject::connectSlotsByName(GuiUserList);
    } // setupUi

    void retranslateUi(QWidget *GuiUserList)
    {
        GuiUserList->setWindowTitle(QCoreApplication::translate("GuiUserList", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("GuiUserList", "menu", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GuiUserList", "clean", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuiUserList: public Ui_GuiUserList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIUSERLIST_H
