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

QPair<QStringList,QStringList> InterfaceBLE::getInterfaceProperty() {}

bool InterfaceBLE::isOpen() {}

QString InterfaceBLE::getType() {
    return QString::fromLocal8Bit(typeName, strlen(typeName));
}

QStringList InterfaceBLE::getAvailableList() {
    QStringList list;
    return list;
}
