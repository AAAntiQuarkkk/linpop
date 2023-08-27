#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

namespace Ui {
class GuiChatWindow;
}

class GuiChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiChatWindow(QWidget *parent = nullptr);
    ~GuiChatWindow();

private:
    Ui::GuiChatWindow *ui;
};

#endif // CHATWINDOW_H
