#include "viewController.h"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent)
{
    bool res = false;
    QStringList strLis;

    this->connFactory = new ConnectionFactory();

    strLis = connFactory->getAvailableName(interfacesAbstract::InterfaceTypeSerialPort);

    qDebug() << strLis;

    if(strLis.size() > 0) {
        res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, strLis.at(0), QStringList("9600"));
        qDebug() << "IsOpen = "<< res << strLis.at(0);
    } else {
        qDebug() << "DeviceList -Empty";
    }

    if(res) {
        connect(connFactory,
                SIGNAL(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString)),
                SLOT(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString))
                );
    }
}

void ViewController::connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface) {

}

void ViewController::addConnectionEvent() {
    //    emit addConnReplyList(connectionController->getListInterfacesConnection());
}

void ViewController::closeConnectionEvent() {

}

void ViewController::closeAppEvent() {

}


//// первый - это имя интерфейса (SerialPort,Ble,Ethernet)
//QStringList Connection::getAvailableListInterfaceOfType(int indexType) {
//    QStringList strList;
//    interfacesAbstract::eInterfaceTypes tIndex = (interfacesAbstract::eInterfaceTypes)indexType;
//    if(indexType == interfacesAbstract::InterfaceTypeSerialPort) {
//        strList = connectionController->getAvailableInterfacesToSerialPort();
//    }
//    if(indexType == interfacesAbstract::InterfaceTypeBle) {}
//    if(indexType == interfacesAbstract::InterfaceTypeEthrnet) {}
//    return strList;
//}

//void Connection::addConnection(QString nameInterface, QString subName, QString param) {
//    if(nameInterface.contains("SerialPort")) {
//        if(connectionController->addConnectionToSerialPort(subName, param.toInt())) {
//            emit connectionOpened(nameInterface, subName);
//        }
//    }
//}



//void Connection::currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes interfaceType, QString name, int index) {
//    int activeDevice = 0;

//    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
//        emit activeCurrentInterface(name, index, activeDevice);
//    }
//}
