#include"Gauge.h"



Gauge::Gauge(QWidget* parent) : QWidget(parent) {


   // ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    startAngle = 150;
    currentValue = 0;
    currentValue2 = 0;
    flag = true;

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() {

        update();
        });

    
    timer->start(20);
}

Gauge::~Gauge() {

   // delete ui;

}


/*
 * ���ƻ���
*/
void Gauge::initCanvas(QPainter& painter)
{
    //�������
    painter.setRenderHint(QPainter::Antialiasing, true);
    //���õ�ɫ
   // painter.setBrush(QColor(166, 183, 199));//rgb(166,183,199)
   // painter.setBrush(QColor(0, 0, 0));//rgb(166,183,199)
   // painter.drawRect(rect());
    //ƽ������ϵԭ��λ��
    //QPoint center(rect().width() / 4, rect().height() * 0.6);
    //painter.translate(center);

}

/*
 * ��СԲ
*/
void Gauge::drawMiddleCircle(QPainter& painter, int radius)
{
    //���û�����ɫ�Ϳ��
    painter.setPen(QPen(QColor(255, 255, 255), 3));
    //ԭ�����꣨0��0�����ư뾶Ϊradius��Բ
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * ���̶�
*/
void Gauge::drawScaleLine(QPainter& painter, int radius, int maxValue, int scale)
{
    //�ܼ�60��С�̶ȣ�ÿһ��С�̶ȵĽǶ�ֵ
    angle = 240 * 1.0 / scale;

    //float ang = 240 * 1.0 / scale;
    //���浱ǰ����
    painter.save();
    painter.setPen(QPen(Qt::white, 3));
    //������ʼ�̶�λ��
    painter.rotate(startAngle);
    //painter.
    for (int i = 0; i <= scale; i++)
    {
        if (i >= (3 * scale / 4))
        {
            //��40���̶Ⱥ󣬻��ƻ����޸ĳɺ�ɫ
            painter.setPen(QPen(Qt::blue, 3));
        }
        if (i % 5 == 0)
        {
            //���Ƴ��̶�
            painter.drawLine(radius + 10, 0, radius - 5, 0);

        }
        else
        {
            //���ƶ̶̿�
            painter.drawLine(radius + 10, 0, radius, 0);
        }
        //������һ���̶���תһ������
        painter.rotate(angle);
    }
    //�ָ�����
    painter.restore();
    painter.setPen(QPen(Qt::white, 5));


}

/*
 * ���̶�ֵ
*/
void Gauge::drawScaleValue(QPainter& painter, int radius, int maxValue, int scale)
{
    //�����������ͺʹ�С


    QFont textFont("Arial", 12);
    //���ô���

    angle = 240 * 1.0 / scale;

    // float ang = 240 * 1.0 / scale;
    textFont.setBold(true);
    painter.setFont(textFont);
    int text_r = radius - 49;
    for (int i = 0; i <= scale; i++)
    {
        if (i % 5 == 0)
        {
            if (i >= 3 * scale / 4)
            {
                painter.setPen(QPen(Qt::blue, 5));
            }
            //���浱ǰ����ϵ
            painter.save();
            int delX = qCos((210 - angle * i) * M_PI / 180) * text_r;
            int delY = qSin(qDegreesToRadians(210 - angle * i)) * text_r;
            //ƽ������ϵ
            painter.translate(QPoint(delX, -delY));
            //��ת����ϵ
            painter.rotate(-120 + angle * i);
            //д�Ͽ̶�ֵ�����־���
            painter.drawText(-25, -50, 50, 30, Qt::AlignCenter, QString::number(i * (maxValue / scale)));
            //�ָ�����ϵ
            painter.restore();
        }
    }
    painter.setPen(QPen(Qt::white, 5));
}

/*
 * ��ָ��
*/
void Gauge::drawPoint(QPainter& painter, int radius, int maxValue, float value)
{
    //���浱ǰ����
    painter.save();
    //���û�ˢ��ɫ
    painter.setBrush(Qt::white);
    //���û���Ϊ������
    painter.setPen(Qt::NoPen);
    static const QPointF points[4] = {
        QPointF(0, 0.0),
        QPointF(radius * 2.0 / 3, -1.1),
        QPointF(radius * 2.0 / 3, 1.1),
        QPointF(0, 15.0)
    };
    //����ѡ��ת
    painter.rotate(startAngle + value * (240.0 / maxValue));////value * (500.0/240))
    //���ƶ����
    painter.drawPolygon(points, 4);
    //�ָ�����
    painter.restore();
}

/*
 * ������
*/
void Gauge::drawSpeedSector(QPainter& painter, int radius, int maxValue, int value)
{
    //�����������
    QRect rentangle(-radius, -radius, radius * 2, radius * 2);
    //���û���������
    painter.setPen(Qt::NoPen);
    //���û�ˢ��ɫ
    painter.setBrush(QColor(0, 0, 255, 80));
    //��������
    painter.drawPie(rentangle, (360 - startAngle) * 16, -value * (240.0 / maxValue) * 16);
}

/*
 * ��������Բ
*/
void Gauge::drawInnerEllipse(QPainter& painter, int radius)
{
    QRadialGradient radial(0, 0, radius);
    //������ɫ
    radial.setColorAt(0.0, QColor(0, 0, 255, 200));
    //��Χ��ɫ
    radial.setColorAt(1.0, QColor(0, 0, 0, 100));
    //���û�ˢ����ɫ
    painter.setBrush(radial);
    //��Բ��
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * ����ɫ��Ȧ
*/
void Gauge::drawInnerEllipseBlack(QPainter& painter, int radius)
{
    //���û�ˢ
    painter.setBrush(Qt::black);
    //����Բ��
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * ���Ƶ�ǰ��ֵ
*/
void Gauge::drawCurrentSpeed(QPainter& painter)
{
    painter.setPen(Qt::white);
    //������ֵ
    QFont font("Arial", 24);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(-60, -60, 120, 100), Qt::AlignCenter, QString::number(currentValue * 4));
    //���Ƶ�λ
    QFont font_u("Arial", 13);
    painter.setFont(font_u);
    painter.drawText(QRect(-60, -60, 120, 160), Qt::AlignCenter, "km/h");

    //QFont font_T("Arial", 40);
    //font_T.setBold(true);
    //painter.setFont(font_T);
    //painter.drawText(QRect(-60, -60, 1000, 100), Qt::AlignCenter, QString::number(5));
}

/*
 * ����ǣ�������Ȧ
*/
void Gauge::drawEllipseOutSkirts(QPainter& painter, int radius)
{
    //�������λ�������
    QRect outAngle(-radius, -radius, 2 * radius, 2 * radius);
    painter.setPen(Qt::NoPen);
    //���ý���ɫ
    QRadialGradient radia(0, 0, radius);
    radia.setColorAt(1, QColor(0, 0, 255, 200));
    radia.setColorAt(0.97, QColor(0, 0, 255, 120));
    radia.setColorAt(0.9, QColor(0, 0, 0, 0));
    radia.setColorAt(0, QColor(0, 0, 0, 0));
    painter.setBrush(radia);
    //����Բ��
    painter.drawPie(outAngle, (360 - 150) * 16, -240 * 16);
}

/*
 * ��LOGO
*/
void Gauge::drawLogo(QPainter& painter, int radius)
{
    //����Logo��������
    QRect rectLogo(-65, radius * 0.38, 130, 50);
    painter.drawPixmap(rectLogo, QPixmap("./logo2.png"));
}


/*
 * ��д�����¼�
*/
void Gauge::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);//rgb(166,183,199)



#if 1
    int dashBoad_r = 160;//�Ǳ��̰뾶
    //1.���ƻ���
    initCanvas(painter);


    QPoint center(width()/2, width() / 2);
    painter.translate(center);

    //2.��СԲ
    drawMiddleCircle(painter, 30);
    //3.���̶�
    drawScaleLine(painter, dashBoad_r, 240, 60);
    //4.���̶�ֵ
    drawScaleValue(painter, dashBoad_r, 240, 60);
    //5.��ָ��
    drawPoint(painter, dashBoad_r, 240, currentValue);
    //6.������
    drawSpeedSector(painter, dashBoad_r + 25, 240, currentValue);
    //7.��������Բ
    drawInnerEllipse(painter, 110 / 2);
    //8.����ɫ��Ȧ
    drawInnerEllipseBlack(painter, 80 / 2);
    //9.����ǰ��ֵ
   // drawCurrentSpeed(painter);
    painter.setPen(Qt::white);
    //������ֵ
    QFont font("Arial", 20);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(-60, -60, 120, 120), Qt::AlignCenter, QString::number(currentValue));
    //���Ƶ�λ
    QFont font_u("Arial", 16);
    font_u.setBold(true);
    painter.setFont(font_u);
    painter.drawText(QRect(-60, -60, 120, 320), Qt::AlignCenter, "km/h");
    //10.����ǣ�������Ȧ
    drawEllipseOutSkirts(painter, dashBoad_r + 25);



   // QPoint center2(0, 450);
   // painter.translate(center2);
   // drawMiddleCircle(painter, 30);
   // //3.���̶�
   // drawScaleLine(painter, dashBoad_r, 240, 50);
   // //4.���̶�ֵ
   // drawScaleValue(painter, dashBoad_r, 500, 50);
   // //5.��ָ��
   // drawPoint(painter, dashBoad_r, 500, currentValue2);
   // //6.������
   // drawSpeedSector(painter, dashBoad_r + 25, 500, currentValue2);
   // //7.��������Բ
   // drawInnerEllipse(painter, 110 / 2);
   // //8.����ɫ��Ȧ
   // drawInnerEllipseBlack(painter, 80 / 2);

   // painter.setPen(Qt::white);
   // // ������ֵ
   // QFont font_C("Arial", 20);
   // font_C.setBold(true);
   // painter.setFont(font_C);
   // painter.drawText(QRect(-60, -60, 120, 120), Qt::AlignCenter, QString::number(currentValue2));//* angle * (500.0/240))

   // QFont font_T("Arial", 20);
   // font_T.setBold(true);
   // painter.setFont(font_T);
   // painter.drawText(QRect(-60, -60, 120, 320), Qt::AlignCenter, QString::number(SGP_Gear + 1));
   // //9.����ǰ��ֵ
   //// drawCurrentSpeed(painter);
   // //10.����ǣ�������Ȧ

   // //11.��LOGO
   //// drawLogo(painter, dashBoad_r);


   // QFont font_T1("Arial", 30);
   // font_T1.setBold(true);
   // painter.setFont(font_T1);
   // painter.drawText(-160, 350, QString::number(IMU.AccelZ, 'f', 4));

   // QFont font_T2("Arial", 30);
   // font_T2.setBold(true);
   // painter.setFont(font_T2);
   // painter.drawText(40, 350, QString::number(IMU.GyroZ, 'f', 4));

   // QFont font_T3("Arial", 30);
   // font_T3.setBold(true);
   // painter.setFont(font_T3);
   // painter.drawText(-160, 500, QString::number(IMU.pitch, 'f', 4));

   // QFont font_T4("Arial", 30);
   // font_T4.setBold(true);
   // painter.setFont(font_T4);
   // painter.drawText(40, 500, QString::number(IMU.roll, 'f', 4));


   // drawEllipseOutSkirts(painter, dashBoad_r + 25);

#endif

 

}
