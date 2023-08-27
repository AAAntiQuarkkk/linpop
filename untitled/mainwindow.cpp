#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatwindow.h"
#include "addfriendship.h"
#include <QListWidget>
#include <QVBoxLayout>

QString hostip = "127.0.0.1";
int hosthost = 8888;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //QString myName = getMyName();         TODO
    QString myName = "myName:TODO";

    ui->setupUi(this);
    setWindowTitle("linpop");
    QAction *actProfile = new QAction(myName,this);
    ui->toolBar->addAction(actProfile);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);

    //建立可以滚动的list
    QWidget *scrollContent = new QWidget();
    ui->scrollArea->setWidget(scrollContent);
    QVBoxLayout *layout = new QVBoxLayout(scrollContent);
    QListWidget *mainListWidget = new QListWidget();
    layout->addWidget(mainListWidget);

    //从数据库导入好友数据
    //int contactAmount = getContactAmount();           TODO
    int contactAmount = 100;
    for (int i = 0; i < contactAmount; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText("friendName " + QString::number(i) + "\n"+"status: online_or_offline");   //TODO
        mainListWidget->addItem(item);
    }

    connect(mainListWidget, &QListWidget::itemClicked, this, &MainWindow::friendItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::friendItemClicked()    //TODO
{
    // 本函数需要添加传递一些参数
    showChat();
}

void MainWindow::showChat()     //TODO，本函数需要添加传递一些参数
{
    GuiChatWindow *chatWindow = new GuiChatWindow();
    chatWindow->show();
}

void MainWindow::on_pushButton_clicked()
{
    addfriendship *addFriendshipWindow = new addfriendship();
    addFriendshipWindow->show();
}

