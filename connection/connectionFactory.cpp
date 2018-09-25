#include "./connection/connectionFactory.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->interface.clear();
    this->lockInterface = new QMutex();
}
ConnectionFactory::~ConnectionFactory() {}

bool ConnectionFactory::addConnection(QString typeConnection, QString name, QStringList param) {
    bool res = false;
    lockInterface->lock();

    if(typeConnection.toUpper() == QString("Serial").toUpper()) {
        interfacesAbstract* pInterface = new InterfaceSerial(name, param);
        res  = pInterface->openInterface(name, param);
        if(res) { // TODO: !!! // connect(pInterface, SIGNAL(errorConnection(interfacesAbstract::eInterfaceTypes, QString)), this, SLOT(errorFromConnection(QString, QString)));
            interface.push_back(std::move(pInterface));
            emit updateTree(ConnectionFactory::Type_Update_Add);
        } else {
            delete pInterface;
            qDebug() << "ConnectionFactory: addConnection -ERR " + name;
        }
    } else if(typeConnection.toUpper() == QString("Ethernet").toUpper()) {

    } else if(typeConnection.toUpper() == QString("BLE").toUpper()) {

    } else {
        qDebug() << "Error type create connection";
    }
    lockInterface->unlock();
    return res;
}

QStringList ConnectionFactory::getAvailableName() {
    QStringList interfaceList;
    interfacesAbstract* pInterface = new InterfaceSerial("", QStringList("")); // TODO: it work only serialPort
    interfaceList = pInterface->getAvailableList();
    delete pInterface;
    return interfaceList;
}

void ConnectionFactory::removeConnection(QString name) {
    lockInterface->lock();
    for(auto it = interface.begin(); it != interface.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            interface.erase(it);
        }
    }
    lockInterface->unlock();
    emit updateTree(ConnectionFactory::Type_Update_Removed);
}

void ConnectionFactory::removeConnection(int index) {
    lockInterface->lock();
    auto it = interface.begin();
    (*it)->closeInterface();
    interface.erase(it+= index);
    lockInterface->unlock();
    emit updateTree(ConnectionFactory::Type_Update_Removed);
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

interfacesAbstract* ConnectionFactory::getInterace(QString name) {
    interfacesAbstract* pInterface = nullptr;
    for(auto it = interface.begin(); it!=interface.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            pInterface = (*it);
            break;
        }
    }
    return pInterface;
}

interfacesAbstract* ConnectionFactory::getInterace(int index) {
    interfacesAbstract *pInterface = nullptr;
    QString name = getInteraceNameFromIndex(index);
    if(!name.isEmpty()) {
        for(auto it = interface.begin(); it!=interface.end(); it++) {
            if((*it)->getInterfaceName() == name) {
                pInterface = (*it);
                break;
            }
        }
    }
    return pInterface;
}

//-----------------------------------------------------/
//---------------         SLOTS             -----------/
//-----------------------------------------------------/
void ConnectionFactory::errorFromConnection(QString type, QString name) {
    qDebug() << "errorFromConnection -"  << type << " " << name;
}
