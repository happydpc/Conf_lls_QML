#include "./interfaces/interfaceBLE.h"

InterfaceBLE::InterfaceBLE()
{

}

InterfaceBLE::~InterfaceBLE() {

}

void InterfaceBLE::initInterface()  {

}

bool InterfaceBLE::openInterface() {}

void InterfaceBLE::closeInterface() {
}

bool InterfaceBLE::sendData(QByteArray &pData)  {
    return false;
}

bool InterfaceBLE::readData(QByteArray &pData)  {
    return false;
}

QString InterfaceBLE::getInterfaceName() {}

QStringList InterfaceBLE::getInterfaceProperty() {}

bool InterfaceBLE::isOpen() {}

void InterfaceBLE::aboutClose() {
    emit closeIsNormal();
}

QString InterfaceBLE::getType() {
    return QString::fromLocal8Bit(typeName, strlen(typeName));
}

QStringList InterfaceBLE::getAvailableList() {
    QStringList list;
    return list;
}
