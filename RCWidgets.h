#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RCWidgets.h"
#include <QLabel>

#include<QPoint.h>
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

#include <mozaAPI.h>

#include "SerialPort.h"

#include "RCMap.h"
#include <QtWidgets/QApplication>

#include <QVBoxLayout>
#include <QNetworkInterface>
#include <QHostAddress>

#include"Gauge.h"
#include "ButtonBar.h"


#include <QtCore/QVariant>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>




#include <iostream>
#include <QtWidgets/QApplication>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkInterface>
#include <QHostAddress>
#include< combaseapi.h>


#include <QNetworkAddressEntry>
#include <QAbstractSocket>



typedef struct
{
    union
    {
        uint8_t Data[20];
        struct
        {
            float fSteeringWheelAngle;
            int brake;
            int throttle;
            int ch;
            union
            {
                uint32_t buttons;
                struct
                {
                    uint32_t N : 1;
                    uint32_t WIP : 1;
                    uint32_t L : 1;
                    uint32_t D : 1;
                    uint32_t Ri : 1;
                    uint32_t U : 1;
                    uint32_t CAM : 1;
                    uint32_t RADIO : 1;
                    uint32_t FL : 1;
                    uint32_t PL : 1;
                    uint32_t BOX : 1;
                    uint32_t P : 1;
                    uint32_t S1 : 1;
                    uint32_t S2 : 1;
                    uint32_t HOME : 1;
                    uint32_t MENU : 1;
                    uint32_t START : 1;
                    uint32_t X : 1;
                    uint32_t A : 1;
                    uint32_t B : 1;
                    uint32_t Y : 1;
                    uint32_t R : 1;
                    uint32_t LG : 1;
                    uint32_t RG : 1;
                    uint32_t SGP_F : 1;
                    uint32_t SGP_B : 1;
                    uint32_t SGP_S1 : 1;
                    uint32_t SGP_S2 : 1;
                    uint32_t SGP_S3 : 1;

                    uint32_t Other : 3;
                    /* data */
                };

            };
        };

    };
}MOZA_t;


typedef struct
{
    union
    {
        uint8_t imuData[20];
        struct
        {

            // float AccelX;
            // float AccelY;
            float AccelZ;

            // float GyroX;
            // float GyroY;
            float GyroZ;

            float roll;
            float pitch;
            //  float yaw;

            float speed;
        };

    };
}IMU_t;

extern IMU_t IMU;

extern MOZA_t mozaData;


class RCWidgets : public QMainWindow
{
    Q_OBJECT

public:




    RCWidgets(QWidget *parent = nullptr);
    ~RCWidgets();
     QString getLocalIP() ;
private slots:

   // void processPendingDatagrams();
    void processPendingDatagramsUWB();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;

private:




    Ui::RCWidgetsClass ui;
    QUdpSocket* udpSocketUWB;
    QLabel *IPLabel;
    QTimer* timer;

    SerialPort* Serial;
    Gauge* SpeeedGauge;
    Gauge* ChinalGauge;
    RCMap* Map;
    ButtonBar* Button;

    QComboBox* angleSelector;
    QPushButton* setButton;
    
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

    QTextEdit* debugTextEdit;

    float maxUWBX;
    float maxUWBY;

    void loadSettings();
    void saveSettings();

    void parseJsonData(const QString& jsonString);
    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};
