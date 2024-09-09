#include "RCMap.h"

#include <QVBoxLayout>


RCMap::RCMap(QWidget* parent ) : QWidget(parent) {

    setWindowFlags(Qt::FramelessWindowHint);
	background.load("../../images/rc7.jpg");//"C:\Users\xh\Desktop\Snipaste_2024-08-28_09-57-11.jpg"

    Tag[0].movingImage.load("../../images/peng.jpg");
    Tag[0].borderColor.setRgb(255, 255, 0);
    Tag[0].imageX = 100;
    Tag[0].imageY = 100;

    Tag[1].movingImage.load("../../images/fan.jpg");
    Tag[1].borderColor.setRgb(0, 255, 255);
    Tag[1].imageX = 200;
    Tag[1].imageY = 200;

    Tag[2].movingImage.load("../../images/ding.jpg");
    Tag[2].borderColor.setRgb(0, 0, 0);
    Tag[2].imageX = 300;
    Tag[2].imageY = 300;

    Tag[3].movingImage.load("../../images/jia.jpg");
    Tag[3].borderColor.setRgb(255, 255, 255);
    Tag[3].imageX = 400;
    Tag[3].imageY = 400;


    radius = 20;


}



RCMap::~RCMap(){

}




/*
 * 重写绘制事件
*/
void RCMap::paintEvent(QPaintEvent* event){

    QPainter painter(this);//rgb(166,183,199)
    painter.setRenderHint(QPainter::Antialiasing, true);

    int backgroundX = 0; // 底图在窗口中的 X 坐标
    int backgroundY = 0; // 底图在窗口中的 Y 坐标
    //// 绘制背景图
    if (!background.isNull()) {
        painter.drawPixmap(backgroundX, backgroundY, background.scaled(size(), Qt::KeepAspectRatio));
    }
    
    //QLinearGradient gradient(50, 50, 50, 0);
    //gradient.setColorAt(0.1, QColor(30, 30, 30, 0)); // 右边缘完全透明
    //gradient.setColorAt(0.6, QColor(30, 30, 30, 255)); // 80% 位置完全不透明
    ////gradient.setColorAt(0.8, QColor(0, 0, 0, 255)); // 左边缘完全不透明

    //// 绘制渐变遮罩
    //painter.setBrush(QBrush(gradient));
    //painter.setPen(Qt::NoPen);
    //painter.drawRect(rect());
    //painter.setRenderHint(QPainter::Antialiasing);

    //QRadialGradient gradient(width() / 10, height() / 10, width() / 10);
    //gradient.setColorAt(0, Qt::transparent); // 中心透明
    //gradient.setColorAt(1, QColor(30, 30, 30)); // 边缘黑色（可以调整颜色）

    //// 设置渐变为绘制的画刷
    //painter.setBrush(gradient);
    //painter.drawRect(0, 0, width(), height()); // 覆盖整个区域



    for (int i = 0; i < 4; i++)
    {
        // 设置圆形图片的中心和半径
        // 圆形半径
        QRectF circleRect(Tag[i].imageX - radius, Tag[i].imageY - radius, radius * 2, radius * 2);

        // 创建一个圆形裁剪区域
        QPainterPath path;
        path.addEllipse(circleRect);
        painter.setClipPath(path); // 设置裁剪区域为圆形
        // 确保移动图像是有效的 QPixmap
        if (!Tag[i].movingImage.isNull()) {
            // 绘制移动的图片，按比例缩放
            QPixmap scaledImage = Tag[i].movingImage.scaled(radius * 2, radius * 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(circleRect.topLeft(), scaledImage); // 绘制圆形图片
        }
        // 绘制圆形边框
        painter.setPen(QPen(Tag[i].borderColor, 8)); // 设置边框颜色和宽度
        painter.setBrush(Qt::NoBrush); // 确保边框没有填充颜色
        painter.drawEllipse(circleRect); // 绘制圆形边框


    }


}
