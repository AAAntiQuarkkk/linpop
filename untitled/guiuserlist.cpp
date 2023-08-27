#include "guiuserlist.h"
#include "ui_guiuserlist.h"


GuiUserList::GuiUserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiUserList)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setRootIsDecorated(false);
    ui->treeWidget->setMouseTracking(true);

    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(userItemSelected(QTreeWidgetItem*,int)));
}

GuiUserList::~GuiUserList()
{
    delete ui;
}

void GuiUserList::addGuiUser() {
    QTreeWidgetItem *test;
    test = new QTreeWidgetItem;
    test->setText(0,"test");//这里可以格式化输出ip和用户名
    ui->treeWidget->addTopLevelItem(test);
}

void GuiUserList::userItemSelected(QTreeWidgetItem *item, int) {
    emit userselect();
    ui->treeWidget->clearSelection();
}
