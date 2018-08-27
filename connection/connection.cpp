#include "./connection/connection.h"
#include "./interfaces/interfacesAbstract.h"

Connection::Connection() {
    this->connectionController = new ConnectionController();
}

// TODO: для расширения - когда будет несколько видов интерфейсов
void Connection::addConnectionRequest() {
    int availableCountTypesInterface = 0;
//    availableCountTypesInterface += connectionFactory->bleIsAvailable();
//    availableCountTypesInterface += connectionFactory->ethernetIsAvailable();
//    availableCountTypesInterface += connectionFactory->serialPortIsAvailable();
    availableCountTypesInterface += 1;
    // отсылаем сколько типов интрефейсов можно юзать
    emit readyCreateNewConnections(availableCountTypesInterface);
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
