#include "RCWidgets.h"


#define MAX_ANGLE 720
#define MAX_BRAKE 32768


uint8_t gear[5] = { 2, 4, 6 , 8, 10 };

uint8_t SGP_Gear = 4;

uint8_t Last_SGP_F = 0;
uint8_t Last_SGP_B = 0;
uint8_t Last_SGP_S1 = 0;
uint8_t Last_SGP_S2 = 0;
uint8_t Last_SGP_S3 = 0;


uint8_t butNum[29] = { 19,20,8,7,6,5,22,23,21,34,33,32,24,37,25,38,36,3,1,2,4,35,13,14,113, 114, 115, 116, 117 };

uint8_t tagID[6] = { 0, 1, 2 , 3 , 1, 5};




MOZA_t mozaData;

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
  
    maxUWBX = 17.56;
    maxUWBY = 62.2;

    debugTextEdit = new QTextEdit(this);
    debugTextEdit->setReadOnly(true);
    debugTextEdit->setGeometry(240, 1755, 230, 100);


    QString myIPAdress = getLocalIP();
    debugTextEdit->append(myIPAdress + ":12345");

    QStringList ipParts = myIPAdress.split('.');
    int lastNumber = 0;

    // ���ָ����Ƿ���Ч
    if (ipParts.size() == 4) { // ȷ����һ����Ч�� IPv4 ��ַ
        // ��ȡ���һ���ֲ�ת��Ϊ����
        bool ok;
        lastNumber = ipParts.last().toInt(&ok); // toInt �������Է���һ������ֵ��ʾת���Ƿ�ɹ�

        if (ok) { // ���ת���ɹ�

            debugTextEdit->append( "IP lastNumber:" + QString::number(lastNumber));
        }
        else {
            debugTextEdit->append("err");
        }
    }
    else {
        debugTextEdit->append("NO IPAdress��");
    }

    QString sPort;
    int maxAngle;

    switch (lastNumber)
    {
    case 30:

        sPort = "COM4";
        maxAngle = 360;

        break;

    case 70:
        sPort = "COM11";
        maxAngle = 360;
        break;
    case 75:

        sPort = "COM12";
        maxAngle = 360;

        break;
    case 208:
        sPort = "COM18";
        maxAngle = 180;

        break;

    case 13:
        sPort = "COM4";
        maxAngle = 180;

        break;

    default:

        sPort = "COM11";
        maxAngle = 360;
        break;
    }

    SpeeedGauge = new Gauge(240, 60, 120, this);
    SpeeedGauge->setGeometry(0, 0, 480, 480);
    SpeeedGauge->utext = QString("km/h");
    SpeeedGauge->currentValue = 0;


    ChinalGauge = new Gauge(240, 50, 500, this);
    ChinalGauge->currentValue = 200;
    ChinalGauge->utext = QString::number(SGP_Gear + 1);
    ChinalGauge->setGeometry(0, 480, 480, 480);

    Button = new ButtonBar(this);
    Button->setGeometry(0, 1300, 480, 300);

    Map = new RCMap(this);
    Map->setGeometry(480, 0, 600, 1920);

   
    Serial = new SerialPort(this, sPort);
    Serial->setGeometry(0, 1650, 240, 240);
  
    moza::installMozaSDK();
    Sleep(5000);


    //debugTextEdit->setStyleSheet("background-color: green; color: white;");

    angleSelector = new QComboBox(this);
    angleSelector->setGeometry(370, 1685, 100, 40);
    
    angleSelector->addItem(QString::number(90));
    angleSelector->addItem(QString::number(180));
    angleSelector->addItem(QString::number(360));
    angleSelector->addItem(QString::number(720));
   

    angleSelector->setCurrentText(QString::number(maxAngle));

    setButton = new QPushButton("Steering Angle", this);
    setButton->setGeometry(240, 1685, 120, 40);


    udpSocketUWB = new QUdpSocket(this);
    udpSocketUWB->bind(QHostAddress(myIPAdress), 12345); // �󶨵������ַ�Ͷ˿�12345  //192.168.50.30
    connect(udpSocketUWB, &QUdpSocket::readyRead, this, &RCWidgets::processPendingDatagramsUWB);

    timer = new QTimer(this);


    //QSpinBox* spinBox = new QSpinBox(this);

    //spinBox->setRange(0, 100); // ���÷�Χ
    //spinBox->setValue(50); // ���ó�ʼֵ

    //spinBox->setGeometry(240, 1585, 120, 40);

    ERRORCODE err = NORMAL;
    err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());
    if (err)
    {
        debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText() + " err:" + QString::number(err));
        setButton->setStyleSheet("background-color: red; color: white;");
    }
    else
    {
        debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText());
        setButton->setStyleSheet("background-color: green; color: white;");
    }
   


    QObject::connect(angleSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [&](int index) {

            ERRORCODE err = NORMAL;
            err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());
            if (err)
            {
                debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText() + " err:" + QString::number(err));
                setButton->setStyleSheet("background-color: red; color: white;");
            }
            else
            {
                debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText());
                setButton->setStyleSheet("background-color: green; color: white;");
            }

        });



  //  debugTextEdit->append(QString::number(Map->width()) +"    " + QString::number(Map->height()));

   // setButton->setStyleSheet("background-color: green; color: white;");

    connect(setButton, &QPushButton::clicked, [=]() {
        
        
        ERRORCODE err = NORMAL;
        err = moza::setMotorLimitAngle(angleSelector->currentText().toInt(), angleSelector->currentText().toInt());
        if (err)
        {
            debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText() + " err:" + QString::number(err));
            setButton->setStyleSheet("background-color: red; color: white;");
        }
        else
        {
            debugTextEdit->append("setMotorLimitAngle " + angleSelector->currentText());
            setButton->setStyleSheet("background-color: green; color: white;");
        }
        });


    //IPLabel = new QLabel(this);

    //IPLabel->setText(getLocalIP());
    //IPLabel->setGeometry(0, 0, 400, 100);
    //IPLabel->setStyleSheet("background-color: green;");



    connect(timer, &QTimer::timeout, [=]() {


        ERRORCODE err = NORMAL;
#if 1
        const HIDData* d = moza::getHIDData(err);
        if (d) {

             //mozaData.buttons = 0;

            for (int i = 28; i >= 4; i--)
            {

                 mozaData.buttons |= (d->buttons[butNum[i]].isPressed() << (i));
                 //std::cout << i << ":" << d->buttons[i].isPressed() << " ";
            }

           // debugTextEdit->append("SGP_B " + QString::number(mozaData.SGP_B));
          //  if (mozaData.SGP_B != Last_SGP_B)
            {
                if (mozaData.SGP_B == 1)
                {
                   Button->sendButton[0]->setStyleSheet("background-color: green; color: white;");
                   Button->sendButton[0]->setText("1000"); // ���İ�ť�ı�
                   mozaData.N = 1;
                    //SGP_Gear = SGP_Gear >= 4 ? 4 : SGP_Gear + 1;
                    //static bool isClicked = true;

                    //if (isClicked) {
                    //    Button->sendButton[0]->setStyleSheet("background-color: green; color: white;");
                    //    Button->sendButton[0]->setText("1000"); // ���İ�ť�ı�
                    //    mozaData.N = 1;
                    //}
                    //else {
                    //    Button->sendButton[0]->setStyleSheet("background-color: gray; color: white;");
                    //    Button->sendButton[0]->setText("0"); // ���İ�ť�ı�
                    //    mozaData.N = 0;
                    //}
                    //isClicked = !isClicked;
                }
                else
                {
                    Button->sendButton[0]->setStyleSheet("background-color: gray; color: white;");
                    Button->sendButton[0]->setText("0"); // ���İ�ť�ı�
                    mozaData.N = 0;

                }
         

            }

            if (mozaData.SGP_F != Last_SGP_F)
            {
                if (mozaData.SGP_F == 1)
                {
                    //SGP_Gear = SGP_Gear <= 0 ? 0 : SGP_Gear - 1;

                    static bool isClicked1 = true;

                    if (isClicked1) {
                        Button->sendButton[1]->setStyleSheet("background-color: green; color: white;");
                        Button->sendButton[1]->setText("1000"); // ���İ�ť�ı�
                        mozaData.WIP = 1;
                    }
                    else {
                        Button->sendButton[1]->setStyleSheet("background-color: gray; color: white;");
                        Button->sendButton[1]->setText("0"); // ���İ�ť�ı�
                        mozaData.WIP = 0;
                    }
                    isClicked1 = !isClicked1;
                }

            }


            Last_SGP_F = mozaData.SGP_F;
            Last_SGP_B = mozaData.SGP_B;
            Last_SGP_S1 = mozaData.SGP_S1;


            //std::cout << SGP_Gear << std::endl;
            //printf("SGP_Gear:%d \r\n", SGP_Gear + 1);
            if (d->fSteeringWheelAngle >= -(angleSelector->currentText().toInt() / 2) && d->fSteeringWheelAngle <= (angleSelector->currentText().toInt() / 2))
            {
                mozaData.fSteeringWheelAngle = d->fSteeringWheelAngle * 500 / (angleSelector->currentText().toInt() / 2);
            }

            mozaData.brake = (d->brake + MAX_BRAKE) * 500 / (2 * MAX_BRAKE);
            mozaData.throttle = (d->throttle + MAX_BRAKE) * 50 * gear[SGP_Gear] / (2 * MAX_BRAKE);


            ChinalGauge->utext = QString::number(SGP_Gear + 1);

//
            //if (mozaData.SGP_B)
            //{
            //    static bool isClicked = true;

            //    if (isClicked) {
            //        Button->sendButton[0]->setStyleSheet("background-color: green; color: white;");
            //        Button->sendButton[0]->setText("1000"); // ���İ�ť�ı�
            //        mozaData.N = 1;
            //    }
            //    else {
            //        Button->sendButton[0]->setStyleSheet("background-color: gray; color: white;");
            //        Button->sendButton[0]->setText("0"); // ���İ�ť�ı�
            //        mozaData.N = 0;
            //    }
            //    isClicked = !isClicked;

            //    //
            //}


            //if (d->throttle > 20)
            //{
            //    if ((IMU.speed / 100) > 80)
            //    {
            //        SpeeedGauge->currentValue = abs(80 + ((int)IMU.speed % 10));
            //    }
            //    else
            //    {
            //        SpeeedGauge->currentValue = abs(IMU.speed / 100);
            //    }

            //}
            //else
            //{
            //    if ((IMU.speed / 100) > 60)
            //    {
            //        SpeeedGauge->currentValue = abs(60 + ((int)IMU.speed % 10));
            //    }
            //    else
            //    {
            //        SpeeedGauge->currentValue = abs(IMU.speed / 100);
            //    }
            //    //SpeeedGauge->currentValue = abs(((int)IMU.speed / 100)%60);
            //}

            if (mozaData.brake > 20)
            {
                ChinalGauge->currentValue = mozaData.brake;
            }
            else
            {
               ChinalGauge->currentValue = (d->throttle + MAX_BRAKE) * 500 / (2 * MAX_BRAKE);

            }

            Serial->sendData((char*)mozaData.Data, sizeof(mozaData.Data));


            mozaData.SGP_B = 0;
            mozaData.SGP_F = 0;
           // mozaData.buttons = 0;

        }
        else
        {
            debugTextEdit->append("getHIDData err" + QString::number(err));
        }
#endif
       // Serial->sendData((char*)mozaData.Data, sizeof(mozaData.Data));

        update();

        });

    timer->start(20);

}

