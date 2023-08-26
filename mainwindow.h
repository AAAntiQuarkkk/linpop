#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void checkUserSelected();//需要有对用户作区分的参数？
    void showChat();//对会话需要一个区分的参数？


private:
    Ui::MainWindow *ui;
    QWidget *guiuserlist;
    QWidget *guichatlist;
};

#endif // MAINWINDOW_H
