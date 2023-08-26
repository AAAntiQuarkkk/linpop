#ifndef ADDFRIENDSHIP_H
#define ADDFRIENDSHIP_H

#include <QWidget>

namespace Ui {
class addfriendship;
}

class addfriendship : public QWidget
{
    Q_OBJECT

public:
    explicit addfriendship(QWidget *parent = nullptr);
    ~addfriendship();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addfriendship *ui;
};

#endif // ADDFRIENDSHIP_H
