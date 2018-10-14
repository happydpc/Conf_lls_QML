#include "./connection/connectionFactory.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->interfaceList.clear();
    this->lockInterface = new QMutex();
}
ConnectionFactory::~ConnectionFactory() {}

bool ConnectionFactory::addConnection(QString typeName, QString name, QPair<QStringList,QStringList> param) {
    bool res = false;
    lockInterface->lock();
    if(typeName.toLower() == QString("serial")) {
        interfacesAbstract* pInterface = new InterfaceSerial(name, param);
        res  = pInterface->openInterface();
        if(res) {
            // TODO: !!! // connect(pInterface, SIGNAL(errorConnection(interfacesAbstract::eInterfaceTypes, QString)), this, SLOT(errorFromConnection(QString, QString)));
            interfaceList.push_back(std::move(pInterface));
            emit updateTree(ConnectionFactory::Type_Update_Add);
        } else {
            delete pInterface;
            qDebug() << "ConnectionFactory: addConnection -ERR " + name;
        }
    } else if(typeName.toLower() == QString("ethernet")) {

    } else if(typeName.toLower() == QString("ble")) {

    } else {
        qDebug() << "Error type create connection";
    }
    if(!res) qDebug() << "Error type create connection";
    lockInterface->unlock();
    return res;
}

QStringList ConnectionFactory::getAvailableName(QString typeName) {
    QStringList interfaceList;
    if(typeName == "serial") {
        interfacesAbstract* pInterface = new InterfaceSerial("", QPair<QStringList,QStringList>());
        interfaceList = pInterface->getAvailableList();
        delete pInterface;
    }
    return interfaceList;
}

void ConnectionFactory::removeConnection(QString name) {
    lockInterface->lock();
    for(auto it = interfaceList.begin(); it != interfaceList.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            interfaceList.erase(it);
        }
    }
    lockInterface->unlock();
    emit updateTree(ConnectionFactory::Type_Update_Removed);
}

void ConnectionFactory::removeConnection(int index) {
    lockInterface->lock();
    if(!interfaceList.isEmpty()) {
        if(index <= interfaceList.size()-1) {
            interfaceList[index]->closeInterface();
            interfaceList.erase(interfaceList.begin() + index);
            emit updateTree(ConnectionFactory::Type_Update_Removed);
        }
    }
    lockInterface->unlock();
}

int ConnectionFactory::getCountConnection() {
    return interfaceList.size();
}

QString ConnectionFactory::getInteraceNameFromIndex(int index) {
    QString res;
    int counter = 0;
    for(auto i=interfaceList.begin(); i!=interfaceList.end(); i++) {
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
    for(auto it = interfaceList.begin(); it!=interfaceList.end(); it++) {
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
        for(auto it = interfaceList.begin(); it!=interfaceList.end(); it++) {
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
