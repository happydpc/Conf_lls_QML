#include "./interfaces/interfaceEthernet.h"

InterfaceEthernet::InterfaceEthernet() {
//    this->portHandler = new QSerialPort();
}

InterfaceEthernet::InterfaceEthernet(const InterfaceEthernet & interface) {
//    this->portHandler = interface.portHandler;
}

InterfaceEthernet::~InterfaceEthernet() {

}

void InterfaceEthernet::initInterface() {

}

bool InterfaceEthernet::openInterface(QString name, QStringList arg)  {
    return false;
}

bool InterfaceEthernet::isOpen() {
return false;
}

void InterfaceEthernet::closeInterface()  {

}

bool InterfaceEthernet::sendData(QByteArray &pData)  {
    return false;
}

bool InterfaceEthernet::readData(QByteArray &pData)  {
    return false;
}

QString InterfaceEthernet::getInterfaceName()  {

}

QStringList InterfaceEthernet::getInterfaceProperty() {

}

QStringList InterfaceEthernet::getAvailableList() {

}

void InterfaceEthernet::aboutClose() {
    emit closeIsNormal();
}
