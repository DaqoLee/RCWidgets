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

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void toggleConnection();
    void sendData();
    void readData();
    void refreshPorts();
    void setConnectButtonStyle(bool connected);

private:
    QComboBox* portSelector;
    QPushButton* connectButton;
    QPushButton* sendButton;
    QTextEdit* sendTextEdit;
    QTextEdit* receiveTextEdit;
    QSerialPort serialPort;
};


//#include "main.moc"

#endif // SERIALPORT_H
