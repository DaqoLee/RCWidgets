#ifndef SERIALPORT_H
#define SERIALPORT_H

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

class SerialPort : public QWidget {
    Q_OBJECT

public:

    SerialPort(QWidget* parent = nullptr);
    ~SerialPort();
    void sendData(char* data, int len);
    bool isOpen();

    QTextEdit* receiveTextEdit;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void toggleConnection();
   
    void readData();
    void refreshPorts();
    void setConnectButtonStyle(bool connected);

private:
    QComboBox* portSelector;
    QPushButton* connectButton;
    QPushButton* sendButton;
    QTextEdit* sendTextEdit;
   
    QSerialPort serialPort;
};


//#include "main.moc"

#endif // SERIALPORT_H

