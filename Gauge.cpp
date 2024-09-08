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
 * 绘制画布
*/
void Gauge::initCanvas(QPainter& painter)
{
    //消除锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //设置底色
   // painter.setBrush(QColor(166, 183, 199));//rgb(166,183,199)
   // painter.setBrush(QColor(0, 0, 0));//rgb(166,183,199)
   // painter.drawRect(rect());
    //平移坐标系原点位置
    //QPoint center(rect().width() / 4, rect().height() * 0.6);
    //painter.translate(center);

}

/*
 * 画小圆
*/
void Gauge::drawMiddleCircle(QPainter& painter, int radius)
{
    //设置画笔颜色和宽度
    painter.setPen(QPen(QColor(255, 255, 255), 3));
    //原点坐标（0，0）绘制半径为radius的圆
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * 画刻度
*/
void Gauge::drawScaleLine(QPainter& painter, int radius, int maxValue, int scale)
{
    //总计60个小刻度，每一个小刻度的角度值
    angle = 240 * 1.0 / scale;

    //float ang = 240 * 1.0 / scale;
    //保存当前坐标
    painter.save();
    painter.setPen(QPen(Qt::white, 3));
    //设置起始刻度位置
    painter.rotate(startAngle);
    //painter.
    for (int i = 0; i <= scale; i++)
    {
        if (i >= (3 * scale / 4))
        {
            //第40个刻度后，绘制画笔修改成红色
            painter.setPen(QPen(Qt::blue, 3));
        }
        if (i % 5 == 0)
        {
            //绘制长刻度
            painter.drawLine(radius + 10, 0, radius - 5, 0);

        }
        else
        {
            //绘制短刻度
            painter.drawLine(radius + 10, 0, radius, 0);
        }
        //绘制完一个刻度旋转一次坐标
        painter.rotate(angle);
    }
    //恢复坐标
    painter.restore();
    painter.setPen(QPen(Qt::white, 5));


}

/*
 * 画刻度值
*/
void Gauge::drawScaleValue(QPainter& painter, int radius, int maxValue, int scale)
{
    //设置字体类型和大小


    QFont textFont("Arial", 12);
    //设置粗体

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
            //保存当前坐标系
            painter.save();
            int delX = qCos((210 - angle * i) * M_PI / 180) * text_r;
            int delY = qSin(qDegreesToRadians(210 - angle * i)) * text_r;
            //平移坐标系
            painter.translate(QPoint(delX, -delY));
            //旋转坐标系
            painter.rotate(-120 + angle * i);
            //写上刻度值，文字居中
            painter.drawText(-25, -50, 50, 30, Qt::AlignCenter, QString::number(i * (maxValue / scale)));
            //恢复坐标系
            painter.restore();
        }
    }
    painter.setPen(QPen(Qt::white, 5));
}

/*
 * 画指针
*/
void Gauge::drawPoint(QPainter& painter, int radius, int maxValue, float value)
{
    //保存当前坐标
    painter.save();
    //设置画刷颜色
    painter.setBrush(Qt::white);
    //设置画笔为无线条
    painter.setPen(Qt::NoPen);
    static const QPointF points[4] = {
        QPointF(0, 0.0),
        QPointF(radius * 2.0 / 3, -1.1),
        QPointF(radius * 2.0 / 3, 1.1),
        QPointF(0, 15.0)
    };
    //坐标选旋转
    painter.rotate(startAngle + value * (240.0 / maxValue));////value * (500.0/240))
    //绘制多边形
    painter.drawPolygon(points, 4);
    //恢复坐标
    painter.restore();
}

/*
 * 画扇形
*/
void Gauge::drawSpeedSector(QPainter& painter, int radius, int maxValue, int value)
{
    //定义矩形区域
    QRect rentangle(-radius, -radius, radius * 2, radius * 2);
    //设置画笔无线条
    painter.setPen(Qt::NoPen);
    //设置画刷颜色
    painter.setBrush(QColor(0, 0, 255, 80));
    //绘制扇形
    painter.drawPie(rentangle, (360 - startAngle) * 16, -value * (240.0 / maxValue) * 16);
}

