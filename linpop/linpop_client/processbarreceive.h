#ifndef PROCESSBARRECEIVE_H
#define PROCESSBARRECEIVE_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ProcessBarReceive;
}

class ProcessBarReceive : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessBarReceive(QString fileID, QString clientIP, qint64 fileSize,QWidget *parent = nullptr);
    ~ProcessBarReceive();
    void updateProcess(qint64 recSize);
    void setStatus(bool isFinished);

private:
    Ui::ProcessBarReceive *ui;
    qint64 fileSize;
};

#endif // PROCESSBARRECEIVE_H
