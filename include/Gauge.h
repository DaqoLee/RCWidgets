#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>


#include <QWidget>

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtMath>
#include <Qpushbutton.h>
#include <QUdpSocket>
#include <QWidget>
#include <QHostAddress>
#include <QString>
#include <QStringList>
#include<QSerialPort>
#include<QSerialPortInfo>

#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>


#include <QMessageBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QTextEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include< combaseapi.h>

namespace Ui {
    class Gauge;
}

class Gauge : public QWidget
{
    Q_OBJECT

public:
    Gauge(int _maxAngle, int _scale, int _maxValue, QWidget* parent = nullptr);
    ~Gauge();

    int scale;
   // int radius;
    int maxValue;
    int maxAngle;
    int currentValue;//��ǰֵ
    QString utext;
private slots:


private:

    int startAngle;//��ʼ�Ƕ�
    double angle;
//    int currentValue;//��ǰֵ
  //  int currentValue2;
    QTimer* timer;
    bool flag;//ָ��ת����־λ

   // Ui::Gauge* ui;

    void initCanvas(QPainter& painter);
    void drawScaleLine(QPainter& painter, int radius);
    void drawScaleValue(QPainter& painter, int radius);
    void drawPoint(QPainter& painter, int radius);
    void drawMiddleCircle(QPainter& painter, int radius);
    void drawSpeedSector(QPainter& painter, int radius);
    void drawInnerEllipse(QPainter& painter, int radius);
    void drawInnerEllipseBlack(QPainter& painter, int radius);
    void drawCurrentSpeed(QPainter& painter);
    void drawEllipseOutSkirts(QPainter& painter, int radius);
    void drawLogo(QPainter& painter, int radius);

    void paintEvent(QPaintEvent* event) override;
};
