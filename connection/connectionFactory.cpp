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
        interfacesAbstract * p_interface = nullptr;
        p_interface = new InterfaceSerial(name, param);
        if(p_interface != nullptr) {
            res  = p_interface->openInterface();
            if(res) {
                 connect(p_interface, SIGNAL(errorInterface(QString,QString)), this, SLOT(errorFromConnection(QString,QString)));
                interfaceList.push_back(std::move(p_interface));
                emit updateTree(getCountConnection() != 0 ? getCountConnection()-1 : 0, ConnectionFactory::Type_Update_Add);
            } else {
                qDebug() << "ConnectionFactory: addConnection -ERR " + name;
                delete p_interface;
            }
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
        interfacesAbstract* p_interface = nullptr;
        p_interface = new InterfaceSerial("", QPair<QStringList,QStringList>());
        if(p_interface != nullptr) {
            interfaceList = p_interface->getAvailableList();
            delete p_interface;
        }
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
    emit updateTree(getCountConnection() != 0 ? getCountConnection()-1 : 0, ConnectionFactory::Type_Update_Removed);
}

void ConnectionFactory::removeConnection(int index) {
    lockInterface->lock();
    if(!interfaceList.isEmpty()) {
        if(index <= interfaceList.size()-1) {
            interfaceList[index]->closeInterface();
            interfaceList.erase(interfaceList.begin() + index);
            emit updateTree(getCountConnection() != 0 ? getCountConnection()-1 : 0, ConnectionFactory::Type_Update_Removed);
        }
    }
    lockInterface->unlock();
}

void ConnectionFactory::removeAll() {
    lockInterface->lock();
    if(!interfaceList.isEmpty()) {
        for(int i=0; i<interfaceList.size(); i++) {
            interfaceList[i]->closeInterface();
        }
        interfaceList.clear();
        emit updateTree(0, ConnectionFactory::Type_Update_Removed);
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
    interfacesAbstract* p_interface = nullptr;
    for(auto it = interfaceList.begin(); it!=interfaceList.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            p_interface = (*it);
            break;
        }
    }
    return p_interface;
}

interfacesAbstract* ConnectionFactory::getInterace(int index) {
    interfacesAbstract *p_interface = nullptr;
    QString name = getInteraceNameFromIndex(index);
    if(!name.isEmpty()) {
        for(auto it = interfaceList.begin(); it!=interfaceList.end(); it++) {
            if((*it)->getInterfaceName() == name) {
                p_interface = (*it);
                break;
            }
        }
    }
    return p_interface;
}

//-----------------------------------------------------/
//---------------         SLOTS             -----------/
//-----------------------------------------------------/
void ConnectionFactory::errorFromConnection(QString conTypeName, QString errMessage) {
    qDebug() << "errorFromConnection -"  << conTypeName << " " << errMessage;
}
