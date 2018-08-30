#include "./connection/connectionFactory.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory()
{

}
ConnectionFactory::~ConnectionFactory() {}

bool ConnectionFactory::addConnection(interfacesAbstract::eInterfaceTypes type, QString name, QStringList param) {
    bool res = false;
    QString conCaption;
    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
        conCaption = "SerialPort";
    } else if(type  == interfacesAbstract::InterfaceTypeBle) {
        conCaption = "Ble";
    } else if(type == interfacesAbstract::InterfaceTypeEthrnet) {
        conCaption = "SerialPort";
    } else {
        conCaption = "UNKNOWN";
    }
    Interface tInterface(type, name, param);
    res  = tInterface.openInterface(name, param);
    if(res) {;
        connect(&tInterface,
                SIGNAL(errorConnection(interfacesAbstract::eInterfaceTypes, QString)), this,
                SLOT(errorFromConnection(interfacesAbstract::eInterfaceTypes, QString)));
        interface.insert(conCaption, std::move(tInterface));
    }
    return res;
}

QStringList ConnectionFactory::getAvailableName(interfacesAbstract::eInterfaceTypes type) {
    Interface tInterface(type, "", QStringList(""));
    return tInterface.getAvailableList();
}

void ConnectionFactory::removeConnection(interfacesAbstract::eInterfaceTypes type, QString name) {

}

int ConnectionFactory::getCountConnection() {

}

QString ConnectionFactory::getNameConnection() {

}

QString ConnectionFactory::getTypeConnection() {

}

////-----------------------------------------------------/
////---------------         SLOTS             -----------/
////-----------------------------------------------------/

void ConnectionFactory::errorFromConnection(interfacesAbstract::eInterfaceTypes, QString name) {
        qDebug() << "errorFromConnection -" << name;
}


//QStringList ConnectionFactory::getAvailableInterfaces() {
//    QStringList availIntfaces;
//    availIntfaces << "SerialPort" << "Bluetooth";
//    return availIntfaces;
//}

//QStringList ConnectionFactory::getAvailableSubIterfaces(interfacesAbstract::eInterfaceTypes type) {
//    QStringList strList;
//    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
//        InterfaceSerial tSerial;
//        tSerial.getAvailableList();
//    }
//    return strList;
//}


//-----------------------------------------------------/
//---------------   ConnectionFactory       -----------/
//-----------------------------------------------------/
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

//bool ConnectionController::addConnectionToSerialPort(QString portName, int baudrate) {
//    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, portName, &baudrate);
//}
//bool ConnectionController::addConnectionToBLE(QString portName) {
//    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeBle, portName, nullptr);
//}
//bool ConnectionController::addConnectionToEthernet(QString portName) {
//    return connectionFactory->addConnection(interfacesAbstract::InterfaceTypeEthrnet, portName, nullptr);
//}

//bool ConnectionController::removeConnectionToSerialPort(QString portName) {
//    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeSerialPort, portName);
//}
//bool ConnectionController::removeConnectionToBLE(QString portName) {
//    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeBle, portName);
//}
//bool ConnectionController::removeConnectionToEthernet(QString portName) {
//    return connectionFactory->removeConnection(interfacesAbstract::InterfaceTypeEthrnet, portName);
//}

//QStringList ConnectionController::getAvailableInterfacesToSerialPort() {
//    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeSerialPort);
//}
//QStringList ConnectionController::getAvailableInterfacesToBLE() {
//    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeBle);
//}
//QStringList ConnectionController::getAvailableInterfacesToEthernet() {
//    return connectionFactory->getAvailableInterfacesFromType(interfacesAbstract::InterfaceTypeEthrnet);
//}
