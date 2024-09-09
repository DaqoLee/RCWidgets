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

    QTextEdit* TextEdit1;
    QTextEdit* TextEdit2;

    QPushButton* sendButton2;
    QTextEdit* TextEdit3;
    QTextEdit* TextEdit4;


    QTextEdit* TextEdit5;
    QTextEdit* TextEdit6;


    QSerialPort serialPort;
};
