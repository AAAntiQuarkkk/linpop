#ifndef TCPSERVERHELPER_H
#define TCPSERVERHELPER_H

#include <QTcpServer>

class TcpServerHelper:public QTcpServer
{
public:
    Q_OBJECT
public:
    explicit TcpServerHelper(QObject *parent = nullptr);
protected:
    //重写incomingConnection,用于多线程通讯，子线程中不能使用主线程中创建的套接字对象
    void incomingConnection(qintptr socketDescriptor);
signals:
    void newSockDescriptor(qintptr _sock);
};

#endif // TCPSERVERHELPER_H
