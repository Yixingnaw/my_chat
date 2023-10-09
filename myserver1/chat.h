#ifndef CHAT_H
#define CHAT_H
#include"global.h"
#include <QWidget>

namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
    //inline return ui_ptr;
    Ui::chat* return_ui(){
        return  ui;
    }
     void show_online_numbbers()const;

private:
    Ui::chat *ui;
};

#endif // CHAT_H
