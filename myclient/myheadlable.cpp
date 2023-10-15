#include "myheadlable.h"
#include<QDebug>
#include<QFileDialog>

 myheadlable::  myheadlable(QWidget* parent ) : QLabel(parent)

{


   QObject:: connect(this,&myheadlable::clicked,[&]{
                                                                    qDebug()<<"choose photo";
         // 弹出文件选择对话框以选择图像文件
             QString imagePath = QFileDialog::getOpenFileName(this, "Select an image", QString(), "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

             // 检查用户是否选择了文件
             if (!imagePath.isEmpty()) {
                 setPixmap(QPixmap(imagePath)); // 设置默认图像
                 setAlignment(Qt::AlignCenter); // 居中显示图像

                 // 设置 QLabel 的大小策略，以保持图像的宽高比并适应 QLabel
                 setScaledContents(true);
                 setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
                 emit imagepath(imagePath);
             }
     });
}
void  myheadlable::  mousePressEvent(QMouseEvent* event)  {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}

