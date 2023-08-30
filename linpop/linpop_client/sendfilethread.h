#ifndef SENDFILETHREAD_H
#define SENDFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>

class SendFileThread:public QObject
{
    Q_OBJECT
public:
    SendFileThread(QObject* parent = NULL);
    ~SendFileThread();

signals:
    void sigConnect(bool);
    void refFileInfo(QString ,qint64 );
    void sigOver(QString,bool);

public slots:
    void initThread(ushort port,QString ip,QString fileID);
    void copeDisconnect();
    void copeConnect();
    void copeRead();

private:
    QString* m_ip;
    ushort* m_port;
    //QString* m_hostIp;
    QTcpSocket* m_tcpSocket;

    QFile* m_file;
    qint64* m_fileSize;
    qint64* m_sendSize;
    QString* m_filePath;
    QString* m_fileName;
    bool m_stop;
    bool m_sendOk;
    QString* m_time;
    QString* m_fileNameTime;

private:
    void sendFile();
};

#endif // SENDFILETHREAD_H
