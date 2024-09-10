#include "RCWidgets.h"

#include <iostream>


#define MAX_ANGLE 720
#define MAX_BRAKE 32768


uint8_t gear[5] = { 2, 4, 6 , 8, 10 };

uint8_t SGP_Gear = 4;

uint8_t Last_SGP_F = 0;
uint8_t Last_SGP_B = 0;

uint8_t butNum[29] = { 19,20,8,7,6,5,22,23,21,34,33,32,24,37,25,38,36,3,1,2,4,35,13,14,113, 114, 115, 116, 117 };

uint8_t tagID[6] = { 0, 1, 2 , 4 , 3, 5};

typedef struct
{
    union
    {
        uint8_t Data[16];
        struct
        {
            float fSteeringWheelAngle;
            int brake;
            int throttle;
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

MOZA_t mazaData;



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

IMU_t IMU;


RCWidgets::RCWidgets(QWidget *parent)
    : QMainWindow(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint);
    loadSettings();
    ui.setupUi(this);

    //this->setStyleSheet(
    //    "background-color: rgb(30,30,30);"
    //);
  


    SpeeedGauge = new Gauge(240, 60, 240, this);
    SpeeedGauge->setGeometry(0, 0, 480, 480);
    SpeeedGauge->utext = QString("km/h");
    SpeeedGauge->currentValue = 100;


    ChinalGauge = new Gauge(240, 50, 500, this);
    ChinalGauge->currentValue = 200;
    ChinalGauge->utext = QString::number(SGP_Gear + 1);
    ChinalGauge->setGeometry(0, 480, 480, 480);

    Button = new ButtonBar(this);
    Button->setGeometry(0, 1300, 480, 300);

    Map = new RCMap(this);
    Map->setGeometry(480, 0, 600, 1920);

   
    Serial = new SerialPort(this);
    Serial->setGeometry(0, 1650, 240, 240);
  
    moza::installMozaSDK();
    Sleep(5000);

 

    angleSelector = new QComboBox(this);
    angleSelector->setGeometry(260, 1685, 100, 40);
    
    angleSelector->addItem(QString::number(90));
    angleSelector->addItem(QString::number(180));
    angleSelector->addItem(QString::number(360));
    angleSelector->addItem(QString::number(720));
   

    angleSelector->setCurrentText(QString::number(MAX_ANGLE));


    ERRORCODE err = NORMAL;
    err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());

    if (err)
    {
        Serial->receiveTextEdit->append("setMotorLimitAngle " + angleSelector->currentText() + " err:" + QString::number(err));
    }
    else
    {
        Serial->receiveTextEdit->append("setMotorLimitAngle " + angleSelector->currentText());
    }
   


    QObject::connect(angleSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [&](int index) {

            ERRORCODE err = NORMAL;
            err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());
            if (err)
            {
                Serial->receiveTextEdit->append("setMotorLimitAngle " + angleSelector->currentText() + " err:" + QString::number(err));
            }
            else
            {
                Serial->receiveTextEdit->append("setMotorLimitAngle " + angleSelector->currentText());
            }

        });


   // setButton = new QPushButton("OK", this);
   // setButton->setGeometry(370, 1775, 100, 40);
   //// setButton->setStyleSheet("background-color: green; color: white;");

   // connect(setButton, &QPushButton::clicked, [=]() {
   //     
   //     
   //     ERRORCODE err = NORMAL;
   //     err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());
   //    //QString::number(angleSelector->currentText())
   //     
   //     });

    udpSocketUWB = new QUdpSocket(this);
    udpSocketUWB->bind(QHostAddress("192.168.50.30"), 12345); // 绑定到任意地址和端口12345
    connect(udpSocketUWB, &QUdpSocket::readyRead, this, &RCWidgets::processPendingDatagramsUWB);
    timer = new QTimer(this);


    //IPLabel = new QLabel(this);

    //IPLabel->setText(getLocalIP());
    //IPLabel->setGeometry(0, 0, 400, 100);
    //IPLabel->setStyleSheet("background-color: green;");



    connect(timer, &QTimer::timeout, [=]() {


        ERRORCODE err = NORMAL;
        const HIDData* d = moza::getHIDData(err);
        if (d) {

            // mazaData.buttons = 0;

            for (int i = 28; i >= 0; i--)
            {

                // mazaData.buttons |= (d->buttons[butNum[i]].isPressed() << (i));
                 //std::cout << i << ":" << d->buttons[i].isPressed() << " ";
            }

            if (mazaData.SGP_B != Last_SGP_B)
            {
                if (mazaData.SGP_B == 1)
                {
                    SGP_Gear = SGP_Gear >= 4 ? 4 : SGP_Gear + 1;
                }

            }

            if (mazaData.SGP_F != Last_SGP_F)
            {
                if (mazaData.SGP_F == 1)
                {
                    SGP_Gear = SGP_Gear <= 0 ? 0 : SGP_Gear - 1;
                }

            }

            //std::cout << SGP_Gear << std::endl;
            //printf("SGP_Gear:%d \r\n", SGP_Gear + 1);
            if (d->fSteeringWheelAngle >= -(angleSelector->currentText().toInt() / 2) && d->fSteeringWheelAngle <= (angleSelector->currentText().toInt() / 2))
            {
                mazaData.fSteeringWheelAngle = d->fSteeringWheelAngle * 500 / (angleSelector->currentText().toInt() / 2);
            }

            mazaData.brake = (d->brake + MAX_BRAKE) * 500 / (2 * MAX_BRAKE);
            mazaData.throttle = (d->throttle + MAX_BRAKE) * 50 * gear[SGP_Gear] / (2 * MAX_BRAKE);

            Last_SGP_F = mazaData.SGP_F;
            Last_SGP_B = mazaData.SGP_B;

            Serial->sendData((char*)mazaData.Data, 16);

           // serialPort->write((char*)mazaData.Data, 16);

            if (mazaData.brake > 20)
            {
                ChinalGauge->currentValue = mazaData.brake;
            }
            else
            {
               ChinalGauge->currentValue = (d->throttle + MAX_BRAKE) * 500 / (2 * MAX_BRAKE);

            }

        }
        else
        {
            Serial->receiveTextEdit->append("getHIDData err" + QString::number(err));
        }

        SpeeedGauge->currentValue = abs(IMU.speed / 100);

        update();

        });

    timer->start(20);

}

