#include "guichatlist.h"
#include "ui_guichatlist.h"

#include <QTreeWidgetItem>

GuiChatList::GuiChatList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiChatList)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setRootIsDecorated(false);
    ui->treeWidget->setMouseTracking(true);

    QTreeWidgetItem *test;
    test = new QTreeWidgetItem;
    test->setText(0,"test");
    ui->treeWidget->addTopLevelItem(test);
}

GuiChatList::~GuiChatList()
{
    delete ui;
}
