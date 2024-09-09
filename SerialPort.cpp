#include "SerialPort.h"

#include <QVBoxLayout>


SerialPort::SerialPort(QWidget* parent ) : QWidget(parent) {
    setWindowTitle("Serial Port Manager");

 
    // 创建串口选择框
    portSelector = new QComboBox();
    portSelector->setFixedSize(100, 40);
    refreshPorts(); // 初始化时刷新端口列表

    // 创建连接/断开按钮
    connectButton = new QPushButton("Connect");
    connectButton->setFixedSize(100, 40);
    setConnectButtonStyle(false); // 初始为未连接状态

    // 创建发送框
    sendTextEdit = new QTextEdit();
    sendTextEdit->setFixedHeight(100);

    // 创建发送按钮
    sendButton = new QPushButton("Send");
    sendButton->setFixedSize(200, 40);
    sendButton->setEnabled(false); // 初始为禁用状态

    // 创建接收框
    receiveTextEdit = new QTextEdit();
    receiveTextEdit->setReadOnly(true);
    receiveTextEdit->setFixedHeight(100);

    // 创建布局
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

    // 连接按钮点击事件
    connect(connectButton, &QPushButton::clicked, this, &SerialPort::toggleConnection);
    //// 发送按钮点击事件
    //connect(sendButton, &QPushButton::clicked, this, &SerialPort::sendData);

    // 安装事件过滤器以捕获下拉框打开事件
    portSelector->view()->installEventFilter(this);
}



SerialPort::~SerialPort(){

}


void SerialPort::toggleConnection() {
    if (serialPort.isOpen()) {
        // 断开连接
        serialPort.close();
        setConnectButtonStyle(false); // 设置为未连接样式
        connectButton->setText("Connect"); // 更改按钮文本
        sendButton->setEnabled(false); // 禁用发送按钮
       // QMessageBox::information(this, "Connection", "Disconnected from port.");
    }
    else {
        // 尝试连接
        QString portName = portSelector->currentText();
        serialPort.setPortName(portName);
        serialPort.setBaudRate(QSerialPort::Baud115200); // 设置波特率
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);




        if (serialPort.open(QIODevice::ReadWrite)) {
            setConnectButtonStyle(true); // 设置为连接样式
            connectButton->setText("Disconnect"); // 更改按钮文本
            sendButton->setEnabled(true); // 启用发送按钮
           // QMessageBox::information(this, "Connection", "Connected to " + portName);
           // connect(&serialPort, &QSerialPort::readyRead, this, &SerialPort::readData); // 连接读数据信号
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
        //sendTextEdit->clear(); // 清空发送框
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
        receiveTextEdit->append(receivedData); // 将接收到的数据添加到接收框
    }
}

void SerialPort::refreshPorts() {
    portSelector->clear(); // 清空现有的端口列表
    const auto ports = QSerialPortInfo::availablePorts(); // 获取可用串口
    for (const QSerialPortInfo& info : ports) {
        portSelector->addItem(info.portName()); // 添加可用串口到选择框
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
        refreshPorts(); // 刷新可用串口列表
    }
    return QWidget::eventFilter(obj, event);
}