#include "login.h"
#include "ui_login.h"

#include "addfriendship.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    addfriendship *configWindow = new addfriendship;
    configWindow->show();
}
