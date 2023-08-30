#ifndef RECEIVEFILETHREAD_H
#define RECEIVEFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include <QFile>
#include <QFileInfo>

class ReceiveFileThread:public QObject
{
    Q_OBJECT
public:
    ReceiveFileThread(QObject* parent = NULL);
    ~ReceiveFileThread();

signals:
    void sigOver(QString,bool);
    void refFileInfo(QString ,QString ,qint64 ,qint64 );

public slots:
    void initThread(qintptr);
    void copeTimeout();
    void copeReadyRead();
    void copeDisconnected();

private:
    void initFile();
    void returnReceive(bool);
    QString getFilePath(QString);

private:
    QTcpSocket* m_tcpSocket;
    QFile* m_file;
    bool m_isStart;
    qint64* m_recSize;
    qint64* m_fileSize;
    QString* m_filePath;
    QString* m_fileName;
    QString* m_fileNameTime;
    bool m_transOver;
    QTimer* m_timer;
};

#endif // RECEIVEFILETHREAD_H
