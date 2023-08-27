#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Login.h>
#include <sendfile.h>
#include <receivefile.h>

extern userinfo user;
userinfo otheruser;
QList <QString> friendlist;
QList <QString> friendiplist;
QList <QString> friendstatuelist;//1在线
QList <QString> friendsendmassagelist;
QList <QString> friendsendfilelist;

//QString hostip = "192.168.72.128";
QString hostip = "127.0.0.1";

int hosthost = 8888;

bool is_open_chatdialog;
int onlinenum = -1;
int listnum = -1;
int sendmassagenum = -1;
int sendfilenum = -1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_userWelcome->setText("您好，"+user.name);

    timer = new QTimer();
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(Createdfriendlist()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showChat(){}

void MainWindow::Createdfriendlist()
{
{
    if(is_open_chatdialog)
    {
//        ui->pushButton_startChat->setEnabled(false);
//        ui->pushButton_sendFile->setEnabled(false);

//        ui->pushButton_startchat->setEnabled(false);
//        ui->pushButton_sendmessage->setEnabled(false);
//        ui->pushButton_receivefile->setEnabled(false);
//        ui->pushButton_sendfile->setEnabled(false);
    }
    else if(friendlist.length()!=0 && !is_open_chatdialog)
    {
        ui->pushButton_startChat->setEnabled(true);
        ui->pushButton_sendFile->setEnabled(true);

//        ui->pushButton_startchat->setEnabled(true);
//        ui->pushButton_sendmessage->setEnabled(true);
//        ui->pushButton_receivefile->setEnabled(true);
//        ui->pushButton_sendfile->setEnabled(true);
    }
    else if(friendlist.length()==0 && !is_open_chatdialog)
    {
        ui->pushButton_startChat->setEnabled(false);
        ui->pushButton_sendFile->setEnabled(false);

//        ui->pushButton_startchat->setEnabled(false);
//        ui->pushButton_sendmessage->setEnabled(true);
//        ui->pushButton_receivefile->setEnabled(false);
//        ui->pushButton_sendfile->setEnabled(false);
    }

    tcpSocket = new QTcpSocket();
    tcpSocket->abort();//取消已有链接
    tcpSocket->connectToHost(hostip,hosthost);//链接服务器
    if(!tcpSocket->waitForConnected(3000))
    {
        QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
        this->close();
        user.islogin = false;
        Login *login = new Login();
        login->show();
    }
    else
    {//服务器连接成功
        QString message = QString("getfriendlist##%1").arg(user.id);
        tcpSocket->write(message.toUtf8());
        tcpSocket->flush();
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            QByteArray buffer = tcpSocket->readAll();
            if(QString(buffer).section("##",0,0)==QString("getfriendlist_ok"))
            {
                int newnum = QString(buffer).section("##",1,1).toInt();
                int newonlinenum = QString(buffer).section("##",2,2).toInt();
                int newsendmassagenum = QString(buffer).section("##",3,3).toInt();
                int newsendfilenum = QString(buffer).section("##",4,4).toInt();
                qDebug()<<newnum<<newonlinenum<<newsendfilenum<<sendfilenum<<onlinenum<<listnum;
                if(newsendmassagenum!= sendmassagenum ||sendfilenum!=newsendfilenum || newonlinenum != onlinenum || onlinenum == -1 ||sendmassagenum==-1|| listnum==-1|| newnum!= listnum || sendfilenum == -1)
                {
                    onlinenum = newonlinenum;
                    listnum = newnum;
                    sendfilenum = newsendfilenum;
                    sendmassagenum = newsendmassagenum;

                    ui->listWidget_friendList->clear();
                    friendlist.clear();
                    friendiplist.clear();
                    friendstatuelist.clear();
                    friendsendmassagelist.clear();
                    friendsendfilelist.clear();

                    for(int rownum = 0;rownum < newnum ;rownum++)
                    {
                        QString friendname = QString(buffer).section("##",5+rownum*5,5+rownum*5);
                        QString friendstatue = QString(buffer).section("##",6+rownum*5,6+rownum*5);
                        QString friendip = QString(buffer).section("##",7+rownum*5,7+rownum*5);
                        QString friendsendmassage = QString(buffer).section("##",8+rownum*5,8+rownum*5);
                        QString friendsendfile = QString(buffer).section("##",9+rownum*5,9+rownum*5);
                        friendlist.append(friendname);
                        friendstatuelist.append(friendstatue);
                        friendiplist.append(friendip);
                        friendsendmassagelist.append(friendsendmassage);
                        friendsendfilelist.append(friendsendfile);

                        if(friendstatue=='1')
                        {
                            if(friendsendmassage == '1')
                            {
                                if(friendsendfile == '1')
                                {
                                    ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(在线，想给您发文件，有新消息)").toUtf8()));
                                }
                                else
                                {
                                    ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(在线，有新消息)").toUtf8()));
                                }
                            }
                            else
                            {
                                if(friendsendfile == '1')
                                {
                                    ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(在线，想给您发文件)").toUtf8()));
                                }
                                else
                                {
                                    ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(在线)").toUtf8()));
                                }
                            }
                        }
                        else
                        {
                            if(friendsendmassage == '1')
                            {
                                ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(不在线，有新消息)").toUtf8()));
                            }
                            else
                            {
                                ui->listWidget_friendList->insertItem(rownum,tr((friendname + "(不在线)").toUtf8()));
                            }
                        }
                    }

                    //删除还没弄

//                    ui->pushButton_deletepeople->setEnabled(true);
                    if(!is_open_chatdialog)
                    {
                        ui->pushButton_startChat->setEnabled(true);
//                        ui->pushButton_receivefile->setEnabled(true);
                        ui->pushButton_sendFile->setEnabled(true);
                    }
                }
            }
            else if(QString(buffer).section("##",0,0)==QString("getfriendlist_error"))
            {
                if( listnum == -1 || 0!= listnum)
                {
                    listnum = 0;
                    ui->listWidget_friendList->clear();
                    ui->listWidget_friendList->insertItem(0,tr("您没有朋友"));
                }
//                ui->pushButton_startchat->setEnabled(false);
//                ui->pushButton_deletepeople->setEnabled(false);
//                ui->pushButton_receivefile->setEnabled(false);
//                ui->pushButton_sendfile->setEnabled(false);
            }
        });
    }
}
}



