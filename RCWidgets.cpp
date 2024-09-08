#include "RCWidgets.h"
#include "SerialPort.h"
#include <mozaAPI.h>
#include "RCMap.h"
#include <QtWidgets/QApplication>

#include <QVBoxLayout>
#include <QNetworkInterface>
#include <QHostAddress>

#include"Gauge.h"
#include "ButtonBar.h"



#define MAX_ANGLE 180
#define MAX_BRAKE 32768

RCWidgets::RCWidgets(QWidget *parent)
    : QMainWindow(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint);
    ui.setupUi(this);

    this->setStyleSheet(
        "background-color: rgb(30,30,30);"
    );


    Gauge* SpeeedGauge = new Gauge(this);
    SpeeedGauge->setGeometry(0, 0, 480, 480);

    Gauge* ChinalGauge = new Gauge(this);
    ChinalGauge->setGeometry(0, 520, 480, 480);

    ButtonBar* Button = new ButtonBar(this);
    Button->setGeometry(0, 1000, 480, 100);

    SerialPort* Serial = new SerialPort(this);
    Serial->setGeometry(0, 1740, 240, 240);

    RCMap* Map = new RCMap(this);
    Map->setGeometry(480, 0, 600, 1960);



  
    //moza::installMozaSDK();
    //Sleep(5000);
    //ERRORCODE err = NORMAL;
    //err = moza::setMotorLimitAngle(MAX_ANGLE, MAX_ANGLE);


    //IPLabel = new QLabel(this);

    //IPLabel->setText(getLocalIP());
    //IPLabel->setGeometry(0, 0, 400, 100);
    //IPLabel->setStyleSheet("background-color: green;");

    udpSocketUWB = new QUdpSocket(this);
    udpSocketUWB->bind(QHostAddress("192.168.31.70"), 12345); // 绑定到任意地址和端口12345
    connect(udpSocketUWB, &QUdpSocket::readyRead, this, &RCWidgets::processPendingDatagramsUWB);

}

RCWidgets::~RCWidgets(){

}

QString RCWidgets::getLocalIP() {
    QString ipAddress;

    //const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    //for (const QNetworkInterface& interface : interfaces) {
    //    if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
    //        !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {

    //        const QList<QNetworkAddressEntry> entries = interface.addressEntries();
    //        for (const QNetworkAddressEntry& entry : entries) {
    //            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
    //                ipAddress = entry.ip().toString();
    //                break;
    //            }
    //        }
    //    }
    //    if (!ipAddress.isEmpty()) {
    //        break;
    //    }
    //}

    return ipAddress.isEmpty() ? "No IP Address found" : ipAddress;
}




void RCWidgets::parseJsonData(const QString& jsonString) {
    // 将 JSON 字符串转换为 QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    // 检查是否成功解析
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to create JSON doc.";
        //IPLabel->setText("Failed to create JSON doc.");

        return;
    }
    // 确保是一个对象
    if (!jsonDoc.isObject()) {
        qDebug() << "JSON is not an object.";
        //IPLabel->setText("JSON is not an object");
        return;
    }
    // 获取 JSON 对象
    QJsonObject jsonObj = jsonDoc.object();

    // 解析各个字段
    QString command = jsonObj.value("Command").toString();
    IPLabel->setText(command);

    //std::cout << command.toUtf8();
   
    int tagID = jsonObj.value("TagID").toInt();
    //UWB[tagID].x = jsonObj.value("X").toDouble();
    //UWB[tagID].y = jsonObj.value("Y").toDouble();
    //UWB[tagID].z = jsonObj.value("Z").toDouble();
    //imageX[tagID] = abs(UWB[tagID].x) * 60;
    //imageY[tagID] = abs(UWB[tagID].y) * 40;
    //update();

    double x = jsonObj.value("X").toDouble();
    double y = jsonObj.value("Y").toDouble();
    double z = jsonObj.value("Z").toDouble();


    // 输出解析结果

    qDebug() << "X:" << x;
    qDebug() << "Y:" << y;
    qDebug() << "Z:" << z;
}


void RCWidgets::processPendingDatagramsUWB() {
    while (udpSocketUWB->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketUWB->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        // 读取数据

      //  qDebug() << "Z:" << datagram.size();

        if (datagram.size() == 22)
        {
         //   udpSocketUWB->readDatagram((char*)IMU.imuData, 20, &sender, &senderPort);
        }
        else
        {
            udpSocketUWB->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            QString jsonString(datagram);

         //   IPLabel->setText(jsonString);
            parseJsonData(jsonString);
        }


        // 解析接收到的 JSON 数据

    }
}