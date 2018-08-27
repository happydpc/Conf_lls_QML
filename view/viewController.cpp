#include "viewController.h"

ViewController::ViewController(QObject *parent) : QObject(parent)
{
    this->connectionController = new ConnectionController();
}



void ViewController::addConnectionEvent() {
    connectionController->addConnection();
    emit addConnectionEventReplyReady();
}

void ViewController::closeConnectionEvent() {

}

void ViewController::closeAppEvent() {

}


// первый - это имя интерфейса (SerialPort,Ble,Ethernet)
QStringList Connection::getAvailableListInterfaceOfType(int indexType) {
    QStringList strList;
    interfacesAbstract::eInterfaceTypes tIndex = (interfacesAbstract::eInterfaceTypes)indexType;
    if(indexType == interfacesAbstract::InterfaceTypeSerialPort) {
        strList = connectionController->getAvailableInterfacesToSerialPort();
    }
    if(indexType == interfacesAbstract::InterfaceTypeBle) {}
    if(indexType == interfacesAbstract::InterfaceTypeEthrnet) {}
    return strList;
}

void Connection::addConnection(QString nameInterface, QString subName, QString param) {
    if(nameInterface.contains("SerialPort")) {
        if(connectionController->addConnectionToSerialPort(subName, param.toInt())) {
            emit connectionOpened(nameInterface, subName);
        }
    }
}



void Connection::currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes interfaceType, QString name, int index) {
    int activeDevice = 0;

    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        emit activeCurrentInterface(name, index, activeDevice);
    }
}
