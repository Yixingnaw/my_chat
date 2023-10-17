/********************************************************************************
** Form generated from reading UI file 'qqcontact.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQCONTACT_H
#define UI_QQCONTACT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qqContact
{
public:
    QListWidget *friends;
    QLineEdit *jiahaoyou;
    QListWidget *listWidget;
    QLineEdit *jiaqun;
    QLabel *label;
    QPushButton *add_friend;
    QPushButton *add_group;
    QLabel *head;
    QLineEdit *lineEdit;
    QPushButton *group_create;

    void setupUi(QWidget *qqContact)
    {
        if (qqContact->objectName().isEmpty())
            qqContact->setObjectName(QString::fromUtf8("qqContact"));
        qqContact->resize(338, 663);
        friends = new QListWidget(qqContact);
        friends->setObjectName(QString::fromUtf8("friends"));
        friends->setGeometry(QRect(10, 20, 311, 192));
        jiahaoyou = new QLineEdit(qqContact);
        jiahaoyou->setObjectName(QString::fromUtf8("jiahaoyou"));
        jiahaoyou->setGeometry(QRect(10, 570, 111, 25));
        listWidget = new QListWidget(qqContact);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 250, 311, 192));
        jiaqun = new QLineEdit(qqContact);
        jiaqun->setObjectName(QString::fromUtf8("jiaqun"));
        jiaqun->setGeometry(QRect(130, 570, 91, 21));
        label = new QLabel(qqContact);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 620, 66, 17));
        add_friend = new QPushButton(qqContact);
        add_friend->setObjectName(QString::fromUtf8("add_friend"));
        add_friend->setGeometry(QRect(20, 620, 89, 25));
        add_group = new QPushButton(qqContact);
        add_group->setObjectName(QString::fromUtf8("add_group"));
        add_group->setGeometry(QRect(130, 620, 89, 25));
        head = new QLabel(qqContact);
        head->setObjectName(QString::fromUtf8("head"));
        head->setGeometry(QRect(30, 470, 67, 81));
        lineEdit = new QLineEdit(qqContact);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 500, 113, 25));
        group_create = new QPushButton(qqContact);
        group_create->setObjectName(QString::fromUtf8("group_create"));
        group_create->setGeometry(QRect(230, 620, 89, 25));

        retranslateUi(qqContact);

        QMetaObject::connectSlotsByName(qqContact);
    } // setupUi

    void retranslateUi(QWidget *qqContact)
    {
        qqContact->setWindowTitle(QCoreApplication::translate("qqContact", "Form", nullptr));
        label->setText(QString());
        add_friend->setText(QCoreApplication::translate("qqContact", "friend", nullptr));
        add_group->setText(QCoreApplication::translate("qqContact", "group", nullptr));
        head->setText(QCoreApplication::translate("qqContact", "TextLabel", nullptr));
        group_create->setText(QCoreApplication::translate("qqContact", "group_create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qqContact: public Ui_qqContact {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQCONTACT_H
