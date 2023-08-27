#include "guichatwindow.h"
#include "ui_guichatwindow.h"

#include <mainwindow.h>
#include <login.h>

extern userinfo user;
extern bool is_open_chatdialog;
extern userinfo otheruser;
extern QString hostip;
extern int hosthost;

GuiChatWindow::GuiChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiChatWindow)
{
    ui->setupUi(this);
//    ui->label_title->setText("您正在与"+otheruser.name+"进行对话");
    is_open_chatdialog = true;
    tcpSocket = new QTcpSocket();
    timer = new QTimer();

    qDebug()<<otheruser.id<<otheruser.name;
    connect(timer,SIGNAL(timeout()),this,SLOT(getchathistory()));
    timer->start(500);
}

GuiChatWindow::~GuiChatWindow()
{
    is_open_chatdialog = false;
    timer->stop();
    delete ui;
}

void GuiChatWindow::on_pushButton_sendMsg_clicked()
{//发送消息
    if(ui->lineEdit_msgEdit->text()!="")
    {//消息不为空
        tcpSocket->abort();//取消已有链接
        tcpSocket->connectToHost(hostip, hosthost);//链接服务器
        QString ip = tcpSocket->peerAddress().toString().section(":",3,3);
        int port = tcpSocket->peerPort();
        QString str = QString("[%1:%2]").arg(ip).arg(port);
        qDebug() << str ;
        if(!tcpSocket->waitForConnected(30000))
        {
            QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
            this->close();
            user.islogin = false;
            Login *login = new Login();
            login->show();
        }
        else
        {//服务器连接成功
            //第一个是时间，第二个发送的ID，第三个是接受的ID，第四个是内容
            QString nowstr = QDateTime::currentDateTime().currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
            QString message = QString("chat_send##%1##%2##%3##%4").arg(nowstr).arg(user.id).arg(otheruser.id).arg(ui->lineEdit_msgEdit->text());
            tcpSocket->write(message.toUtf8());
            tcpSocket->flush();
            ui->lineEdit_msgEdit->clear();
        }
    }
    else
    {//空消息
        QMessageBox::warning(this, "Warning!", "不能发送空消息", QMessageBox::Yes);
    }
}

void GuiChatWindow::on_pushButton_close_clicked()
{
    qDebug()<<is_open_chatdialog;

    is_open_chatdialog = false;
    qDebug()<<is_open_chatdialog;
    this->close();
    timer->stop();
}

void GuiChatWindow::getchathistory()
{
    tcpSocket->abort();//取消已有链接
    tcpSocket->connectToHost(hostip, hosthost);//链接服务器

    if(!tcpSocket->waitForConnected(30000))
    {
        QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
        this->close();
    }
    else
    {//服务器连接成功
        QString message = QString("chat_history##%1##%2").arg(user.id).arg(otheruser.id);
        tcpSocket->write(message.toUtf8());
        tcpSocket->flush();
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            QByteArray buffer = tcpSocket->readAll();
            if(QString(buffer).section("##",0,0)==QString("chat_history_ok"))
            {
                QString chatshow = "";
                int num = QString(buffer).section("##",1,1).toInt();
                for(int rownum = 0;rownum < num ;rownum++)
                {
                    QDateTime time = QDateTime::fromString( QString(buffer).section("##",rownum*3+2,rownum*3+2),"yyyy-MM-dd hh:mm:ss.zzz");
                    qDebug()<<time.toString();
                    QString timeshow = time.toString("MM-dd hh:mm:ss");
                    qDebug()<<timeshow;
                    QString idshow = "";
                    if(QString(buffer).section("##",rownum*3+3,rownum*3+3).toInt()==user.id)
                    {//我自己发送的消息
                        idshow = " 我：";
                    }
                    else
                    {
                        idshow =" "+ otheruser.name + "：";
                    }
                    chatshow = "("+timeshow+")" + idshow + QString(buffer).section("##",rownum*3+4,rownum*3+4) +"\n" + chatshow;
                }
                ui->textBrowser_msgShow->setText(chatshow);
            }
            else if(QString(buffer).section("##",0,0)==QString("chat_history_error"))
            {
                ui->textBrowser_msgShow->setText("无消息记录");
            }
        });
    }
}

void GuiChatWindow::closeEvent(QCloseEvent *event)
{
    is_open_chatdialog = false;
    timer->stop();
}
