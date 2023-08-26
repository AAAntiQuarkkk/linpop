#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void btnSignal(quint8 state);

private slots:
    void getStatus(quint8 state);
    void btnClicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