/*
 * 画渐变内圆
*/
void Gauge::drawInnerEllipse(QPainter& painter, int radius)
{
    QRadialGradient radial(0, 0, radius);
    //中心颜色
    radial.setColorAt(0.0, QColor(0, 0, 255, 200));
    //外围颜色
    radial.setColorAt(1.0, QColor(0, 0, 0, 100));
    //设置画刷渐变色
    painter.setBrush(radial);
    //画圆形
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * 画黑色内圈
*/
void Gauge::drawInnerEllipseBlack(QPainter& painter, int radius)
{
    //设置画刷
    painter.setBrush(Qt::black);
    //绘制圆形
    painter.drawEllipse(QPoint(0, 0), radius, radius);
}

/*
 * 绘制当前数值
*/
void Gauge::drawCurrentSpeed(QPainter& painter)
{
    painter.setPen(Qt::white);
    //绘制数值
    QFont font("Arial", 24);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(-60, -60, 120, 100), Qt::AlignCenter, QString::number(currentValue * 4));
    //绘制单位
    QFont font_u("Arial", 13);
    painter.setFont(font_u);
    painter.drawText(QRect(-60, -60, 120, 160), Qt::AlignCenter, "km/h");

    //QFont font_T("Arial", 40);
    //font_T.setBold(true);
    //painter.setFont(font_T);
    //painter.drawText(QRect(-60, -60, 1000, 100), Qt::AlignCenter, QString::number(5));
}

/*
 * 画外壳，发光外圈
*/
void Gauge::drawEllipseOutSkirts(QPainter& painter, int radius)
{
    //设置扇形绘制区域
    QRect outAngle(-radius, -radius, 2 * radius, 2 * radius);
    painter.setPen(Qt::NoPen);
    //设置渐变色
    QRadialGradient radia(0, 0, radius);
    radia.setColorAt(1, QColor(0, 0, 255, 200));
    radia.setColorAt(0.97, QColor(0, 0, 255, 120));
    radia.setColorAt(0.9, QColor(0, 0, 0, 0));
    radia.setColorAt(0, QColor(0, 0, 0, 0));
    painter.setBrush(radia);
    //绘制圆形
    painter.drawPie(outAngle, (360 - 150) * 16, -240 * 16);
}

/*
 * 画LOGO
*/
void Gauge::drawLogo(QPainter& painter, int radius)
{
    //定义Logo绘制区域
    QRect rectLogo(-65, radius * 0.38, 130, 50);
    painter.drawPixmap(rectLogo, QPixmap("./logo2.png"));
}


/*
 * 重写绘制事件
*/
void Gauge::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);//rgb(166,183,199)



#if 1
    int dashBoad_r = 160;//仪表盘半径
    //1.绘制画布
    initCanvas(painter);


    QPoint center(width()/2, width() / 2);
    painter.translate(center);

    //2.画小圆
    drawMiddleCircle(painter, 30);
    //3.画刻度
    drawScaleLine(painter, dashBoad_r, 240, 60);
    //4.画刻度值
    drawScaleValue(painter, dashBoad_r, 240, 60);
    //5.画指针
    drawPoint(painter, dashBoad_r, 240, currentValue);
    //6.画扇形
    drawSpeedSector(painter, dashBoad_r + 25, 240, currentValue);
    //7.画渐变内圆
    drawInnerEllipse(painter, 110 / 2);
    //8.画黑色内圈
    drawInnerEllipseBlack(painter, 80 / 2);
    //9.画当前数值
   // drawCurrentSpeed(painter);
    painter.setPen(Qt::white);
    //绘制数值
    QFont font("Arial", 20);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(-60, -60, 120, 120), Qt::AlignCenter, QString::number(currentValue));
    //绘制单位
    QFont font_u("Arial", 16);
    font_u.setBold(true);
    painter.setFont(font_u);
    painter.drawText(QRect(-60, -60, 120, 320), Qt::AlignCenter, "km/h");
    //10.画外壳，发光外圈
    drawEllipseOutSkirts(painter, dashBoad_r + 25);



   // QPoint center2(0, 450);
   // painter.translate(center2);
   // drawMiddleCircle(painter, 30);
   // //3.画刻度
   // drawScaleLine(painter, dashBoad_r, 240, 50);
   // //4.画刻度值
   // drawScaleValue(painter, dashBoad_r, 500, 50);
   // //5.画指针
   // drawPoint(painter, dashBoad_r, 500, currentValue2);
   // //6.画扇形
   // drawSpeedSector(painter, dashBoad_r + 25, 500, currentValue2);
   // //7.画渐变内圆
   // drawInnerEllipse(painter, 110 / 2);
   // //8.画黑色内圈
   // drawInnerEllipseBlack(painter, 80 / 2);

   // painter.setPen(Qt::white);
   // // 绘制数值
   // QFont font_C("Arial", 20);
   // font_C.setBold(true);
   // painter.setFont(font_C);
   // painter.drawText(QRect(-60, -60, 120, 120), Qt::AlignCenter, QString::number(currentValue2));//* angle * (500.0/240))

   // QFont font_T("Arial", 20);
   // font_T.setBold(true);
   // painter.setFont(font_T);
   // painter.drawText(QRect(-60, -60, 120, 320), Qt::AlignCenter, QString::number(SGP_Gear + 1));
   // //9.画当前数值
   //// drawCurrentSpeed(painter);
   // //10.画外壳，发光外圈

   // //11.画LOGO
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
