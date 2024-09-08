#include "RCWidgets.h"
#include <QtWidgets/QApplication>



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    RCWidgets RC;
    RC.resize(1080, 1960);



    //Serial->show();
    RC.show();
    return a.exec();
}

//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//    SerialPort window;
//    window.resize(400, 400); // ´°¿Ú´óÐ¡
//    window.show();
//    return app.exec();
//}
//

//#include <QApplication>
//#include <QWidget>
//#include <QVBoxLayout>
//#include <QLabel>
//#include <QNetworkInterface>
//#include <QHostAddress>
//
//QString getLocalIP() {
//    QString ipAddress;
//
//    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
//
//    for (const QNetworkInterface& interface : interfaces) {
//        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
//            !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
//
//            const QList<QNetworkAddressEntry> entries = interface.addressEntries();
//            for (const QNetworkAddressEntry& entry : entries) {
//                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
//                    ipAddress = entry.ip().toString();
//                    break;
//                }
//            }
//        }
//        if (!ipAddress.isEmpty()) {
//            break;
//        }
//    }
//
//    return ipAddress.isEmpty() ? "No IP Address found" : ipAddress;
//}
//
//int main(int argc, char* argv[]) {
//    QApplication app(argc, argv);
//
//    QWidget window;
//    window.setWindowTitle("Local IP Address");
//
//    QVBoxLayout* layout = new QVBoxLayout(&window);
//    QLabel* ipLabel = new QLabel("Your Local IP Address: " + getLocalIP());
//    layout->addWidget(ipLabel);
//
//    window.setLayout(layout);
//    window.resize(300, 100);
//    window.show();
//
//    return app.exec();
//}
