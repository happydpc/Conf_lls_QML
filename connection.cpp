#include "connection.h"
#include "interfacesAbstract.h"

Connection::Connection() {
    this->connectionFactory = new ConnectionFactory();
}

void Connection::addConnectionRequest() {
    int availableCountTypesInterface = 0;
    availableCountTypesInterface += connectionFactory->bleIsAvailable();
    availableCountTypesInterface += connectionFactory->ethernetIsAvailable();
    availableCountTypesInterface += connectionFactory->serialPortIsAvailable();

    // отсылаем сколько типов интрефейсов можно юзать
    emit readyCreateNewConnections(availableCountTypesInterface);
}

// первый - это имя интерфейса (SerialPort,Ble,Ethernet)
QStringList Connection::getAvailableListInterfaceOfType(int indexType) {
    QStringList strList;
    interfacesAbstract::eInterfaceTypes tIndex = (interfacesAbstract::eInterfaceTypes)indexType;
    if(indexType == interfacesAbstract::InterfaceTypeSerialPort) {
        strList = connectionFactory->getAvailableInterfacesToSerialPort();
    }
    if(indexType == interfacesAbstract::InterfaceTypeBle) {}
    if(indexType == interfacesAbstract::InterfaceTypeEthrnet) {}
    return strList;
}

void Connection::addConnection(QString nameInterface, QString subName, QString param) {
    if(nameInterface.contains("SerialPort")) {
        if(connectionFactory->addConnectionToSerialPort(subName, param.toInt())) {
            emit connectionOpened(nameInterface, subName);
        }
    }
}
