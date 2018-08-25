#include "connectionFactory.h"

ConnectionFactory::ConnectionFactory(QObject *parent) : QObject(parent)
{
    this->interfaceSerial = new InterfaceSerial();
    this->interfaceEthernet = new InterfaceEthernet();
    this->interfaceBLE = new InterfaceBLE();

    connect(this->interfaceSerial,
            SIGNAL(portMessage(InterfaceSerial::eInterfaceMessageType, QString)),
            SLOT(interfaceMessageSlot(InterfaceSerial::eInterfaceMessageType, QString)));
}

ConnectionFactory::~ConnectionFactory(){

}

bool ConnectionFactory::serialPortIsAvailable() {
    return !interfaceSerial->getAvailableInterfaceList().empty();
}

bool ConnectionFactory::bleIsAvailable() {
    return false;
}

bool ConnectionFactory::ethernetIsAvailable() {
    return false;
}




//-----------------------------------------------------/
//---------------         QML block         -----------/
//-----------------------------------------------------/
bool ConnectionFactory::addConnectionToSerialPort(QString portName, int baudrate) {
    return addConnection(interfacesAbstract::InterfaceTypeSerialPort, portName, &baudrate);
}
bool ConnectionFactory::addConnectionToBLE(QString portName) {
    return addConnection(interfacesAbstract::InterfaceTypeBle, portName, nullptr);
}
bool ConnectionFactory::addConnectionToEthernet(QString portName) {
    return addConnection(interfacesAbstract::InterfaceTypeEthrnet, portName, nullptr);
}

bool ConnectionFactory::removeConnectionToSerialPort(QString portName) {
    return removeConnection(interfacesAbstract::InterfaceTypeSerialPort, portName);
}
bool ConnectionFactory::removeConnectionToBLE(QString portName) {
    return removeConnection(interfacesAbstract::InterfaceTypeBle, portName);
}
bool ConnectionFactory::removeConnectionToEthernet(QString portName) {
    return removeConnection(interfacesAbstract::InterfaceTypeEthrnet, portName);
}

QStringList ConnectionFactory::getAvailableInterfacesToSerialPort() {
    return getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeSerialPort);
}
QStringList ConnectionFactory::getAvailableInterfacesToBLE() {
    return getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeBle);
}
QStringList ConnectionFactory::getAvailableInterfacesToEthernet() {
    return getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeEthrnet);
}
//-----------------------------------------------------/
//---------------       private block        ----------/
//-----------------------------------------------------/
bool ConnectionFactory::addConnection(interfacesAbstract::eInterfaceTypes type, QString name, int *arg) {
    bool res = false;
    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
        res = interfaceSerial->openInterface(name, arg);
    }
    return res;
}

bool ConnectionFactory::removeConnection(interfacesAbstract::eInterfaceTypes, QString name) {
    return true;
}

QStringList ConnectionFactory::getAvailableInterfacesFromType(interfacesAbstract::eInterfaceTypes type) {
    QStringList connectionList;
    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
        connectionList = interfaceSerial->getAvailableInterfaceList();
    } else if(type == interfacesAbstract::InterfaceTypeEthrnet) {
        //        connectionList = interfaceEthernet->getAvailableInterfaceList();
    } else if(type == interfacesAbstract::InterfaceTypeBle) {
        //        connectionList = interfaceBLE->getAvailableInterfaceList();
    } else {
        throw QString("getAvailableInterfacesFromType: Unsuported type");
    }
    return connectionList;
}
