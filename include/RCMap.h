#ifndef RCMAP_H
#define RCMAP_H

#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtMath>
#include <Qpushbutton.h>
#include <QUdpSocket>
#include <QWidget>
#include <QHostAddress>
#include <QString>
#include <QStringList>
#include<QSerialPort>
#include<QSerialPortInfo>

#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>


#include <QMessageBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QTextEdit>

#include<QPainterPath.h>

class RCMap : public QWidget {
    Q_OBJECT

public:
    RCMap(QWidget* parent = nullptr);
    ~RCMap();

protected:
   // bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    //void toggleConnection();
    //void sendData();
    //void readData();
    //void refreshPorts();
    //void setConnectButtonStyle(bool connected);

private:

    QPixmap background;

    typedef struct
    {
        QPixmap movingImage;
        QColor borderColor;
        int imageX;
        int imageY;
    }Tag_t;


    Tag_t Tag[5];

    int radius;

    void paintEvent(QPaintEvent* event) override;
};




//#include "main.moc"

#endif // SERIALPORT_H

