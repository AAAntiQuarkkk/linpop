#ifndef SENDFILE_H
#define SENDFILE_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QCloseEvent>

namespace Ui {
class sendFile;
}

class sendFile : public QWidget
{
    Q_OBJECT

public:
    explicit sendFile(QWidget *parent = nullptr);
    ~sendFile();

    //发送数据
    void sendData();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::sendFile *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QFile file;
    QTimer timer;
    QString fileName;
    quint64 fileSize;
    quint64 sendSize;
};

#endif // SENDFILE_H
