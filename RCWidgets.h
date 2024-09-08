#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RCWidgets.h"
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

class RCWidgets : public QMainWindow
{
    Q_OBJECT

public:
    RCWidgets(QWidget *parent = nullptr);
    ~RCWidgets();
private slots:

   // void processPendingDatagrams();
    void processPendingDatagramsUWB();
private:
    Ui::RCWidgetsClass ui;
    QUdpSocket* udpSocketUWB;
    QString getLocalIP();
    QLabel *IPLabel;

    void parseJsonData(const QString& jsonString);
};