void MainWindow::on_pushButton_addFriend_clicked()
{
    bool ok;
    QString addfriendname = QInputDialog::getText(this, tr("增添联系人"),tr("请输入对方昵称"), QLineEdit::Normal,0,&ok);
    if (ok && !addfriendname.isEmpty())
    {
        if(addfriendname != user.name)
        {
            tcpSocket = new QTcpSocket();
            tcpSocket->abort();//取消已有链接
            tcpSocket->connectToHost(hostip, hosthost);//链接服务器
            if(!tcpSocket->waitForConnected(30000))
            {
                //服务器连接失败，回到登录界面
                QMessageBox::warning(this, "Warning!", "网络错误", QMessageBox::Yes);
                this->close();
                user.islogin = false;
                Login *login = new Login();
                login->show();
            }
            else
            {//服务器连接成功
                QString message = QString("add_friend##%1##%2").arg(user.id).arg(addfriendname);

                tcpSocket->write(message.toUtf8());
                tcpSocket->flush();

                connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                    QByteArray buffer = tcpSocket->readAll();
                    qDebug() << QString(buffer);
                    if( QString(buffer).section("##",0,0) == QString("add_friend_ok"))
                    {//加朋友
                        onlinenum = -1;
                    }
                    else if( QString(buffer).section("##",0,0) == QString("add_friend_error"))
                    {
                        QMessageBox::warning(this, "Warning!", "查无此人", QMessageBox::Yes);
                    }
                });
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "不能添加自己", QMessageBox::Yes);
        }
    }
}


