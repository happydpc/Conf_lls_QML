#include "viewController.h"
#include <QDebug>

//    bool res = false;
//    QStringList strLis;

ViewController::ViewController(QObject *parent) : QObject(parent) {
    this->connFactory = new ConnectionFactory();

//    strLis = connFactory->getAvailableName(interfacesAbstract::InterfaceTypeSerialPort);
//    qDebug() << strLis;
//    int contAvailableList = 0;
//    while(contAvailableList != strLis.size()) {
//        res = connFactory->addConnection(
//                    interfacesAbstract::InterfaceTypeSerialPort, strLis.at(contAvailableList),
//                    QStringList("9600"));
//        qDebug() << "IsOpen = "<< res << strLis.at(contAvailableList);
//        contAvailableList++;
//    }
//    int id_dev = 1;
//    for(int i=0; i<3; i++) {
////        QString nameInterface = QString("ttyACM%1").arg(i);
//        QString nameInterface = QString("ttyACM0");
//        Interface *pInterface = nullptr;
//        pInterface = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, nameInterface);

//        if(pInterface != nullptr) {
//            res = pInterface->getDeviceFactory()->addNewDevice(
//                        DeviceAbstract::Type_Progress_Tmk324,
//                        QString("/%1/lls_tmk3.24_%2").arg(nameInterface).arg(i),
//                        id_dev, QStringList(""));
//            qDebug() << "Interface-" << nameInterface << " -open Ok";
//        } else {
//            qDebug() << "Interface-" << nameInterface << " -no open!";
//        }
//    }
}

QStringList ViewController::getAvailableNameToSerialPort() {
    QStringList retList;
    retList = connFactory->getAvailableName(interfacesAbstract::InterfaceTypeSerialPort);
    return retList;
}

bool ViewController::addConnectionSerialPort(QString name, QString baudrate) {
    bool res = false;
    res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, name, QStringList(baudrate));
    qDebug() << "addConnectionSerialPort -open= "<< res << name;
    return res;
}



void ViewController::connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface) {
    //        connect(connFactory,
    //                SIGNAL(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString)),
    //                SLOT(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString))
    //                );
}
