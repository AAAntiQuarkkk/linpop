#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QTcpSocket>
#include <mainwindow.h>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

//signals:
//    void btnSignal(quint8 state);

private slots:
//    void getStatus(quint8 state);
//    void btnClicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
    QTcpSocket *tcpSocket;
};

#endif // LOGIN_H
