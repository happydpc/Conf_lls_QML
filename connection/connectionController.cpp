#include "connectionController.h"

ConnectionController::ConnectionController()
{
    this->connectionFactory = new ConnectionFactory();

    this->devController = new DeviceController();
}


QStringList ConnectionController::getListInterfacesConnection() {
    connectionController->getListInterfacesConnection();
}

//ConnectionController::addConnection() {

//}

//-----------------------------------------------------/
//---------------         QML block         -----------/
//-----------------------------------------------------/
bool ConnectionController::addConnectionToSerialPort(QString portName, int baudrate) {
    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, portName, &baudrate);
}
bool ConnectionController::addConnectionToBLE(QString portName) {
    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeBle, portName, nullptr);
}
bool ConnectionController::addConnectionToEthernet(QString portName) {
    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeEthrnet, portName, nullptr);
}

bool ConnectionController::removeConnectionToSerialPort(QString portName) {
    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeSerialPort, portName);
}
bool ConnectionController::removeConnectionToBLE(QString portName) {
    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeBle, portName);
}
bool ConnectionController::removeConnectionToEthernet(QString portName) {
    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeEthrnet, portName);
}

QStringList ConnectionController::getAvailableInterfacesToSerialPort() {
    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeSerialPort);
}
QStringList ConnectionController::getAvailableInterfacesToBLE() {
    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeBle);
}
QStringList ConnectionController::getAvailableInterfacesToEthernet() {
    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeEthrnet);
}
