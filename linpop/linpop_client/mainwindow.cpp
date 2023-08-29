#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <login.h>
#include <sendfile.h>
#include <receivefile.h>
#include <QHBoxLayout>

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
    setWindowTitle("Linpop");
    ui->label->setStyleSheet("background-color: transparent;");
    ui->label_3->setStyleSheet("background-color: transparent;");
    ui->label_userWelcome->setStyleSheet("background-color: transparent;");
    ui->label_userWelcome->setStyleSheet("font-size: 16px; font-weight: bold;");
    ui->label_userWelcome->setText("欢迎,"+user.name);

    //显示Tips用
    ui->pushButton_addFriend->installEventFilter(this);
    ui->pushButton_deleteFriend->installEventFilter(this);
    ui->pushButton->installEventFilter(this);
    ui->pushButton_sendFile->installEventFilter(this);
    //ui->pushButton_quit->installEventFilter(this);

    timer = new QTimer();
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(Createdfriendlist()));
    pShakeAnimation = new QPropertyAnimation(this,"pos");
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
        //ui->pushButton_startChat->setEnabled(true);
        ui->pushButton_sendFile->setEnabled(true);

//        ui->pushButton_startchat->setEnabled(true);
//        ui->pushButton_sendmessage->setEnabled(true);
//        ui->pushButton_receivefile->setEnabled(true);
//        ui->pushButton_sendfile->setEnabled(true);
    }
    else if(friendlist.length()==0 && !is_open_chatdialog)
    {
        //ui->pushButton_startChat->setEnabled(false);
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
                                    addFriendList(friendname,"在线，请求发送文件，有新消息");
                                    QPoint pos = this->pos();
                                      //动画还没有结束就先立马停止，防止用户不停的点击
                                      if(pShakeAnimation->state() == QPropertyAnimation::Running)
                                        {
                                          pShakeAnimation->stop();
                                        }
                                      pShakeAnimation->setDuration(600);
                                      pShakeAnimation->setStartValue(pos);

                                      int offset =0;
                                      double dOffset = (double)1/30;
                                      double dIndex =dOffset;
                                      for(int i=1;i<30;i++){
                                          offset = i%2==0?-10:10;
                                          dIndex += dOffset;
                                          pShakeAnimation->setKeyValueAt(dIndex,pos + QPoint((int)offset,(int)offset));
                                        }

                                      pShakeAnimation->setEndValue(pos);
                                      pShakeAnimation->start();
                                }
                                else
                                {
                                    addFriendList(friendname,"在线，有新消息");
                                    QPoint pos = this->pos();
                                      if(pShakeAnimation->state() == QPropertyAnimation::Running)
                                        {
                                          pShakeAnimation->stop();
                                        }
                                      pShakeAnimation->setDuration(600);
                                      pShakeAnimation->setStartValue(pos);

                                      int offset =0;
                                      double dOffset = (double)1/30;
                                      double dIndex =dOffset;
                                      for(int i=1;i<30;i++){
                                          offset = i%2==0?-10:10;
                                          dIndex += dOffset;
                                          pShakeAnimation->setKeyValueAt(dIndex,pos + QPoint((int)offset,(int)offset));
                                        }

                                      pShakeAnimation->setEndValue(pos);
                                      pShakeAnimation->start();
                                }
                            }
                            else
                            {
                                if(friendsendfile == '1')
                                {
                                    addFriendList(friendname,"在线，请求发送文件");
                                }
                                else
                                {
                                    addFriendList(friendname,"在线");
                                }
                            }
                        }
                        else
                        {
                            if(friendsendmassage == '1')
                            {
                                addFriendList(friendname,"离线，有新消息");
                            }
                            else
                            {
                                addFriendList(friendname,"离线");
                            }
                        }
                    }

                    if(!is_open_chatdialog)
                    {
                        //ui->pushButton_startChat->setEnabled(true);
                        //ui->pushButton_receivefile->setEnabled(true);
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
                    QListWidgetItem *item = new QListWidgetItem(tr("暂无已添加好友"));
                    item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 设置成不能点击
                    ui->listWidget_friendList->insertItem(0, item);
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

void MainWindow::addFriendList(QString friendname, QString friendstatuetext)
{
    // 构造好友列表项的文本，包括好友名字和状态
    QString listItemText = QString("%1\n%2").arg(friendname).arg(friendstatuetext);
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(listItemText);
    ui->listWidget_friendList->addItem(item);
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
                        QMessageBox::warning(this, "Warning!", "添加失败，该用户不存在", QMessageBox::Yes);
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

/*
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
*/

void MainWindow::on_listWidget_friendList_itemDoubleClicked(QListWidgetItem *item) //双击开启会话
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
            {//开启会话
                otheruser.id = QString(buffer).section("##",1,1).toInt();
                otheruser.name = friendname;
                //ui->pushButton_startChat->setEnabled(false);
                GuiChatWindow *cht = new GuiChatWindow();
                cht->show();
            }
        });
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

//下线
void MainWindow::closeEvent(QCloseEvent *event)
{
    timer->stop();
    tcpSocket = new QTcpSocket();
    tcpSocket->abort();//取消已有链接
    tcpSocket->connectToHost(hostip, hosthost);//链接服务器
    if(!tcpSocket->waitForConnected(30000))
    {
        this->close();
        user.islogin = false;
    }
    else
    {//服务器连接成功
        QString message = QString("logout##%1").arg(user.id);
        tcpSocket->write(message.toUtf8());
        tcpSocket->flush();
        QMessageBox::warning(this, "Success", "下线成功", QMessageBox::Yes);
    }
}

/*
void MainWindow::on_pushButton_quit_clicked()
{//退出登录
    this->close();
    user.islogin = false;
    Login *log = new Login();
    log->show();
}
*/

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->pushButton_addFriend)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->label_3->setText("Tips: 点击添加联系人");
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_3->setText("Tips:");
        }
    }else if(obj == ui->pushButton_deleteFriend){
        if (event->type() == QEvent::Enter)
        {
            ui->label_3->setText("Tips: 选择一个联系人，点击删除");
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_3->setText("Tips:");
        }
    }else if(obj == ui->pushButton){
        if (event->type() == QEvent::Enter)
        {
            ui->label_3->setText("Tips: 当存在联系人想要发送文件时，点击进行接收");
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_3->setText("Tips:");
        }
    }else if(obj == ui->pushButton_sendFile){
        if (event->type() == QEvent::Enter)
        {
            ui->label_3->setText("Tips: 选择一个联系人，点击发送文件");
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_3->setText("Tips:");
        }
    }/*else if(obj == ui->pushButton_quit){
        if (event->type() == QEvent::Enter)
        {
            ui->label_3->setText("Tips: 退出登录，切换用户");
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_3->setText("");
        }
    }*/
    return QMainWindow::eventFilter(obj, event);
}