RCWidgets::~RCWidgets(){
    saveSettings();
}



QString RCWidgets::getLocalIP() {
    QString ipAddress;  // ��ʼ��һ���յ��ַ��������ڴ洢�ҵ���IP��ַ

    // ��ȡϵͳ����������ӿ�
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    // ����ÿ������ӿ�
    for (const QNetworkInterface& netInterface : interfaces) { // �� interface ��Ϊ netInterface
        // ���ӿ��Ƿ��ڻ״̬�Ҳ��ǻ��ؽӿ�
        if (netInterface.flags().testFlag(QNetworkInterface::IsUp) &&  // ���ӿ��Ƿ�Ϊ�����״̬
            !netInterface.flags().testFlag(QNetworkInterface::IsLoopBack)) { // ���ӿ��Ƿ�Ϊ���ؽӿڣ���localhost��

            // ��ȡ�ӿڵĵ�ַ��Ŀ��IPv4 �� IPv6 ��ַ��
            const QList<QNetworkAddressEntry> entries = netInterface.addressEntries();
            // �����ӿڵ����е�ַ��Ŀ
            for (const QNetworkAddressEntry& entry : entries) {
                // ����Ƿ�����Ч�� IPv4 ��ַ�����Ҳ��ǿյ�ַ
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && // ����ַЭ���Ƿ�ΪIPv4
                    entry.ip() != QHostAddress::Null && // ȷ����ַ���ǿյ�ַ
                    entry.ip() != QHostAddress::Any) { // ȷ����ַ���ǡ��κε�ַ��

                    ipAddress = entry.ip().toString(); // ���ҵ���IPv4��ַת��Ϊ�ַ���
                    break; // �ҵ���һ����Ч��IPv4��ַ���˳��ڲ�ѭ��
                }
            }
        }
        // ������ҵ�IP��ַ�����˳����ѭ��
        if (!ipAddress.isEmpty()) {
            break; // �ҵ�IP���˳��ⲿѭ��
        }
    }

    // ���δ�ҵ�IP��ַ������Ĭ����Ϣ�����򷵻��ҵ���IP��ַ
    return ipAddress.isEmpty() ? "No IP Address found" : ipAddress;
}



