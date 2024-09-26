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

    //// �������Ͱ�ť
    //sendButton1 = new QPushButton("Send");
    //sendButton1->setFixedSize(60, 100);
   // sendButton1->setEnabled(false); // ��ʼΪ����״̬



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
            sendButton[0]->setText("1000"); // ���İ�ť�ı�
            mozaData.N = 1;
        }
        else {
            sendButton[0]->setStyleSheet("background-color: gray; color: white;");
            sendButton[0]->setText("0"); // ���İ�ť�ı�
            mozaData.N = 0;
        }
        isClicked = !isClicked;

        
        });


    QObject::connect(sendButton[0], &QPushButton::clicked, [=]() {

        static bool isClicked = true;
        
        if (isClicked) {
            sendButton[0]->setStyleSheet("background-color: green; color: white;");
            sendButton[0]->setText("1000"); // ���İ�ť�ı�
            mozaData.N = 1;
        }
        else {
            sendButton[0]->setStyleSheet("background-color: gray; color: white;");
            sendButton[0]->setText("0"); // ���İ�ť�ı�
            mozaData.N = 0;
        }
        isClicked = !isClicked;

        
        });

    QObject::connect(sendButton[1], &QPushButton::clicked, [=]() {

        static bool isClicked = true;

        if (isClicked) {
            sendButton[1]->setStyleSheet("background-color: green; color: white;");
            sendButton[1]->setText("1000"); // ���İ�ť�ı�
            mozaData.WIP = 1;
            
        }
        else {
            sendButton[1]->setStyleSheet("background-color: gray; color: white;");
            sendButton[1]->setText("0"); // ���İ�ť�ı�
            mozaData.WIP = 0;
        }
        isClicked = !isClicked;


        });

    QObject::connect(sendButton[2], &QPushButton::clicked, [=]() {

        static bool isClicked = true;

        if (isClicked) {
            sendButton[2]->setStyleSheet("background-color: green; color: white;");
            sendButton[2]->setText("1000"); // ���İ�ť�ı�
            mozaData.L = 1;
        }
        else {
            sendButton[2]->setStyleSheet("background-color: gray; color: white;");
            sendButton[2]->setText("0"); // ���İ�ť�ı�
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

   //  //�������Ϳ�
   // TextEdit3 = new QLabel("0");
   // TextEdit3->setFixedHeight(40);
   // TextEdit3->setFixedWidth(60);
   // TextEdit3->setStyleSheet("background-color: green; color: white;");

   // TextEdit4 = new QLabel("1000");
   // TextEdit4->setFixedHeight(40);
   // TextEdit4->setFixedWidth(60);
   // TextEdit4->setStyleSheet("background-color: lightgray; color: white;");

   //  //�������Ͱ�ť
   // sendButton2 = new QPushButton("Send");
   // sendButton2->setFixedSize(60, 100);
   //// sendButton2->setEnabled(false); // ��ʼΪ����״̬


   // TextEdit5 = new QLabel("0");
   // TextEdit5->setFixedHeight(40);
   // TextEdit5->setFixedWidth(60);
   // TextEdit5->setStyleSheet("background-color: green; color: white;");

   // TextEdit6 = new QLabel("1000");
   // TextEdit6->setFixedHeight(40);
   // TextEdit6->setFixedWidth(60);
   // TextEdit6->setStyleSheet("background-color: lightgray; color: white;");

   // //�������Ͱ�ť
   // sendButton3 = new QPushButton("Send");
   // sendButton3->setFixedSize(60, 100);
   //// sendButton3->setEnabled(false); // ��ʼΪ����״̬



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


        // ���� QLabel ������ʾ������ֵ
    label = new QLabel("0");
    label->setFixedWidth(30);

    slider = new QSlider(Qt::Horizontal); // ����ˮƽ����

    slider->setRange(-500, 500); // ���÷�Χ
    slider->setValue(-500);     // ���ó�ʼֵ


    // �Զ��廬���Ĵ�С����ɫ
    slider->setFixedHeight(40); // ���û����ĸ߶�

    // ʹ����ʽ�����û�������ɫ
    slider->setStyleSheet(
        "QSlider {"
        "   background: lightgray;"    // ������ɫ����ʾδ�����Ĳ���
        "   border-radius: 5px;"
       
        "}"
        "QSlider::handle {"
        "   background: white;"         // ������ɫ
        "   width: 40px;"              // ������
        "   height: 30px;"
        "   border-radius: 5px;"      // ����Բ��
        "}"
        "QSlider::groove:horizontal {"
        "   background: lightgray;"    // ����ı�����ɫ����ʾδ�����Ĳ���
        "   border-radius: 5px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "   background: green;"        // �����ѻ������ֵ���ɫ
        "   border-radius: 5px;"
        "}"
        "QSlider::add-page:horizontal {"
        "   background: lightgray;"    // ����δ�������ֵ���ɫ
        "   border-radius: 5px;"
        "}"
    );


         // �����ź���ۺ���
        QObject::connect(slider, &QSlider::valueChanged, [this](int value) {
        label->setText(QString::number(value+500)); // ���� QLabel ���ı�
        mozaData.ch = value;
        slider->setStyleSheet(
            QString(
            "QSlider {"
            "   background: lightgray;"    // ������ɫ����ʾδ�����Ĳ��� "   border-radius: 10px;"
             "border-radius: 10px;"
            "}"
            "QSlider::handle {"
            "   background: white;"         // ������ɫ
            "   width: 40px;"              // ������
            "height: 30px;"
            "   border-radius: 5px;"      // ����Բ��
            "}"
            "QSlider::groove:horizontal {"
            "background: lightgray;"    // ����ı�����ɫ����ʾδ�����Ĳ���
                "border-radius: 5px;"
            "}"
            "QSlider::sub-page:horizontal {"
            "   background: green;"        // �����ѻ������ֵ���ɫ
            "   width: %1px;"              // ʹ�õ�ǰֵ�����ѻ������ֵĿ��
            "   border-radius: 5px;"
            "}"
            "QSlider::add-page:horizontal {"
            "   background: lightgray;"    // ����δ�������ֵ���ɫ
            "   border-radius: 5px;"
            "}"
           ) .arg(value * 2)); // ���ݻ�����ֵ���ÿ�ȣ����� 2 ����Ӧ�����Ŀ�ȣ�
        });

    hlayout5->addWidget(slider);
    hlayout5->addWidget(label);
  

    QVBoxLayout* vlayout4 = new QVBoxLayout();
   
    vlayout4->addLayout(hlayout1);
    vlayout4->addLayout(hlayout5);
   
    setLayout(vlayout4);

    // ���Ӱ�ť����¼�
   // connect(connectButton, &QPushButton::clicked, this, &ButtonBar::toggleConnection);
    //// ���Ͱ�ť����¼�

    //connect(sendButton, &QPushButton::clicked, this, &ButtonBar::sendData);

    // ��װ�¼��������Բ�����������¼�
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

