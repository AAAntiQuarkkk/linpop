#include "addfriendship.h"
#include "ui_addfriendship.h"
#include "database.h"

addfriendship::addfriendship(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfriendship)
{
    ui->setupUi(this);
    setWindowTitle("添加好友");
}

addfriendship::~addfriendship()
{
    delete ui;
}

void addfriendship::on_pushButton_clicked()
{
    DataDB *dbInstance = DataDB::GetInstance();
    quint32 friend_id = ui->lineEdit->text().toUInt();
    dbInstance->addFriendship(friend_id);
}

void addfriendship::on_pushButton_2_clicked()
{
    DataDB *dbInstance = DataDB::GetInstance();
    quint32 friend_id = ui->lineEdit->text().toUInt();
    dbInstance->deleteFriendship(friend_id);
}
