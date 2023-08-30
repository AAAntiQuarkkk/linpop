#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include "processbarreceive.h"
#include "receivefilethread.h"
#include "tcpserverhelper.h"

#include <QMainWindow>
#include <QMap>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ReceiveFile; }
QT_END_NAMESPACE

class ReceiveFile : public QMainWindow
{
    Q_OBJECT

public:
    ReceiveFile(QWidget *parent = nullptr);
    ~ReceiveFile();

signals:
    void startThread(qintptr);

private slots:
    void copeNewConnection(qintptr);
    void doRefFileInfo(QString , QString , qint64 , qint64 );
    void doSigOver(QString,bool);

protected:
    void closeEvent(QCloseEvent *event);

private:
    void serverInit();
    bool getReceiveFirst(QString);
    ProcessBarReceive* getProcessBarReceive(QString);
    QThread* getReceiveFileThread(QString);

private:
    Ui::ReceiveFile *ui;

    QTcpSocket* tcpSocket;

    QThread *fileThread;
    ReceiveFileThread *receiveThread;

    //QTcpServer* m_tcpServer;
    TcpServerHelper* m_tcpServerHelper;

    QMap<QString,ProcessBarReceive*> m_mapReceive;
    QMap<QString,QThread*> m_mapTcpServer;
    QList<QString> m_ListRecFirst;
};
#endif // MAINWINDOW_H
