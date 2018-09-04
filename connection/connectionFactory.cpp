#include "./connection/connectionFactory.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory()
{
    this->interface.clear();
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
    Interface *pInterface = new Interface(type, name, param);
    res  = pInterface->openInterface(name, param);
    if(res) {
        connect(pInterface,
                SIGNAL(errorConnection(interfacesAbstract::eInterfaceTypes, QString)), this,
                SLOT(errorFromConnection(interfacesAbstract::eInterfaceTypes, QString)));
        interface.push_back(std::move(pInterface));
    } else {
        delete pInterface;
        qDebug() << "ConnectionFactory: addConnection-ERR " + name;
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
    return interface.size();
}

QString ConnectionFactory::getInteraceNameFromIndex(int index) {
    QString res;
    int counter = 0;
    for(auto i=interface.begin(); i!=interface.end(); i++) {
        if(counter == index) {
            res = (*i)->getInterfaceName();
            break;
        }
        counter++;
    }
    return res;
}

Interface* ConnectionFactory::getInterace(interfacesAbstract::eInterfaceTypes type, QString name) {
    Interface *pInterface = nullptr;
    for(auto it = interface.begin(); it!=interface.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            if((*it)->getInterfaceType() == type) {
                pInterface = (*it);
                break;
            }
        }
    }
    return pInterface;
}

Interface* ConnectionFactory::getInterace(interfacesAbstract::eInterfaceTypes type, int index) {
    Interface *pInterface = nullptr;
    QString name = getInteraceNameFromIndex(index);
    if(!name.isEmpty()) {
        for(auto it = interface.begin(); it!=interface.end(); it++) {
            if((*it)->getInterfaceName() == name) {
                if((*it)->getInterfaceType() == type) {
                    pInterface = (*it);
                    break;
                }
            }
        }
    }
    return pInterface;
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
