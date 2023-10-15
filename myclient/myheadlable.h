#ifndef MYHEADLABLE_H
#define MYHEADLABLE_H
#include<QLabel>
#include<QMouseEvent>
class myheadlable:public QLabel
{
public:
    myheadlable();

        Q_OBJECT

    public:
        explicit myheadlable(QWidget* parent = nullptr) ;

    protected:
       void mousePressEvent(QMouseEvent* event) override;
     signals:
        void clicked();
        void imagepath(const QString &);
    };


#endif // MYHEADLABLE_H
