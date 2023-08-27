#ifndef RECEIVEFILE_H
#define RECEIVEFILE_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QCloseEvent>

namespace Ui {
class receivefile;
}

class receivefile : public QWidget
{
    Q_OBJECT

public:
    explicit receivefile(QWidget *parent = nullptr);
    ~receivefile();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::receivefile *ui;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    quint64 fileSize;
    quint64 receiveSize;
    bool isStart;

    QString ip;
    qint16 port;
};

#endif // RECEIVEFILE_H
