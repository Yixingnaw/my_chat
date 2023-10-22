#include "group_contact.h"
#include "ui_group_contact.h"

group_contact::group_contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::group_contact)
{
    ui->setupUi(this);
}

group_contact::~group_contact()
{
    delete ui;
}
