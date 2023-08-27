#include "registerui.h"
#include "ui_registerui.h"
#include <userinfo.h>
#include <login.h>

extern userinfo user;
extern QString hostip;
extern int hosthost;

registerui::registerui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerui)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket();
}

registerui::~registerui()
{
    delete ui;
}

void registerui::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text()!=""&& ui->lineEdit_2->text()!=""&& ui->lineEdit_3->text()!="")
    {
        if(ui->lineEdit_2->text()==ui->lineEdit_3->text())
        {
            tcpSocket->abort();//取消已有链接
            tcpSocket->connectToHost(hostip, hosthost);//链接服务器

            if(!tcpSocket->waitForConnected(30000))
            {
                QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
                this->close();
                user.islogin = false;
                Login *log = new Login();
                log->show();
            }
            else
            {//服务器连接成功
                QString loginmessage = QString("register##%1##%2").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text());
                tcpSocket->write(loginmessage.toUtf8());
                tcpSocket->flush();
                QString ip = tcpSocket->peerAddress().toString().section(":",3,3);
                int port = tcpSocket->peerPort();
                QString str = QString("[%1:%2]").arg(ip).arg(port);
                qDebug() << str ;
                connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                    QByteArray buffer = tcpSocket->readAll();
                    if(QString(buffer).section("##",0,0)==QString("register successed"))
                    {//注册成功
                        this->close();
                        Login *log = new Login();
                        log->show();
                    }
                    else if(QString(buffer).section("##",0,0)==QString("register error"))
                    {
                        if(QString(buffer).section("##",1,1)==QString("same_name"))
                        {
                            QMessageBox::warning(this, "Warning!", "昵称有重复", QMessageBox::Yes);
                            ui->lineEdit->clear();
                            ui->lineEdit->setFocus();
                        }
                    }
                });
            }
        }
        else
        {//两次密码不一样
            QMessageBox::warning(this, "Warning!", "两次密码不一样", QMessageBox::Yes);
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_2->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "用户名或密码不为空", QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
    }
}

void registerui::on_pushButton_clicked()
{
    this->close();
    Login *log = new Login();
    log->show();
}
