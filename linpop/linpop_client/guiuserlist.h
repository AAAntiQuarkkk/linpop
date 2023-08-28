#ifndef GUIUSERLIST_H
#define GUIUSERLIST_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class GuiUserList;
}

class GuiUserList : public QWidget
{
    Q_OBJECT

public:
    explicit GuiUserList(QWidget *parent = nullptr);
    ~GuiUserList();

signals:
    void userselect();
    void chatselect();

private slots:
    void addGuiUser();
    void userItemSelected(QTreeWidgetItem* item, int);

private:
    Ui::GuiUserList *ui;
};

#endif // GUIUSERLIST_H
