#include "./connection/connectionFactory.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->interface.clear();
    this->lockInterface = new QMutex();
}
ConnectionFactory::~ConnectionFactory() {}

bool ConnectionFactory::addConnection(interfacesAbstract::eInterfaceTypes type, QString name, QStringList param) {
    bool res = false;
    lockInterface->lock();
    Interface *pInterface = new Interface(type, name, param);
    res  = pInterface->openInterface(name, param);
    if(res) {
        connect(pInterface,
                SIGNAL(errorConnection(interfacesAbstract::eInterfaceTypes, QString)), this,
                SLOT(errorFromConnection(interfacesAbstract::eInterfaceTypes, QString)));
        interface.push_back(std::move(pInterface));
        emit updateTree(ConnectionFactory::Type_Update_Add);
    } else {
        delete pInterface;
        qDebug() << "ConnectionFactory: addConnection -ERR " + name;
    }
    lockInterface->unlock();
    return res;
}

QStringList ConnectionFactory::getAvailableName() {
    Interface tInterface(interfacesAbstract::InterfaceTypeSerialPort, "", QStringList("")); // TODO: it work only serialPort
    return tInterface.getAvailableList();
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

Interface* ConnectionFactory::getInterace(QString name) {
    Interface *pInterface = nullptr;
    for(auto it = interface.begin(); it!=interface.end(); it++) {
        if((*it)->getInterfaceName() == name) {
            pInterface = (*it);
            break;
        }
    }
    return pInterface;
}

Interface* ConnectionFactory::getInterace(int index) {
    Interface *pInterface = nullptr;
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
void ConnectionFactory::errorFromConnection(interfacesAbstract::eInterfaceTypes, QString name) {
    qDebug() << "errorFromConnection -" << name;
}
