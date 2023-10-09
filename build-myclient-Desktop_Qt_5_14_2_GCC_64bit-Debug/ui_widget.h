/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *user_input;
    QLineEdit *password_input;
    QLabel *label;
    QLabel *label_2;
    QPushButton *log_on;
    QPushButton *sign_up;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        user_input = new QLineEdit(Widget);
        user_input->setObjectName(QString::fromUtf8("user_input"));
        user_input->setGeometry(QRect(180, 170, 361, 61));
        password_input = new QLineEdit(Widget);
        password_input->setObjectName(QString::fromUtf8("password_input"));
        password_input->setGeometry(QRect(180, 290, 361, 61));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(580, 190, 31, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(580, 310, 41, 41));
        log_on = new QPushButton(Widget);
        log_on->setObjectName(QString::fromUtf8("log_on"));
        log_on->setGeometry(QRect(220, 440, 89, 25));
        sign_up = new QPushButton(Widget);
        sign_up->setObjectName(QString::fromUtf8("sign_up"));
        sign_up->setGeometry(QRect(420, 440, 89, 25));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\270\220\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        log_on->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        sign_up->setText(QCoreApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
