#include "sendfile.h"
#include "ui_sendfile.h"
#include "userinfo.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QDebug>

extern userinfo user;
extern userinfo otheruser;
extern bool is_open_chatdialog;
extern int hosthost;
extern QString hostip;

SendFile::SendFile(QString clientIP, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SendFile)
{
    ui->setupUi(this);
    ui->lineEdit->setText(clientIP);
}

SendFile::~SendFile()
{
    delete ui;
}


ProcessBarSend* SendFile::getProcessBarSend(QString fileID) {
    QMap<QString,ProcessBarSend*>::iterator itor;
    for(itor = m_mapSend.begin();itor != m_mapSend.end();++itor) {
        if(itor.key() == fileID) {
            return itor.value();
        }
    }
}

QThread* SendFile::getSendFileThread(QString fileID) {
    QMap<QString,QThread*>::iterator itor;
    for(itor = m_mapClient.begin();itor != m_mapClient.end();++itor) {
        if(itor.key() == fileID) {
            return itor.value();
        }
    }
}

void SendFile::doSigConnect(bool connected) {
    if(!connected) {
        fileThread->exit();
        fileThread->wait();
        fileThread->deleteLater();
        QMessageBox::information(this,"错误！","无法连接到用户");
    }
}

void SendFile::doRefFileInfo(QString name,qint64 receivedSize) {
    qDebug()<<"sendFile"<<name;
    qApp->processEvents();
    getProcessBarSend(name)->updateProcess(receivedSize);
}

void SendFile::doSigOver(QString name,bool over) {
    QThread* thread = getSendFileThread(name);
    thread->exit();
    thread->wait();
    thread->deleteLater();
    getProcessBarSend(name)->setStatus(over);
}

void SendFile::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"选择文件","../");
    //若文件路径无效，则提示
    if(filePath.isEmpty())
    {
        QMessageBox::information(this,"Error: ",filePath+"文件路径无效");
        return;
    }
    /*
    //获取发送端IP
    QString hostIp;
    QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, AddressList){
        if(address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress::Null &&
            address != QHostAddress::LocalHost){
            if (address.toString().contains("127.0.")){
                continue;
            }
            hostIp = address.toString();
            break;
        }
    }
    */
    //获取时间
    QString currentDateTime = (QDateTime::currentDateTime()).toString("MMddhhmmsszzz");

    QFileInfo info(filePath);

    QString targetIp = ui->lineEdit->text();
    ushort port = 9988;
    QString fileID = filePath+"##"+currentDateTime;

    sendThread = new SendFileThread();
    fileThread = new QThread();
    sendThread->moveToThread(fileThread);
    connect(fileThread,&QThread::finished,fileThread,&QObject::deleteLater);
    connect(fileThread,&QThread::finished,sendThread,&QObject::deleteLater);
    connect(this,SIGNAL(startThread(ushort,QString,QString)),sendThread,SLOT(initThread(ushort,QString,QString)));
    connect(sendThread,SIGNAL(sigConnect(bool)),this,SLOT(doSigConnect(bool)));
    connect(sendThread,SIGNAL(refFileInfo(QString,qint64)),this,SLOT(doRefFileInfo(QString,qint64)));
    connect(sendThread,SIGNAL(sigOver(QString,bool)),this,SLOT(doSigOver(QString,bool)));

    connect(sendThread,&SendFileThread::sigConnect,this,[=](bool connected){
        qDebug()<<"测试"<<connected;
        if(connected) {
            ProcessBarSend* processBarSend = new ProcessBarSend(info.fileName(),info.size());
            ui->verticalLayout_2->addWidget(processBarSend);
            qDebug()<<"filePath:"<<info.fileName()<<":"<<info.size();

            /*字典，<处理后的文件名，线程>，*/
            m_mapClient.insert(info.fileName()+"##"+currentDateTime,fileThread);//有风险的操作，fileThread可能会改变
            /*字典，<处理后的文件名，传输界面>，*/
            m_mapSend.insert(info.fileName()+"##"+currentDateTime,processBarSend);
        }
    });

    fileThread->start();
    emit startThread(port,targetIp,fileID);
}

void SendFile::closeEvent(QCloseEvent *event)
{
    tcpSocket = new QTcpSocket();
    tcpSocket->abort();//取消已有链接
    tcpSocket->connectToHost(hostip, hosthost);//链接服务器
    qDebug()<<"close!";
    if(!tcpSocket->waitForConnected(30000))
    {
        this->close();
        user.islogin = false;
    }
    else
    {//服务器连接成功
        QString loginmessage = QString("send_file_miss##%1##%2").arg(user.id).arg(otheruser.name);
        qDebug()<<loginmessage;
        tcpSocket->write(loginmessage.toUtf8());
        tcpSocket->flush();
        is_open_chatdialog = false;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

