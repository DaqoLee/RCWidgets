#include "SerialPort.h"

#include <QVBoxLayout>


SerialPort::SerialPort(QWidget* parent ) : QWidget(parent) {
    setWindowTitle("Serial Port Manager");

 
    // ��������ѡ���
    portSelector = new QComboBox();
    portSelector->setFixedSize(100, 40);
    refreshPorts(); // ��ʼ��ʱˢ�¶˿��б�

    // ��������/�Ͽ���ť
    connectButton = new QPushButton("Connect");
    connectButton->setFixedSize(100, 40);
    setConnectButtonStyle(false); // ��ʼΪδ����״̬

    // �������Ϳ�
    sendTextEdit = new QTextEdit();
    sendTextEdit->setFixedHeight(100);

    // �������Ͱ�ť
    sendButton = new QPushButton("Send");
    sendButton->setFixedSize(200, 40);
    sendButton->setEnabled(false); // ��ʼΪ����״̬

    // �������տ�
    receiveTextEdit = new QTextEdit();
    receiveTextEdit->setReadOnly(true);
    receiveTextEdit->setFixedHeight(100);

    // ��������
    QHBoxLayout* hlayout = new QHBoxLayout;
    //layout->addWidget(new QLabel("Select Serial Port:"));
    hlayout->addWidget(portSelector);
    hlayout->addWidget(connectButton);
    //layout->addWidget(new QLabel("Send:"));
    //layout->addWidget(sendTextEdit);
    //layout->addWidget(sendButton);
    //layout->addWidget(new QLabel("Received:"));

    QVBoxLayout* vlayout = new QVBoxLayout();
   
    vlayout->addLayout(hlayout);
    vlayout->addWidget(receiveTextEdit);

    setLayout(vlayout);

    // ���Ӱ�ť����¼�
    connect(connectButton, &QPushButton::clicked, this, &SerialPort::toggleConnection);
    //// ���Ͱ�ť����¼�
    //connect(sendButton, &QPushButton::clicked, this, &SerialPort::sendData);

    // ��װ�¼��������Բ�����������¼�
    portSelector->view()->installEventFilter(this);
}



SerialPort::~SerialPort(){

}


void SerialPort::toggleConnection() {
    if (serialPort.isOpen()) {
        // �Ͽ�����
        serialPort.close();
        setConnectButtonStyle(false); // ����Ϊδ������ʽ
        connectButton->setText("Connect"); // ���İ�ť�ı�
        sendButton->setEnabled(false); // ���÷��Ͱ�ť
       // QMessageBox::information(this, "Connection", "Disconnected from port.");
    }
    else {
        // ��������
        QString portName = portSelector->currentText();
        serialPort.setPortName(portName);
        serialPort.setBaudRate(QSerialPort::Baud115200); // ���ò�����
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);




        if (serialPort.open(QIODevice::ReadWrite)) {
            setConnectButtonStyle(true); // ����Ϊ������ʽ
            connectButton->setText("Disconnect"); // ���İ�ť�ı�
            sendButton->setEnabled(true); // ���÷��Ͱ�ť
           // QMessageBox::information(this, "Connection", "Connected to " + portName);
           // connect(&serialPort, &QSerialPort::readyRead, this, &SerialPort::readData); // ���Ӷ������ź�
            receiveTextEdit->clear();

        }
        else {
            QMessageBox::warning(this, "Connection Error", "Failed to connect to " + portName);
        }
    }
}

void SerialPort::sendData(char *data, int len) {
    if (serialPort.isOpen()) {
        QString text = sendTextEdit->toPlainText();
        serialPort.write(data, len);
        //sendTextEdit->clear(); // ��շ��Ϳ�
        //receiveTextEdit->append(data);
    }
    else
    {
        receiveTextEdit->append("Please connect serial!!!");
    }
}

bool SerialPort::isOpen(){

    bool isOpen = serialPort.isOpen();

    if (isOpen) {
        receiveTextEdit->clear();
    }
    else
    {
        receiveTextEdit->append("Please connect serial!!!"+ isOpen);
    }

    return (isOpen);
}

void SerialPort::readData() {
    if (serialPort.canReadLine()) {
        QString receivedData = QString::fromUtf8(serialPort.readAll());
        receiveTextEdit->append(receivedData); // �����յ���������ӵ����տ�
    }
}

void SerialPort::refreshPorts() {
    portSelector->clear(); // ������еĶ˿��б�
    const auto ports = QSerialPortInfo::availablePorts(); // ��ȡ���ô���
    for (const QSerialPortInfo& info : ports) {
        portSelector->addItem(info.portName()); // ��ӿ��ô��ڵ�ѡ���
    }
}

void SerialPort::setConnectButtonStyle(bool connected) {
    if (connected) {
        connectButton->setStyleSheet("background-color: green; color: white;");
    }
    else {
        connectButton->setStyleSheet("background-color: red; color: white;");
    }
}


bool SerialPort::SerialPort::eventFilter(QObject* obj, QEvent* event)  {
    if (obj == portSelector->view() && event->type() == QEvent::Show) {
        refreshPorts(); // ˢ�¿��ô����б�
    }
    return QWidget::eventFilter(obj, event);
}