void RCWidgets::loadSettings() {
    QSettings settings("MyCompany", "MyApp");

    // �ָ����ڴ�С��λ��
    resize(settings.value("windowSize", QSize(800, 600)).toSize());
    move(settings.value("windowPos", QPoint(100, 100)).toPoint());
}

void RCWidgets::saveSettings() {
    QSettings settings("MyCompany", "MyApp");

    // ���洰�ڴ�С��λ��
    settings.setValue("windowSize", size());
    settings.setValue("windowPos", pos());
}

// ��д resizeEvent �Ա��洰�ڴ�С
void RCWidgets::resizeEvent(QResizeEvent* event)  {
    QMainWindow::resizeEvent(event);
    saveSettings(); // �Զ������С
}

// ��д moveEvent �Ա��洰��λ��
void RCWidgets::moveEvent(QMoveEvent* event)  {
    QMainWindow::moveEvent(event);
    saveSettings(); // �Զ�����λ��
}

void RCWidgets::mousePressEvent(QMouseEvent* event)
{
    //this->windowPos = this->pos();       // ��ò�����ǰλ��
    //this->mousePos = event->globalPos(); // ������λ��
    //this->dPos = mousePos - windowPos;   // �ƶ��󲿼����ڵ�λ��
}

void RCWidgets::mouseMoveEvent(QMouseEvent* event)
{
  //  this->move(event->globalPos() - this->dPos);
}


