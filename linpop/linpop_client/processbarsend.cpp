#include "processbarsend.h"
#include "ui_processbarsend.h"

ProcessBarSend::ProcessBarSend(QString fileName,qint64 fileSize,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessBarSend)
{
    ui->setupUi(this);
    setFixedHeight(85);
    ui->label->setText(fileName);
    this->fileSize = fileSize;
    ui->progressBar->setMinimum(0);
    if(fileSize>1024)
        ui->progressBar->setMaximum(fileSize/1024);
    else
        ui->progressBar->setMaximum(fileSize);
}

ProcessBarSend::~ProcessBarSend()
{
    delete ui;
}

void ProcessBarSend::updateProcess(qint64 recSize) {
    if(fileSize>1024)
        ui->progressBar->setValue(recSize/1024);
    else
        ui->progressBar->setValue(recSize);
    ui->label_3->setText(QString("%1/%2").arg(recSize).arg(fileSize));
    update();
}

void ProcessBarSend::setStatus(bool isFinished) {
    if(isFinished) {
        ui->label_2->setText("完成！");
    }
    else {
        ui->label_2->setText("错误！");
    }
}
