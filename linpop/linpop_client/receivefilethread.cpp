#include "receivefilethread.h"

#include <QDebug>
#include <QStringList>
#include <QApplication>

ReceiveFileThread::ReceiveFileThread(QObject*)
{

}
ReceiveFileThread::~ReceiveFileThread() {
    if(m_file->isOpen()){
        m_file->close();
    }
    if(m_tcpSocket != NULL){
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
        m_tcpSocket = NULL;
    }
    if(m_timer->isActive())
        m_timer->stop();
}

void ReceiveFileThread::initThread(qintptr _sock) {
    m_file = new QFile();
    m_recSize = (qint64*)malloc(sizeof(qint64));
    m_fileSize = (qint64*)malloc(sizeof(qint64));
    m_filePath = new QString();
    m_fileName = new QString();
    m_fileNameTime = new QString();
    m_timer = new QTimer();
    m_tcpSocket = new QTcpSocket();

    m_tcpSocket->setSocketDescriptor(_sock);
    m_isStart = true;
    *m_filePath = "";
    *m_recSize = 0;
    m_transOver = false;

    connect(m_timer,SIGNAL(timeout()),this,SLOT(copeTimeout()));
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(copeReadyRead()));
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(copeDisconnected()));

}

void ReceiveFileThread::returnReceive(bool received) {
    qDebug()<<"returnReceice:"<<received;
    m_transOver = true;
    //回复客户端是否接收成功
    if(received || *m_fileSize == *m_recSize){
        qDebug()<<*m_fileSize<<":"<<*m_recSize;
        m_tcpSocket->write(QString("success").toUtf8().data(),1024);
        qDebug()<<*m_fileSize<<":"<<*m_recSize;
        QApplication::processEvents();/*实时发送*/
        emit sigOver(*m_fileNameTime,true);
        qDebug()<<"test"<<*m_fileNameTime;
    }else{
        qDebug()<<*m_fileSize<<"/"<<*m_recSize;
        m_tcpSocket->write(QString("error").toUtf8().data(),1024);
        QApplication::processEvents();/*实时发送*/
        emit sigOver(*m_fileNameTime,false);
    }
}

QString ReceiveFileThread::getFilePath(QString filePath) {
    /*判断文件名是否重复，重复则重命名*/
    QFile file(filePath);
    if (file.exists()){
        QFileInfo info(filePath);
        return getFilePath(*m_filePath + info.completeBaseName()+"(1)."+info.completeSuffix());
    }else{
        return filePath;
    }
}

void ReceiveFileThread::initFile() {
    m_isStart = false;
    char buf[4*1024] = {0};
    m_tcpSocket->read(buf,1024);
    qDebug()<<"buf:"<<buf;
    //验证
    QStringList list = QString("%1").arg(buf).split("##");
    if(list.length()<2){
        emit sigOver(*m_fileName,false);
    }
    *m_fileName = QString("%1").arg(buf).section("##",0,0);
    *m_fileSize = QString("%1").arg(buf).section("##",1,1).toInt();
    //名字去重
    QString filePath = *m_filePath + *m_fileName;
    filePath = getFilePath(filePath);
    QFileInfo info(filePath);
    *m_fileName = info.fileName();
    //打开文件
    m_file->setFileName(filePath);
    bool isOk = m_file->open(QIODevice::WriteOnly);
    if(!isOk){
        qDebug()<<"open error!";
        returnReceive(false);
    }
    //添加时间
    QString currentDateTime =(QDateTime::currentDateTime()).toString("MMddhhmmsszzz");
    qDebug()<<"time:"<<currentDateTime;
    *m_fileNameTime = (*m_fileName) +"##"+ currentDateTime;
}

void ReceiveFileThread::copeTimeout() {
    static qint64 preSize =0;
    qDebug()<<this<<":"<<preSize<<":"<<*m_recSize;
    if(preSize == *m_recSize){
        returnReceive(false);
    }
    preSize = *m_recSize;
}

void ReceiveFileThread::copeReadyRead() {
    if(m_isStart) {
        initFile();
    }
    m_timer->start(1000);//每秒进行验证
    //接收文件
    QByteArray array = m_tcpSocket->readAll();
    qint64 len = m_file->write(array);
    *m_recSize+=len;
    //更新
    QString clientIP = m_tcpSocket->peerAddress().toString();
    if(len>0){
        emit refFileInfo(*m_fileNameTime,clientIP,*m_fileSize,*m_recSize);
    }
    if(*m_recSize == *m_fileSize){
        qDebug()<<"rec success!";
        returnReceive(true);
    }
}

void ReceiveFileThread::copeDisconnected() {
    qDebug()<<"dealDisconnected!";
    if(!m_transOver){
        if(*m_fileSize != *m_recSize){
            emit sigOver(*m_fileNameTime,false);
        }else{
            emit sigOver(*m_fileNameTime,true);
        }
    }
}