double time_now, time_end;
double xp = 0.0, yp = 0.0, xp_last = 0.0, yp_last = 0.0;


void RCWidgets::parseJsonData(const QString& jsonString) {
    // �� JSON �ַ���ת��Ϊ QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    // ����Ƿ�ɹ�����
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to create JSON doc.";

        return;
    }
    // ȷ����һ������
    if (!jsonDoc.isObject()) {
        qDebug() << "JSON is not an object.";
        //IPLabel->setText("JSON is not an object");
        return;
    }
    // ��ȡ JSON ����
    QJsonObject jsonObj = jsonDoc.object();

    // ���������ֶ�
    QString command = jsonObj.value("Command").toString();

    //std::cout << command.toUtf8();
   
    int ID = jsonObj.value("TagID").toInt();

    Map->Tag[tagID[ID]].imageX = Map->width() +(jsonObj.value("X").toDouble() * ((float)(Map->width() + 0.5f)/maxUWBX));
    Map->Tag[tagID[ID]].imageY = Map->height() - (jsonObj.value("Y").toDouble() * ((float)(Map->height() + 0.5f)/maxUWBY));
 //   Map->Tag[tagID[ID]].imageZ = jsonObj.value("Z").toDouble();

    if (ID == 4) {

        time_now = clock();

        xp = jsonObj.value("X").toDouble(), yp = jsonObj.value("Y").toDouble();

        if (time_now != time_end) {
            double speed = sqrt((xp - xp_last) * (xp - xp_last) + (yp - yp_last) * (yp - yp_last)) / (time_now - time_end);
            if (speed * 1000 * 3.6 < 80 && (abs(IMU.AccelZ) > 0.1)) {
                SpeeedGauge->currentValue = speed * 1000 * 3.6;
            }

        }


        debugTextEdit->append(QString::number(time_now - time_end) + ":" + QString::number(ID) + ":" + QString::number(xp) + "," + QString::number(yp) + ":" + QString::number(xp - xp_last) + "," + QString::number(yp - yp_last));

        xp_last = xp;
        yp_last = yp;


        time_end = clock();

    }

    //UWB[tagID].x = jsonObj.value("X").toDouble();
    //UWB[tagID].y = jsonObj.value("Y").toDouble();
    //UWB[tagID].z = jsonObj.value("Z").toDouble();
    //imageX[tagID] = abs(UWB[tagID].x) * 60;
    //imageY[tagID] = abs(UWB[tagID].y) * 40;
    //update();

    //double x = jsonObj.value("X").toDouble();
    //double y = jsonObj.value("Y").toDouble();
    //double z = jsonObj.value("Z").toDouble();


    //// ����������

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

        // ��ȡ����

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


        // �������յ��� JSON ����

    }
}



/*
 * ��д�����¼�
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