RCWidgets::~RCWidgets(){
    saveSettings();
}


void RCWidgets::loadSettings() {
    QSettings settings("MyCompany", "MyApp");

    // 恢复窗口大小和位置
    resize(settings.value("windowSize", QSize(800, 600)).toSize());
    move(settings.value("windowPos", QPoint(100, 100)).toPoint());
}

void RCWidgets::saveSettings() {
    QSettings settings("MyCompany", "MyApp");

    // 保存窗口大小和位置
    settings.setValue("windowSize", size());
    settings.setValue("windowPos", pos());
}

// 重写 resizeEvent 以保存窗口大小
void RCWidgets::resizeEvent(QResizeEvent* event)  {
    QMainWindow::resizeEvent(event);
    saveSettings(); // 自动保存大小
}

// 重写 moveEvent 以保存窗口位置
void RCWidgets::moveEvent(QMoveEvent* event)  {
    QMainWindow::moveEvent(event);
    saveSettings(); // 自动保存位置
}

void RCWidgets::mousePressEvent(QMouseEvent* event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos;   // 移动后部件所在的位置
}

void RCWidgets::mouseMoveEvent(QMouseEvent* event)
{
    this->move(event->globalPos() - this->dPos);
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

    //std::cout << command.toUtf8();
   
    int ID = jsonObj.value("TagID").toInt();

    Map->Tag[tagID[ID]].imageX = 600 +(jsonObj.value("X").toDouble() * (  33));
    Map->Tag[tagID[ID]].imageY = 1960- (jsonObj.value("Y").toDouble() * 32);
 //   Map->Tag[tagID[ID]].imageZ = jsonObj.value("Z").toDouble();

    //UWB[tagID].x = jsonObj.value("X").toDouble();
    //UWB[tagID].y = jsonObj.value("Y").toDouble();
    //UWB[tagID].z = jsonObj.value("Z").toDouble();
    //imageX[tagID] = abs(UWB[tagID].x) * 60;
    //imageY[tagID] = abs(UWB[tagID].y) * 40;
    //update();

    //double x = jsonObj.value("X").toDouble();
    //double y = jsonObj.value("Y").toDouble();
    //double z = jsonObj.value("Z").toDouble();


    //// 输出解析结果

    //qDebug() << "X:" << x;
    //qDebug() << "Y:" << y;
    //qDebug() << "Z:" << z;
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
            udpSocketUWB->readDatagram((char*)IMU.imuData, 20, &sender, &senderPort);
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



/*
 * 重写绘制事件
*/
void RCWidgets::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);//rgb(166,183,199)

    painter.setBrush(QColor(30, 30, 30));//rgb(166,183,199)
    painter.drawRect(rect());

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::white);
   // painter.setBrush(Qt::white);

    QFont font_T1("Arial", 30);
    font_T1.setBold(true);
    painter.setFont(font_T1);
    painter.drawText(80, 1100, QString::number(IMU.AccelZ, 'f', 4));

    QFont font_T2("Arial", 30);
    font_T2.setBold(true);
    painter.setFont(font_T2);
    painter.drawText(280, 1100, QString::number(IMU.GyroZ, 'f', 4));

    QFont font_T3("Arial", 30);
    font_T3.setBold(true);
    painter.setFont(font_T3);
    painter.drawText(80, 1200, QString::number(IMU.pitch, 'f', 4));

    QFont font_T4("Arial", 30);
    font_T4.setBold(true);
    painter.setFont(font_T4);
    painter.drawText(280, 1200, QString::number(IMU.roll, 'f', 4));

  //  painter.drawRect(rect());

   



}