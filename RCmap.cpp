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
 * ��д�����¼�
*/
void RCMap::paintEvent(QPaintEvent* event){

    QPainter painter(this);//rgb(166,183,199)
    painter.setRenderHint(QPainter::Antialiasing, true);

    int backgroundX = 0; // ��ͼ�ڴ����е� X ����
    int backgroundY = 0; // ��ͼ�ڴ����е� Y ����
    //// ���Ʊ���ͼ
    if (!background.isNull()) {
        painter.drawPixmap(backgroundX, backgroundY, background.scaled(size(), Qt::KeepAspectRatio));
    }
    
    //QLinearGradient gradient(50, 50, 50, 0);
    //gradient.setColorAt(0.1, QColor(30, 30, 30, 0)); // �ұ�Ե��ȫ͸��
    //gradient.setColorAt(0.6, QColor(30, 30, 30, 255)); // 80% λ����ȫ��͸��
    ////gradient.setColorAt(0.8, QColor(0, 0, 0, 255)); // ���Ե��ȫ��͸��

    //// ���ƽ�������
    //painter.setBrush(QBrush(gradient));
    //painter.setPen(Qt::NoPen);
    //painter.drawRect(rect());
    //painter.setRenderHint(QPainter::Antialiasing);

    //QRadialGradient gradient(width() / 10, height() / 10, width() / 10);
    //gradient.setColorAt(0, Qt::transparent); // ����͸��
    //gradient.setColorAt(1, QColor(30, 30, 30)); // ��Ե��ɫ�����Ե�����ɫ��

    //// ���ý���Ϊ���ƵĻ�ˢ
    //painter.setBrush(gradient);
    //painter.drawRect(0, 0, width(), height()); // ������������



    for (int i = 0; i < 4; i++)
    {
        // ����Բ��ͼƬ�����ĺͰ뾶
        // Բ�ΰ뾶
        QRectF circleRect(Tag[i].imageX - radius, Tag[i].imageY - radius, radius * 2, radius * 2);

        // ����һ��Բ�βü�����
        QPainterPath path;
        path.addEllipse(circleRect);
        painter.setClipPath(path); // ���òü�����ΪԲ��
        // ȷ���ƶ�ͼ������Ч�� QPixmap
        if (!Tag[i].movingImage.isNull()) {
            // �����ƶ���ͼƬ������������
            QPixmap scaledImage = Tag[i].movingImage.scaled(radius * 2, radius * 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(circleRect.topLeft(), scaledImage); // ����Բ��ͼƬ
        }
        // ����Բ�α߿�
        painter.setPen(QPen(Tag[i].borderColor, 8)); // ���ñ߿���ɫ�Ϳ��
        painter.setBrush(Qt::NoBrush); // ȷ���߿�û�������ɫ
        painter.drawEllipse(circleRect); // ����Բ�α߿�


    }


}
