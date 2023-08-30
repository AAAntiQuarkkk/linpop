#include "receivefile.h"
#include "ui_receivefile.h"
#include "userinfo.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QApplication>
#include <QDebug>

extern userinfo otheruser;
extern userinfo user;
extern int hosthost;
extern QString hostip;
extern bool is_open_chatdialog;

ReceiveFile::ReceiveFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReceiveFile)
{
    ui->setupUi(this);
    serverInit();
}

ReceiveFile::~ReceiveFile()
{
    delete ui;

}

void ReceiveFile::serverInit() {
    m_tcpServerHelper = new TcpServerHelper(this);
    m_tcpServerHelper->listen(QHostAddress::Any,9988);
    connect(m_tcpServerHelper,SIGNAL(newSockDescriptor(qintptr)),this,SLOT(copeNewConnection(qintptr)));
}

void ReceiveFile::copeNewConnection(qintptr _sock) {
    //QTcpSocket *tcpSocket = m_tcpServer->nextPendingConnection();
    //qDebug()<<tcpSocket->peerAddress().toString();

    receiveThread = new ReceiveFileThread();
    fileThread = new QThread();
    receiveThread->moveToThread(fileThread);
    //tcpSocket->moveToThread(fileThread);
    connect(fileThread,&QThread::finished,fileThread,&QObject::deleteLater);
    connect(fileThread,&QThread::finished,receiveThread,&QObject::deleteLater);
    //connect(fileThread,&QThread::finished,tcpSocket,&QObject::deleteLater);
    connect(this,SIGNAL(startThread(qintptr)),receiveThread,SLOT(initThread(qintptr)));
    connect(receiveThread,SIGNAL(refFileInfo(QString,QString,qint64,qint64)),this,SLOT(doRefFileInfo(QString,QString,qint64,qint64)));
    connect(receiveThread,SIGNAL(sigOver(QString,bool)),this,SLOT(doSigOver(QString,bool)));

    fileThread->start();
    emit startThread(_sock);
}

bool ReceiveFile::getReceiveFirst(QString name) {
    if(m_ListRecFirst.length() == 0)
        return true;

    for (int i=0;i<m_ListRecFirst.length(); ++i) {
        if(name == m_ListRecFirst.at(i)){
            return false;
        }
    }
    return true;
}

ProcessBarReceive* ReceiveFile::getProcessBarReceive(QString name) {
    QMap<QString,ProcessBarReceive*>::iterator itor;
    for(itor = m_mapReceive.begin();itor != m_mapReceive.end();++itor) {
        if(itor.key() == name) {
            return itor.value();
        }
    }
}

QThread* ReceiveFile::getReceiveFileThread(QString name) {
    QMap<QString,QThread*>::iterator itor;
    for(itor = m_mapTcpServer.begin(); itor != m_mapTcpServer.end(); ++itor) {
        if(itor.key() == name) {
            return itor.value();
        }
    }
}

void ReceiveFile::doRefFileInfo(QString name, QString clientIP, qint64 size, qint64 received_size) {
    qApp->processEvents();

    if(getReceiveFirst(name)){
        ProcessBarReceive* form = new ProcessBarReceive(name.section("##",0,0),clientIP,size);
        ui->verticalLayout_2->addWidget(form);
        m_ListRecFirst.append(name);
        m_mapReceive.insert(name,form);
        m_mapTcpServer.insert(name,fileThread);//同样有风险的操作
    }
    getProcessBarReceive(name)->updateProcess(received_size);
}

void ReceiveFile::doSigOver(QString fileName,bool over) {
    qDebug()<<"doSigOver"<<fileName;
    QThread* thread = getReceiveFileThread(fileName);
    thread->exit();
    thread->wait();
    thread->deleteLater();
    qDebug()<<"doSigOver"<<fileName;
    getProcessBarReceive(fileName)->setStatus(over);
}

void ReceiveFile::closeEvent(QCloseEvent *event)
{
    tcpSocket = new QTcpSocket();
    tcpSocket->abort();//取消已有链接
    tcpSocket->connectToHost(hostip, hosthost);//链接服务器
    qDebug()<<"close";
    if(!tcpSocket->waitForConnected(30000))
    {
        this->close();
        user.islogin = false;
    }
    else
    {//服务器连接成功
        QString loginmessage = QString("send_file_ok##%1##%2").arg(user.id).arg(otheruser.name);
        qDebug()<<loginmessage;
        tcpSocket->write(loginmessage.toUtf8());
        tcpSocket->flush();
        is_open_chatdialog = false;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}
