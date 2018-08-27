#include "./connection/connectionFactory.h"

ConnectionFactory::ConnectionFactory(QObject *parent) : QObject(parent)
{

}

ConnectionFactory::~ConnectionFactory(){

}

QStringList ConnectionFactory::getAvailableInterfaces() {
    QStringList availIntfaces;
    availIntfaces << "SerialPort" << "Bluetooth";
    return availIntfaces;
}

QStringList ConnectionFactory::getAvailableSubIterfaces(interfacesAbstract::eInterfaceTypes type) {
    QStringList inList;
    interfacesAbstract::eInterfaceTypes tIndex = (interfacesAbstract::eInterfaceTypes)type;
    if(indexType == interfacesAbstract::InterfaceTypeSerialPort) {
        strList = connectionController->getAvailableInterfacesToSerialPort();
    }
    if(indexType == interfacesAbstract::InterfaceTypeBle) {}
    if(indexType == interfacesAbstract::InterfaceTypeEthrnet) {}
    return strList;
}

//bool ConnectionFactory::addConnection(QString interface, QString name, QStringList param) {

//}

//bool ConnectionFactory::removeConnection(QString interface, QString name, QString name) {








//QStringList ConnectionFactory::getAvailableInterfaceItemsFromType(int intexType) {

//}

////void Connection::addConnection(QString nameInterface, QString subName, QString param) {
////    if(nameInterface.contains("SerialPort")) {
////        if(connectionController->addConnectionToSerialPort(subName, param.toInt())) {
////            emit connectionOpened(nameInterface, subName);
////        }
////    }
////}



//void Connection::currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes interfaceType, QString name, int index) {
//    int activeDevice = 0;

//    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
//        emit activeCurrentInterface(name, index, activeDevice);
//    }
//}



//bool ConnectionFactory::addConnection(interfacesAbstract::eInterfaceTypes type, QString name, int *arg) {
//    bool res = false;
//    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
//        InterfaceSerial tSerial;
//        res = tSerial.openInterface(name, arg);
//        if(res) {
//            interfacesSerial.insert(name, std::move(tSerial));
//        }
//    }
//    return res;
//}

//bool ConnectionFactory::removeConnection(interfacesAbstract::eInterfaceTypes, QString name) {
//    return true;
//}

//QStringList ConnectionFactory::getAvailableInterfacesFromType(interfacesAbstract::eInterfaceTypes type) {
//    QStringList connectionList;
//    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
//        InterfaceSerial tSerial;
//        connectionList = tSerial.getAvailableInterfaceList();
//    } else if(type == interfacesAbstract::InterfaceTypeEthrnet) {
//        //        connectionList = interfaceEthernet->getAvailableInterfaceList();
//    } else if(type == interfacesAbstract::InterfaceTypeBle) {
//        //        connectionList = interfaceBLE->getAvailableInterfaceList();
//    } else {
//        throw QString("getAvailableInterfacesFromType: Unsuported type");
//    }
//    return connectionList;
//}
