#include "widget.h"
#include"myheadlable.h"
#include <QApplication>
#include"qqcontact.h"
#include<QTcpSocket>
#include"groupcreate.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
   // qqContact c;
    //c.show();

    // groupcreate* g=new groupcreate();
   //g->show();
     w.show();

    return a.exec();
}
