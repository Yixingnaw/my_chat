/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *send;
    QLabel *friend_2;
    QLabel *mine;
    QLabel *label;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(603, 437);
        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(110, 100, 361, 221));
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 350, 361, 51));
        send = new QPushButton(Form);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(500, 360, 89, 41));
        friend_2 = new QLabel(Form);
        friend_2->setObjectName(QString::fromUtf8("friend_2"));
        friend_2->setGeometry(QRect(30, 30, 67, 71));
        friend_2->setScaledContents(false);
        mine = new QLabel(Form);
        mine->setObjectName(QString::fromUtf8("mine"));
        mine->setGeometry(QRect(480, 40, 67, 51));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(500, 50, 61, 31));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        send->setText(QCoreApplication::translate("Form", "send", nullptr));
        friend_2->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        mine->setText(QString());
        label->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
