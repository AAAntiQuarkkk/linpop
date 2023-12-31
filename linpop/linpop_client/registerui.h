#ifndef REGISTERUI_H
#define REGISTERUI_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <login.h>

namespace Ui {
class registerui;
}

class registerui : public QWidget
{
    Q_OBJECT

public:
    explicit registerui(QWidget *parent = nullptr);
    ~registerui();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::registerui *ui;
    QTcpSocket *tcpSocket;
};

#endif // REGISTERUI_H
