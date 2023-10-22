/********************************************************************************
** Form generated from reading UI file 'group_contact.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUP_CONTACT_H
#define UI_GROUP_CONTACT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_group_contact
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *send;

    void setupUi(QWidget *group_contact)
    {
        if (group_contact->objectName().isEmpty())
            group_contact->setObjectName(QString::fromUtf8("group_contact"));
        group_contact->resize(858, 513);
        textEdit = new QTextEdit(group_contact);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(40, 50, 781, 311));
        lineEdit = new QLineEdit(group_contact);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 390, 611, 71));
        send = new QPushButton(group_contact);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(730, 400, 89, 51));

        retranslateUi(group_contact);

        QMetaObject::connectSlotsByName(group_contact);
    } // setupUi

    void retranslateUi(QWidget *group_contact)
    {
        group_contact->setWindowTitle(QCoreApplication::translate("group_contact", "Form", nullptr));
        send->setText(QCoreApplication::translate("group_contact", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class group_contact: public Ui_group_contact {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUP_CONTACT_H
