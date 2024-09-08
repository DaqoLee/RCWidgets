#include "ButtonBar.h"

#include <QVBoxLayout>


ButtonBar::ButtonBar(QWidget* parent) : QWidget(parent) {
  
    //setWindowTitle("Serial Port Manager");


    TextEdit1 = new QTextEdit();
    TextEdit1->setFixedHeight(40);

    TextEdit2 = new QTextEdit();
    TextEdit2->setFixedHeight(40);

    // 创建发送按钮
    sendButton1 = new QPushButton("Send");
    sendButton1->setFixedSize(100, 100);
   // sendButton1->setEnabled(false); // 初始为禁用状态



    // 创建发送框
    TextEdit3 = new QTextEdit();
    TextEdit3->setFixedHeight(40);

    TextEdit4 = new QTextEdit();
    TextEdit4->setFixedHeight(40);

    // 创建发送按钮
    sendButton2 = new QPushButton("Send");
    sendButton2->setFixedSize(100, 100);
   // sendButton2->setEnabled(false); // 初始为禁用状态



    QVBoxLayout* vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(TextEdit1);
    vlayout1->addWidget(TextEdit2);
    QHBoxLayout* hlayout1 = new QHBoxLayout;
    hlayout1->addLayout(vlayout1);
    hlayout1->addWidget(sendButton1);

    QVBoxLayout* vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(TextEdit3);
    vlayout2->addWidget(TextEdit4);
    QHBoxLayout* hlayout2 = new QHBoxLayout;
    hlayout2->addLayout(vlayout2);
    hlayout2->addWidget(sendButton2);

    QHBoxLayout* hlayout3 = new QHBoxLayout;
    hlayout3->addLayout(hlayout1);
    hlayout3->addLayout(hlayout2);




    setLayout(hlayout3);

    // 连接按钮点击事件
   // connect(connectButton, &QPushButton::clicked, this, &ButtonBar::toggleConnection);
    //// 发送按钮点击事件
    //connect(sendButton, &QPushButton::clicked, this, &ButtonBar::sendData);

    // 安装事件过滤器以捕获下拉框打开事件
  //  portSelector->view()->installEventFilter(this);
}



ButtonBar::~ButtonBar() {

}


void ButtonBar::toggleConnection() {

}

void ButtonBar::sendData() {

}

void ButtonBar::readData() {

}

void ButtonBar::refreshPorts() {

}

void ButtonBar::setConnectButtonStyle(bool connected) {
    if (connected) {
        connectButton->setStyleSheet("background-color: green; color: white;");
    }
    else {
        connectButton->setStyleSheet("background-color: red; color: white;");
    }
}

