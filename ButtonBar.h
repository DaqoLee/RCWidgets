#pragma once

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>

#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QAbstractItemView>

class ButtonBar : public QWidget {
    Q_OBJECT

public:
    ButtonBar(QWidget* parent = nullptr);
    ~ButtonBar();

protected:
   

private slots:
    void toggleConnection();
    void sendData();
    void readData();
    void refreshPorts();
    void setConnectButtonStyle(bool connected);

private:
    QComboBox* portSelector;


    QPushButton* sendButton[6];

    QPushButton* connectButton;

    QPushButton* sendButton1;
    QLabel* TextEdit1;
    QLabel* TextEdit2;

    QPushButton* sendButton2;
    QLabel* TextEdit3;
    QLabel* TextEdit4;

    QPushButton* sendButton3;
    QLabel* TextEdit5;
    QLabel* TextEdit6;


    QSlider* slider;
    QLabel* label;

    QSerialPort serialPort;
};
