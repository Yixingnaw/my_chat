/********************************************************************************
** Form generated from reading UI file 'chatui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATUI_H
#define UI_CHATUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chatUi
{
public:
    QLineEdit *contact;
    QPushButton *send;
    QTextEdit *textEdit;

    void setupUi(QDialog *chatUi)
    {
        if (chatUi->objectName().isEmpty())
            chatUi->setObjectName(QString::fromUtf8("chatUi"));
        chatUi->resize(833, 440);
        contact = new QLineEdit(chatUi);
        contact->setObjectName(QString::fromUtf8("contact"));
        contact->setGeometry(QRect(80, 350, 621, 51));
        send = new QPushButton(chatUi);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(720, 360, 89, 25));
        textEdit = new QTextEdit(chatUi);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(70, 50, 681, 271));

        retranslateUi(chatUi);

        QMetaObject::connectSlotsByName(chatUi);
    } // setupUi

    void retranslateUi(QDialog *chatUi)
    {
        chatUi->setWindowTitle(QCoreApplication::translate("chatUi", "Dialog", nullptr));
        send->setText(QCoreApplication::translate("chatUi", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatUi: public Ui_chatUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATUI_H
