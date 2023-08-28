#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtNetwork>
#include <QCloseEvent>
#include <qinputdialog.h>
#include <QMessageBox>
#include <QTimer>

#include <guichatwindow.h>
#include <userinfo.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    //void checkUserSelected();//需要有对用户作区分的参数？
    void showChat();//对会话需要一个区分的参数？

    //生成好友列表
    void Createdfriendlist();

    void on_pushButton_addFriend_clicked();

    void on_pushButton_startChat_clicked();

    void on_pushButton_deleteFriend_clicked();

    void on_pushButton_sendFile_clicked();

    void on_pushButton_clicked();

    //void on_pushButton_quit_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // MAINWINDOW_H
