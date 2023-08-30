#include "sendfilethread.h"

#include <QHostAddress>
#include <QApplication>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

SendFileThread::SendFileThread(QObject*) {

}

SendFileThread::~SendFileThread() {
    m_tcpSocket->disconnectFromHost();
}

void SendFileThread::initThread(ushort port,QString ip,QString fileID) {
    m_ip = new QString();
    m_port = (ushort*)malloc(sizeof(ushort));
    m_filePath = new QString();
    m_time = new QString();
    m_fileName = new QString();
    m_fileSize = (qint64*)malloc(sizeof(qint64));
    m_sendSize = (qint64*)malloc(sizeof(qint64));
    m_filePath = new QString();
    m_fileNameTime = new QString();


    *m_ip = ip;
    *m_port = port;
    *m_filePath = fileID.section("##",0,0);
    *m_time = fileID.section("##",1,1);
    m_sendOk = false;

    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(copeDisconnect()));
    connect(m_tcpSocket,SIGNAL(connected()),this,SLOT(copeConnect()));
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(copeRead()));
    m_tcpSocket->connectToHost(QHostAddress(*m_ip),*m_port);
    //等待连接
    bool connectSig = m_tcpSocket->waitForConnected(5000);
    emit sigConnect(connectSig);
    if(!connectSig) {
        this->deleteLater();
    }
    else {
        QFileInfo info(*m_filePath);
        *m_fileName = info.fileName();
        *m_fileSize = info.size();
        QString msg = QString("%1##%2").arg(*m_fileName).arg(*m_fileSize);
        qDebug()<<"head:"<<msg;
        m_tcpSocket->write(msg.toUtf8().data(),1024);
        QApplication::processEvents();
        *m_fileNameTime = *m_fileName + "##"+ *m_time;
        sendFile();
    }
}

void SendFileThread::copeDisconnect() {
    if(*m_sendSize != *m_fileSize){
        m_stop = true;//中途中断
        qDebug()<<"中断"<<*m_sendSize<<":"<<*m_fileSize;
        emit sigOver(*m_fileNameTime,false);
    }else if(!m_sendOk){
        qDebug()<<"失败"<<*m_fileNameTime;
        emit sigOver(*m_fileNameTime,false);//接收失败
    }else{
        emit sigOver(*m_fileNameTime,true);
    }
}

void SendFileThread::copeConnect() {
    qDebug()<<"Connected!";
}

void SendFileThread::copeRead() {
    qDebug()<<"test!";
    QTcpSocket* tcp = (QTcpSocket*)sender();
    char buf[1024] = {0};
    qint64 len = tcp->read(buf,1024);
    QString flag = QString("%1").arg(buf);
    qDebug()<<"flag:"<<flag;
    /*判断接收端是否接收成功*/
    if("success" == flag){
        m_sendOk = true;
    }else{
        m_sendOk = false;
    }
}

void SendFileThread::sendFile() {
    m_file = new QFile();
    m_file->setFileName(*m_filePath);
    if(!m_file->open(QIODevice::ReadOnly)){
        return;
    }
    qint64 len=0;
    *m_sendSize = 0;
    m_stop = false;
    do{
        //延时
        QEventLoop eventloop;
        QTimer::singleShot(10,&eventloop,SLOT(quit()));
        eventloop.exec();

        char buf[4*1024] = {0};
        len = m_file->read(buf,sizeof(buf));
        m_tcpSocket->write(buf,len);
        QApplication::processEvents();/*实时发送*/
        *m_sendSize += len;
        /*更新进度条*/
        if(len > 0)
            emit refFileInfo(*m_fileNameTime,*m_sendSize);
    }while(len>0 && !m_stop);
    m_file->close();
}


