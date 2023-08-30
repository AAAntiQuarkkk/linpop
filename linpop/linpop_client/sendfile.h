#ifndef SENDFILE_H
#define SENDFILE_H

#include "sendfilethread.h"
#include "processbarsend.h"

#include <QMainWindow>
#include <QMap>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class SendFile; }
QT_END_NAMESPACE

class SendFile : public QMainWindow
{
    Q_OBJECT

public:
    SendFile(QString clientID, QWidget *parent = nullptr);
    ~SendFile();

signals:
    void startThread(ushort port,QString ip,QString fileID);

private slots:
    void doRefFileInfo(QString ,qint64);
    void doSigOver(QString,bool);
    void doSigConnect(bool);

private slots:
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    ProcessBarSend* getProcessBarSend(QString);
    QThread* getSendFileThread(QString);

private:
    Ui::SendFile *ui;

    QTcpSocket* tcpSocket;

    QThread *fileThread;
    SendFileThread *sendThread;

    QMap<QString,ProcessBarSend*> m_mapSend;
    QMap<QString,QThread*> m_mapClient;
};
#endif // MAINWINDOW_H
