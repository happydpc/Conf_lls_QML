#include "connectionFactory.h"

ConnectionFactory::ConnectionFactory(QObject *parent) : QObject(parent)
{
    this->interfaceSerial = new InterfaceSerial();
    this->interfaceEthernet = new InterfaceEthernet();
    this->interfaceBLE = new InterfaceBLE();
}

ConnectionFactory::~ConnectionFactory(){

}

//-----------------------------------------------------/
//---------------         QML block         -----------/
//-----------------------------------------------------/
bool ConnectionFactory::addConnectionToSerialPort(QString portName) {
    return addConnection(interfacesAbstract::InterfaceTypeSerialPort, portName);
}
bool ConnectionFactory::addConnectionToBLE(QString portName) {
    return addConnection(interfacesAbstract::InterfaceTypeBle, portName);
}
bool ConnectionFactory::addConnectionToEthernet(QString portName) {
    return addConnection(interfacesAbstract::InterfaceTypeEthrnet, portName);
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
bool ConnectionFactory::addConnection(interfacesAbstract::eInterfaceTypes, QString name) {

}

bool ConnectionFactory::removeConnection(interfacesAbstract::eInterfaceTypes, QString name) {

}

QStringList ConnectionFactory::getAvailableInterfacesFromType(
        interfacesAbstract::eInterfaceTypes type) {
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