void MainWindow::on_pushButton_startChat_clicked()
{
    if(ui->listWidget_friendList->currentRow()!=-1)
    {
        QString friendname = friendlist.at(ui->listWidget_friendList->currentRow());

        tcpSocket = new QTcpSocket();
        tcpSocket->abort();//取消已有链接
        tcpSocket->connectToHost(hostip, hosthost);//链接服务器
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
            QString message = QString("wantsendmessage##%1##%2").arg(user.id).arg(friendname);
            tcpSocket->write(message.toUtf8());
            tcpSocket->flush();

            connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                QByteArray buffer = tcpSocket->readAll();
                if( QString(buffer).section("##",0,0) == QString("wantsendmessage_ok"))
                {//查有此人，可以发消息
                    otheruser.id = QString(buffer).section("##",1,1).toInt();
                    otheruser.name = friendname;
//                    ui->pushButton_startChat->setEnabled(false);
                    GuiChatWindow *cht = new GuiChatWindow();
                    cht->show();
                }
            });
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
    }
}

void MainWindow::on_pushButton_deleteFriend_clicked()
{
    if(ui->listWidget_friendList->currentRow()!=-1)
    {
        QString friendname = friendlist.at(ui->listWidget_friendList->currentRow());
        QString dlgTitle="提示";
        QString strInfo="您将删除好友："+friendname+"\n确定吗？";
        QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton;
        QMessageBox::StandardButton result;
        result=QMessageBox::question(this, dlgTitle, strInfo,QMessageBox::Cancel|QMessageBox::Yes,defaultBtn);
        if (result==QMessageBox::Yes)
        {

            tcpSocket = new QTcpSocket();
            tcpSocket->abort();//取消已有链接
            tcpSocket->connectToHost(hostip, hosthost);//链接服务器
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
                QString message = QString("delete_friend##%1##%2").arg(user.id).arg(friendname);
                tcpSocket->write(message.toUtf8());
                tcpSocket->flush();

                connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                    QByteArray buffer = tcpSocket->readAll();
                    if( QString(buffer).section("##",0,0) == QString("delete_friend_ok"))
                    {
                        Createdfriendlist();
                    }
                });
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
    }
}



void MainWindow::on_pushButton_sendFile_clicked()
{
    if( ui->listWidget_friendList->currentRow() != -1)
    {
        if(friendstatuelist.at(ui->listWidget_friendList->currentRow()) == "1")
        {
            QString friendname = friendlist.at(ui->listWidget_friendList->currentRow());
            qDebug() << friendname;
            otheruser.name = friendname;
            otheruser.ip = friendiplist.at(ui->listWidget_friendList->currentRow());

            tcpSocket = new QTcpSocket();
            tcpSocket->abort();//取消已有链接
            tcpSocket->connectToHost(hostip, hosthost);//链接服务器
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
                QString message = QString("want_send_file##%1##%2").arg(user.id).arg(friendname);
                tcpSocket->write(message.toUtf8());
                tcpSocket->flush();
            }
                sendFile *sf = new sendFile();
                sf->show();
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "联系人未在线无法发送文件", QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
    }
}



void MainWindow::on_pushButton_clicked()
{
    if( ui->listWidget_friendList->currentRow() != -1)
    {
        if(friendsendfilelist.at(ui->listWidget_friendList->currentRow()) == "1")
        {
            QString friendname = friendlist.at(ui->listWidget_friendList->currentRow());
            otheruser.name = friendname;
            otheruser.ip = friendiplist.at(ui->listWidget_friendList->currentRow());
            receivefile *rf = new receivefile();
            rf->show();
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "该联系人未给您发送文件", QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "您未选择联系人", QMessageBox::Yes);
    }
}
