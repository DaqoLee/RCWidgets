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

class RCWidgets : public QMainWindow
{
    Q_OBJECT

public:
    RCWidgets(QWidget *parent = nullptr);
    ~RCWidgets();
private slots:

   // void processPendingDatagrams();
    void processPendingDatagramsUWB();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;

private:




    Ui::RCWidgetsClass ui;
    QUdpSocket* udpSocketUWB;
    QString getLocalIP();
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


    void loadSettings();
    void saveSettings();

    void parseJsonData(const QString& jsonString);
    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};
