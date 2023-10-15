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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chatUi
{
public:
    QTextEdit *textEdit;
    QLabel *friend_2;
    QLabel *mine;
    QTextEdit *input_text;
    QPushButton *chat_text;

    void setupUi(QDialog *chatUi)
    {
        if (chatUi->objectName().isEmpty())
            chatUi->setObjectName(QString::fromUtf8("chatUi"));
        chatUi->resize(700, 526);
        textEdit = new QTextEdit(chatUi);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 80, 711, 311));
        friend_2 = new QLabel(chatUi);
        friend_2->setObjectName(QString::fromUtf8("friend_2"));
        friend_2->setGeometry(QRect(30, 20, 67, 51));
        mine = new QLabel(chatUi);
        mine->setObjectName(QString::fromUtf8("mine"));
        mine->setGeometry(QRect(600, 20, 67, 51));
        input_text = new QTextEdit(chatUi);
        input_text->setObjectName(QString::fromUtf8("input_text"));
        input_text->setGeometry(QRect(20, 400, 591, 101));
        chat_text = new QPushButton(chatUi);
        chat_text->setObjectName(QString::fromUtf8("chat_text"));
        chat_text->setGeometry(QRect(630, 420, 51, 51));

        retranslateUi(chatUi);

        QMetaObject::connectSlotsByName(chatUi);
    } // setupUi

    void retranslateUi(QDialog *chatUi)
    {
        chatUi->setWindowTitle(QCoreApplication::translate("chatUi", "Dialog", nullptr));
        friend_2->setText(QCoreApplication::translate("chatUi", "TextLabel", nullptr));
        mine->setText(QCoreApplication::translate("chatUi", "TextLabel", nullptr));
        chat_text->setText(QCoreApplication::translate("chatUi", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatUi: public Ui_chatUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATUI_H
