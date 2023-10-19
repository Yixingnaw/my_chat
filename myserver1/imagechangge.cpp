#include "imagechangge.h"
#include"QDebug"
#include<QDir>
#include <QImage>
#include <QBuffer>
#include <QImageWriter>
QByteArray imagechange:: operator()(const QString & imgfile){


// 加载原始图像
QImage originalImage(imgfile);

// 设置新的宽度和高度
int newWidth = 200;
int newHeight = 150;

// 缩小图像
QImage scaledImage = originalImage.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

// 创建一个内存缓冲区
QBuffer buffer;
buffer.open(QIODevice::WriteOnly);
QRegularExpression regex("\\.([^.]+)$"); // 匹配最后一个点号后面的字符

  QRegularExpressionMatch match = regex.match(imgfile);
    QString fileExtension = match.captured(1);
// 创建图像编写器并设置图像质量
QImageWriter writer(&buffer,fileExtension.toUtf8() ); // 选择适当的格式，如PNG
writer.setQuality(50); // 设置图像质量，范围是0到100

// 将缩小后的图像写入缓冲区
writer.write(scaledImage);

// 获取缓冲区的数据
QByteArray imageData = buffer.data();

// 检查文件大小
if (imageData.size() > 20 * 1024) {
    // 如果文件大小仍然大于20KB，可以降低图像质量并重复上述过程
    writer.setQuality(30); // 降低图像质量
    buffer.close();
    buffer.open(QIODevice::WriteOnly);
    writer.write(scaledImage);
    imageData = buffer.data();
}
                                                      //  qDebug()<<"open file file success";
        return imageData.toBase64();

  }
QImage   imagechange:: byte_to_qimage(QByteArray& imagebyte){
    QImage image;
   if(! image.loadFromData(QByteArray::fromBase64(imagebyte))){qDebug()<<"read image filed";throw   QString("read imagefile") ;}

   return  image;
}
QString    imagechange:: image_postfix(QImage& image){

    if (!image.isNull()) {
            // 获取图像的格式
            QImage::Format imageFormat = image.format();

            // 根据格式确定文件扩展名
            QString fileExtension;
            switch (imageFormat) {
                case QImage::Format_Mono:
                    fileExtension = ".bmp"; // 例如：BMP 格式
                    break;
                case QImage::Format_Grayscale8:
                    fileExtension = ".png"; // 例如：PNG 格式
                    break;
                case QImage::Format_RGB32:
                    fileExtension = ".jpg"; // 例如：JPEG 格式
                    break;
                // 添加更多格式的处理
                default:
                    qDebug() << "未知的图像格式";
                    break;
            }

            qDebug() << "图像已保存为："<<fileExtension<<"格式" ;
            return fileExtension;
        } else {
            qDebug() << "图像加载失败";
        }
}

QString     imagechange::get_imagepath(qqUser& qq)
{
// 获取当前工作目录
QString currentDir = QDir::currentPath();
// 使用相对路径
//QString relativePath = "image/"+ qq.getUsername()+imagechange().image_postfix(""); // 以当前工作目录为起点的相对路径
// 将相对路径转换为绝对路径
//QString absolutePath = QDir(currentDir).filePath(relativePath);



}
