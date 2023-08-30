#include "tcpserverhelper.h"

TcpServerHelper::TcpServerHelper(QObject *parent):QTcpServer(parent)
{

}

void TcpServerHelper::incomingConnection(qintptr socketDescriptor) {
    emit newSockDescriptor(socketDescriptor);
}
