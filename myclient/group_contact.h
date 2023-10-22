#ifndef GROUP_CONTACT_H
#define GROUP_CONTACT_H

#include <QWidget>

namespace Ui {
class group_contact;
}

class group_contact : public QWidget
{
    Q_OBJECT

public:
    explicit group_contact(QWidget *parent = nullptr);
    ~group_contact();

private:
    Ui::group_contact *ui;
};

#endif // GROUP_CONTACT_H
