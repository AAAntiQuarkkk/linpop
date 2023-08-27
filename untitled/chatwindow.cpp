#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QListWidget>
#include <QVBoxLayout>

GuiChatWindow::GuiChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiChatWindow)
{
    ui->setupUi(this);
    setWindowTitle("“contactName”TODO");

    //建立可以滚动的list
    QWidget *scrollContent = new QWidget();
    ui->scrollArea->setWidget(scrollContent);
    QVBoxLayout *layout = new QVBoxLayout(scrollContent);
    QListWidget *mainListWidget = new QListWidget();
    layout->addWidget(mainListWidget);

    //从数据库导入聊天数据
    //int chatLogAmount = getChatLogAmount();           TODO
    int chatLogAmount = 50;
    bool isLeft = true;
    for (int i = 0; i < chatLogAmount; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText("chatLogTime \n chatLog");    // TODO: 替换为实际聊天记录内容
        if (isLeft) {
            item->setTextAlignment(Qt::AlignLeft);
        } else {
            item->setTextAlignment(Qt::AlignRight);
        }
        mainListWidget->addItem(item);
        isLeft = !isLeft;
    }
}

GuiChatWindow::~GuiChatWindow()
{
    delete ui;
}
