#include "ButtonBar.h"

#include <QVBoxLayout>
#include "RCWidgets.h"



ButtonBar::ButtonBar(QWidget* parent) : QWidget(parent) {
  
    //setWindowTitle("Serial Port Manager");


    //TextEdit1 = new QLabel("0");
    //TextEdit1->setFixedHeight(40);
    //TextEdit1->setFixedWidth(50);
    //TextEdit1->setStyleSheet("background-color: green; color: white;");

    //TextEdit2 = new QLabel("1000");
    //TextEdit2->setFixedHeight(40);
    //TextEdit2->setFixedWidth(50);
    //TextEdit2->setStyleSheet("background-color: lightgray; color: white;");

    //// 创建发送按钮
    //sendButton1 = new QPushButton("Send");
    //sendButton1->setFixedSize(60, 100);
   // sendButton1->setEnabled(false); // 初始为禁用状态



    for (int i = 0; i < 3; i++)
    {
        sendButton[i] = new QPushButton("0");
        sendButton[i]->setFixedSize(150, 80);
        sendButton[i]->setStyleSheet("background-color: gray; color: white;");
    }

    QHBoxLayout* hlayout1 = new QHBoxLayout();

    for (int i = 0; i < 3; i++)
    {
        hlayout1->addWidget(sendButton[i]);
       
    }

      QObject::connect(sendButton[0], &QPushButton::clicked, [=]() {

        static bool isClicked = true;
        
        if (isClicked) {
            sendButton[0]->setStyleSheet("background-color: green; color: white;");
            sendButton[0]->setText("1000"); // 更改按钮文本
            mozaData.N = 1;
        }
        else {
            sendButton[0]->setStyleSheet("background-color: gray; color: white;");
            sendButton[0]->setText("0"); // 更改按钮文本
            mozaData.N = 0;
        }
        isClicked = !isClicked;

        
        });


    QObject::connect(sendButton[0], &QPushButton::clicked, [=]() {

        static bool isClicked = true;
        
        if (isClicked) {
            sendButton[0]->setStyleSheet("background-color: green; color: white;");
            sendButton[0]->setText("1000"); // 更改按钮文本
            mozaData.N = 1;
        }
        else {
            sendButton[0]->setStyleSheet("background-color: gray; color: white;");
            sendButton[0]->setText("0"); // 更改按钮文本
            mozaData.N = 0;
        }
        isClicked = !isClicked;

        
        });

    QObject::connect(sendButton[1], &QPushButton::clicked, [=]() {

        static bool isClicked = true;

        if (isClicked) {
            sendButton[1]->setStyleSheet("background-color: green; color: white;");
            sendButton[1]->setText("1000"); // 更改按钮文本
            mozaData.WIP = 1;
            
        }
        else {
            sendButton[1]->setStyleSheet("background-color: gray; color: white;");
            sendButton[1]->setText("0"); // 更改按钮文本
            mozaData.WIP = 0;
        }
        isClicked = !isClicked;


        });

    QObject::connect(sendButton[2], &QPushButton::clicked, [=]() {

        static bool isClicked = true;

        if (isClicked) {
            sendButton[2]->setStyleSheet("background-color: green; color: white;");
            sendButton[2]->setText("1000"); // 更改按钮文本
            mozaData.L = 1;
        }
        else {
            sendButton[2]->setStyleSheet("background-color: gray; color: white;");
            sendButton[2]->setText("0"); // 更改按钮文本
            mozaData.L = 0;
        }
        isClicked = !isClicked;


        });
  
    //QHBoxLayout* hlayout2 = new QHBoxLayout();

    //for (int i = 3; i < 6; i++)
    //{
    //    hlayout2->addWidget(sendButton[i]);

    //}
    //QVBoxLayout* vlayout1 = new QVBoxLayout();
    //vlayout1->addLayout(hlayout1);
    //vlayout1->addLayout(hlayout2);
    //setLayout(vlayout1);

   //  //创建发送框
   // TextEdit3 = new QLabel("0");
   // TextEdit3->setFixedHeight(40);
   // TextEdit3->setFixedWidth(60);
   // TextEdit3->setStyleSheet("background-color: green; color: white;");

   // TextEdit4 = new QLabel("1000");
   // TextEdit4->setFixedHeight(40);
   // TextEdit4->setFixedWidth(60);
   // TextEdit4->setStyleSheet("background-color: lightgray; color: white;");

   //  //创建发送按钮
   // sendButton2 = new QPushButton("Send");
   // sendButton2->setFixedSize(60, 100);
   //// sendButton2->setEnabled(false); // 初始为禁用状态


   // TextEdit5 = new QLabel("0");
   // TextEdit5->setFixedHeight(40);
   // TextEdit5->setFixedWidth(60);
   // TextEdit5->setStyleSheet("background-color: green; color: white;");

   // TextEdit6 = new QLabel("1000");
   // TextEdit6->setFixedHeight(40);
   // TextEdit6->setFixedWidth(60);
   // TextEdit6->setStyleSheet("background-color: lightgray; color: white;");

   // //创建发送按钮
   // sendButton3 = new QPushButton("Send");
   // sendButton3->setFixedSize(60, 100);
   //// sendButton3->setEnabled(false); // 初始为禁用状态



   // QVBoxLayout* vlayout1 = new QVBoxLayout();
   // vlayout1->addWidget(TextEdit1);
   // vlayout1->addWidget(TextEdit2);
   // QHBoxLayout* hlayout1 = new QHBoxLayout;
   // hlayout1->addLayout(vlayout1);
   // hlayout1->addWidget(sendButton1);

   // QVBoxLayout* vlayout2 = new QVBoxLayout();
   // vlayout2->addWidget(TextEdit3);
   // vlayout2->addWidget(TextEdit4);
   // QHBoxLayout* hlayout2 = new QHBoxLayout;
   // hlayout2->addLayout(vlayout2);
   // hlayout2->addWidget(sendButton2);

   // QVBoxLayout* vlayout3 = new QVBoxLayout();
   // vlayout3->addWidget(TextEdit5);
   // vlayout3->addWidget(TextEdit6);
   // QHBoxLayout* hlayout3 = new QHBoxLayout;
   // hlayout3->addLayout(vlayout3);
   // hlayout3->addWidget(sendButton3);




   // QHBoxLayout* hlayout4 = new QHBoxLayout;
   // hlayout4->addLayout(hlayout1);
   // hlayout4->addLayout(hlayout2);
   // hlayout4->addLayout(hlayout3);
   // hlayout4->addWidget(slider);

    QHBoxLayout* hlayout5 = new QHBoxLayout;


        // 创建 QLabel 用于显示滑条的值
    label = new QLabel("0");
    label->setFixedWidth(30);

    slider = new QSlider(Qt::Horizontal); // 创建水平滑条

    slider->setRange(-500, 500); // 设置范围
    slider->setValue(-500);     // 设置初始值


    // 自定义滑条的大小和颜色
    slider->setFixedHeight(40); // 设置滑条的高度

    // 使用样式表设置滑条的颜色
    slider->setStyleSheet(
        "QSlider {"
        "   background: lightgray;"    // 背景颜色，表示未滑过的部分
        "   border-radius: 5px;"
       
        "}"
        "QSlider::handle {"
        "   background: white;"         // 滑块颜色
        "   width: 40px;"              // 滑块宽度
        "   height: 30px;"
        "   border-radius: 5px;"      // 滑块圆角
        "}"
        "QSlider::groove:horizontal {"
        "   background: lightgray;"    // 轨道的背景颜色，表示未滑过的部分
        "   border-radius: 5px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "   background: green;"        // 滑条已滑过部分的颜色
        "   border-radius: 5px;"
        "}"
        "QSlider::add-page:horizontal {"
        "   background: lightgray;"    // 滑条未滑过部分的颜色
        "   border-radius: 5px;"
        "}"
    );


         // 连接信号与槽函数
        QObject::connect(slider, &QSlider::valueChanged, [this](int value) {
        label->setText(QString::number(value+500)); // 更新 QLabel 的文本
        mozaData.ch = value;
        slider->setStyleSheet(
            QString(
            "QSlider {"
            "   background: lightgray;"    // 背景颜色，表示未滑过的部分 "   border-radius: 10px;"
             "border-radius: 10px;"
            "}"
            "QSlider::handle {"
            "   background: white;"         // 滑块颜色
            "   width: 40px;"              // 滑块宽度
            "height: 30px;"
            "   border-radius: 5px;"      // 滑块圆角
            "}"
            "QSlider::groove:horizontal {"
            "background: lightgray;"    // 轨道的背景颜色，表示未滑过的部分
                "border-radius: 5px;"
            "}"
            "QSlider::sub-page:horizontal {"
            "   background: green;"        // 滑条已滑过部分的颜色
            "   width: %1px;"              // 使用当前值设置已滑过部分的宽度
            "   border-radius: 5px;"
            "}"
            "QSlider::add-page:horizontal {"
            "   background: lightgray;"    // 滑条未滑过部分的颜色
            "   border-radius: 5px;"
            "}"
           ) .arg(value * 2)); // 根据滑条的值设置宽度（乘以 2 以适应滑条的宽度）
        });

    hlayout5->addWidget(slider);
    hlayout5->addWidget(label);
  

    QVBoxLayout* vlayout4 = new QVBoxLayout();
   
    vlayout4->addLayout(hlayout1);
    vlayout4->addLayout(hlayout5);
   
    setLayout(vlayout4);

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

