#include "guichatwindow.h"
#include "ui_guichatwindow.h"

GuiChatWindow::GuiChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiChatWindow)
{
    ui->setupUi(this);
}

GuiChatWindow::~GuiChatWindow()
{
    delete ui;
}
