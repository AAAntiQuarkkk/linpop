#include "login.h"
#include "ui_login.h"
#include <QtNetwork>
#include <QMessageBox>
#include "mainwindow.h"
#include "register.h"
#include <userinfo.h>

extern userinfo user;
extern QString hostip;
extern int hosthost;

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("linpop");
    tcpSocket = new QTcpSocket();
}

Login::~Login()
{
    delete tcpSocket;
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(ui->lineEdit->text()!=""&& ui->lineEdit_2->text()!= "")
    {//账号密码不能为空
        tcpSocket->abort();//取消已有链接
        tcpSocket->connectToHost(hostip, hosthost);//链接服务器
        QString ip = tcpSocket->peerAddress().toString().section(":",3,3);
        int port = tcpSocket->peerPort();
        QString str = QString("[%1:%2]").arg(ip).arg(port);
        qDebug() << str ;
        if(!tcpSocket->waitForConnected(30000))
        {
            QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
        }
        else
        {//服务器连接成功
            QString loginmessage = QString("login##%1##%2").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text());
            tcpSocket->write(loginmessage.toUtf8());
            tcpSocket->flush();
            connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                QByteArray buffer = tcpSocket->readAll();
                if(QString(buffer).section("##",0,0)==QString("login successed"))
                {//登陆成功
                    user.id=QString(buffer).section("##",1,1).toInt();
                    user.name = ui->lineEdit->text();
                    user.islogin = true;
                    this->close();
                    MainWindow *mww = new MainWindow();
                    mww->show();
                }
                else if(QString(buffer).section("##",0,0)==QString("login error"))
                {
                    if(QString(buffer).section("##",1,1)==QString("no_user"))
                    {//用户不存在
                        QMessageBox::warning(this, "Warning!", "用户不存在", QMessageBox::Yes);
                        ui->lineEdit->clear();
                        ui->lineEdit_2->clear();
                        ui->lineEdit->setFocus();
                    }
                    else if(QString(buffer).section("##",1,1)==QString("errpwd"))
                    {
                        QMessageBox::warning(this, "Warning!", "密码错误", QMessageBox::Yes);
                        ui->lineEdit_2->clear();
                        ui->lineEdit_2->setFocus();
                    }
                }
            });
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "用户名或密码不为空", QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}

void Login::on_pushButton_2_clicked()
{
    this->close();
    registerui *reg = new registerui();
    reg->show();
}
