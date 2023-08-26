#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "guichatlist.h"
#include "guiuserlist.h"
#include "guichatwindow.h"

QString hostip = "127.0.0.1";
int hosthost = 8888;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *actProfile = new QAction(tr("资料"),this);
    ui->toolBar->addAction(actProfile);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
    guiuserlist = new GuiUserList();
    guichatlist = new GuiChatList();
    ui->tabWidget->insertTab(0,guiuserlist,tr("好友"));
    ui->tabWidget->insertTab(1,guichatlist,tr("会话"));

    connect(guiuserlist,SIGNAL(userselect()),this,SLOT(showChat()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showChat() {
    GuiChatWindow *chatWindow = new GuiChatWindow();
    chatWindow->show();
}
