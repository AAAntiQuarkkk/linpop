#include "processbarreceive.h"
#include "ui_processbarreceive.h"

ProcessBarReceive::ProcessBarReceive(QString fileID,QString clientIP, qint64 fileSize,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessBarReceive)
{
    ui->setupUi(this);
    setFixedHeight(85);
    QString fileName = fileID.section("##",0,0);
    ui->label->setText(fileName+"    from: "+clientIP);
    this->fileSize = fileSize;
    ui->progressBar->setMinimum(0);
    if(fileSize>1024)
        ui->progressBar->setMaximum(fileSize/1024);
    else
        ui->progressBar->setMaximum(fileSize);
}

ProcessBarReceive::~ProcessBarReceive()
{
    delete ui;
}

void ProcessBarReceive::updateProcess(qint64 recSize) {
    if(fileSize>1024)
        ui->progressBar->setValue(recSize/1024);
    else
        ui->progressBar->setValue(recSize);
    ui->label_3->setText(QString("%1/%2").arg(recSize).arg(fileSize));
    update();
}

void ProcessBarReceive::setStatus(bool isFinished) {
    if(isFinished) {
        ui->label_2->setText("完成！");
        qDebug()<<"完成";
    }
    else {
        ui->label_2->setText("错误！");
    }
}

