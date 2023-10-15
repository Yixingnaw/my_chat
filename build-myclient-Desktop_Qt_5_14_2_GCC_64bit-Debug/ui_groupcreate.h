/********************************************************************************
** Form generated from reading UI file 'groupcreate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPCREATE_H
#define UI_GROUPCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_groupcreate
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *send;
    QLineEdit *gropu_name;
    QLineEdit *lineEdit;

    void setupUi(QWidget *groupcreate)
    {
        if (groupcreate->objectName().isEmpty())
            groupcreate->setObjectName(QString::fromUtf8("groupcreate"));
        groupcreate->resize(501, 371);
        label = new QLabel(groupcreate);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 180, 101, 17));
        label_2 = new QLabel(groupcreate);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(270, 140, 91, 16));
        send = new QPushButton(groupcreate);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(360, 320, 89, 25));
        gropu_name = new QLineEdit(groupcreate);
        gropu_name->setObjectName(QString::fromUtf8("gropu_name"));
        gropu_name->setGeometry(QRect(60, 140, 151, 25));
        lineEdit = new QLineEdit(groupcreate);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(62, 204, 301, 101));

        retranslateUi(groupcreate);

        QMetaObject::connectSlotsByName(groupcreate);
    } // setupUi

    void retranslateUi(QWidget *groupcreate)
    {
        groupcreate->setWindowTitle(QCoreApplication::translate("groupcreate", "Form", nullptr));
        label->setText(QCoreApplication::translate("groupcreate", "add descrition", nullptr));
        label_2->setText(QCoreApplication::translate("groupcreate", "group_name", nullptr));
        send->setText(QCoreApplication::translate("groupcreate", "create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class groupcreate: public Ui_groupcreate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPCREATE_H
