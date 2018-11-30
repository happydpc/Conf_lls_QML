#include "connection/connectionFactory.h"
#include "interfaces/interfaceSerial.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->lockInterface = std::make_shared<QMutex>(QMutex::NonRecursive);
}
ConnectionFactory::~ConnectionFactory() {}

bool ConnectionFactory::addConnection(QString typeName, QString name, QPair<QStringList,QStringList> param) {
    bool res = false;
    lockInterface->lock();
    try {
        std::shared_ptr<Connection> p_connection = std::make_shared<Connection>(typeName, name, param);
        connect(p_connection.get(), &Connection::errorConnection, this, &ConnectionFactory::errorFromConnection);
        connectionList.push_back(std::move(p_connection));
        emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Add);
        lockInterface->unlock();
        res = true;
    } catch(...) {
        lockInterface->unlock();
        qDebug() << "ConnectionFactory: addConnection -ERR " + name;
    }
    return res;
}

QStringList ConnectionFactory::getAvailableName(QString typeName) const {
    QStringList interfaceList;
    if(typeName == "serial") {
        ioAbstract* p_interface = nullptr;
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
    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
        if((*it)->getInterfaceAbstract()->getInterfaceName() == name) {
            connectionList.erase(it);
        }
    }
    lockInterface->unlock();
    emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Removed);
}

void ConnectionFactory::removeConnection(int index) {
    lockInterface->lock();
    if(!connectionList.isEmpty()) {
        if(index <= connectionList.size()-1) {
            connectionList[index]->closeAndClear();
            connectionList.erase(connectionList.begin() + index);
            emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Removed);
        }
    }
    lockInterface->unlock();
}

void ConnectionFactory::removeAll() {
    lockInterface->lock();
    if(!connectionList.isEmpty()) {
        for(int i=0; i<connectionList.size(); i++) {
            connectionList[i].get()->closeAndClear();
        }
        connectionList.clear();
        emit updateTree(0, ConnectionFactory::Type_Update_Removed);
    }
    lockInterface->unlock();
}

int ConnectionFactory::getCountConnection() const {
    int res = 0;
    if(lockInterface->tryLock(100)) {
        res = connectionList.size();
        lockInterface->unlock();
    }
    return res;
}

QString ConnectionFactory::getIoName(int ioIndex) const {
    if(!connectionList.empty()) {
        if(ioIndex <= connectionList.size()-1) {
            auto p_ret = connectionList.begin();
            std::advance(p_ret, ioIndex);
            return p_ret->get()->getInterfaceAbstract()->getInterfaceName();
        }
    }
    return QString("undefined");
}

bool ConnectionFactory::getIoNameIsExist(QString ioName) const{
    for(auto it = connectionList.begin(); it != connectionList.end(); it++) {
        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
            return true;
        }
    }
    return false;
}

ioAbstract* ConnectionFactory::getIoAbstract(QString ioName) {
    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
            return it->get()->getInterfaceAbstract();
        }
    }
    return nullptr;
}

ioAbstract* ConnectionFactory::getIoAbstract(const int ioIndex) {
    if(ioIndex <= connectionList.size()-1) {
        auto p_ret = connectionList.begin();
        std::advance(p_ret, ioIndex);
        return p_ret->get()->getInterfaceAbstract();
    }
    return nullptr;
}

DeviceController* ConnectionFactory::getDeviceController(const QString ioName) {
    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
            return it->get()->getDeviceController();
        }
    }
    return nullptr;
}

DeviceController* ConnectionFactory::getDeviceController(int ioIndex) {
    auto ret_it = connectionList.begin();
    std::advance(ret_it, ioIndex);
    return  ret_it->get()->getDeviceController();
}

//-----------------------------------------------------/
//---------------         SLOTS             -----------/
//-----------------------------------------------------/
void ConnectionFactory::errorFromConnection(QString conTypeName, QString errMessage) {
    qDebug() << "errorFromConnection -"  << conTypeName << " " << errMessage;
}
