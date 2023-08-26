#ifndef GUICHATLIST_H
#define GUICHATLIST_H

#include <QWidget>

namespace Ui {
class GuiChatList;
}

class GuiChatList : public QWidget
{
    Q_OBJECT

public:
    explicit GuiChatList(QWidget *parent = nullptr);
    ~GuiChatList();

private:
    Ui::GuiChatList *ui;
};

#endif // GUICHATLIST_H
