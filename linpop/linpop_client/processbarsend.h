#ifndef PROCESSBARSEND_H
#define PROCESSBARSEND_H

#include <QWidget>

namespace Ui {
class ProcessBarSend;
}

class ProcessBarSend : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessBarSend(QString fileName,qint64 fileSize,QWidget *parent = nullptr);
    ~ProcessBarSend();
    void updateProcess(qint64 recSize);
    void setStatus(bool isFinished);

private:
    Ui::ProcessBarSend *ui;
    qint64 fileSize;
};

#endif // ProcessBarSend_H
