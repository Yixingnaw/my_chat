/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signUp
{
public:
    QLineEdit *nike_name;
    QLineEdit *password;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QWidget *signUp)
    {
        if (signUp->objectName().isEmpty())
            signUp->setObjectName(QString::fromUtf8("signUp"));
        signUp->resize(510, 340);
        nike_name = new QLineEdit(signUp);
        nike_name->setObjectName(QString::fromUtf8("nike_name"));
        nike_name->setGeometry(QRect(130, 70, 151, 41));
        password = new QLineEdit(signUp);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(132, 144, 151, 41));
        label = new QLabel(signUp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 90, 67, 17));
        label_2 = new QLabel(signUp);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 150, 67, 17));
        pushButton = new QPushButton(signUp);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(170, 250, 89, 25));

        retranslateUi(signUp);

        QMetaObject::connectSlotsByName(signUp);
    } // setupUi

    void retranslateUi(QWidget *signUp)
    {
        signUp->setWindowTitle(QCoreApplication::translate("signUp", "Form", nullptr));
        label->setText(QCoreApplication::translate("signUp", "nikename", nullptr));
        label_2->setText(QCoreApplication::translate("signUp", "password", nullptr));
        pushButton->setText(QCoreApplication::translate("signUp", "sign_up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signUp: public Ui_signUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
