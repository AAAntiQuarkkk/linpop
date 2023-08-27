#ifndef GUICHATWINDOW_H
#define GUICHATWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>

#include <userinfo.h>

namespace Ui {
class GuiChatWindow;
}

class GuiChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiChatWindow(QWidget *parent = nullptr);
    ~GuiChatWindow();
    QTimer *timer;

private slots:
    void on_pushButton_sendMsg_clicked();
    void getchathistory();

private:
    Ui::GuiChatWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // GUICHATWINDOW_H
