#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"


Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(btnClicked()));
    connect(this,SIGNAL(btnSignal(quint8)),this,SLOT(getStatus(quint8)));
}

Login::~Login()
{
    delete ui;
}

//开发过程中从测试用
void Login::btnClicked(){
    quint8 state = 1;
    emit btnSignal(state);
}

//根据服务器返回的状态判断登陆
void Login::getStatus(quint8 state){
    if(state) {
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    }
}
