#include "connection/connectionFactory.h"
#include "interfaces/ioSerial.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->lockInterface = std::make_shared<QMutex>(QMutex::NonRecursive);
}
ConnectionFactory::~ConnectionFactory() {}

IoAbstract* ConnectionFactory::createConnection(const std::string ioTypeName, const std::string ioName, std::pair<std::list<std::string>,std::list<std::string>> param) {
//    bool res = false;
//    lockInterface->lock();
//    try {
//        std::shared_ptr<Connection> p_connection = std::make_shared<Connection>(typeName, name, param);
//        connect(p_connection.get(), &Connection::errorConnection, this, &ConnectionFactory::errorFromConnection);
//        connectionList.push_back(std::move(p_connection));
//        emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Add);
//        lockInterface->unlock();
//        res = true;
//    } catch(...) {
//        lockInterface->unlock();
//        qDebug() << "ConnectionFactory: addConnection -ERR " + name;
//    }
//    return res;
}

//bool res = false;
//if(typeName.toLower() == std::string("serial")) {
//    std::shared_ptr<IoAbstract> p_interface = std::make_shared<IoSerial>(name, param);
//    if(p_interface.get() != nullptr) {
//        res  = p_interface->openInterface();
//        this->connAbstract = std::move(p_interface);
//        this->deviceController = std::make_shared<DeviceController>(connAbstract.get());
//        if(res) {
//            connect(p_interface.get(), &IoAbstract::errorInterface, this, [&](std::string ioTypeName, std::string message) {
//                emit errorConnection(ioTypeName, message);
//            });
//        }
//    }
//}
//if(!res) {
//    qDebug() << "addConnection -ERR " + name;
//    throw std::string("error create connection");
//}

std::list<std::string> ConnectionFactory::getAvailableName(std::string typeName) const {
    std::list<std::string> interfaceList;
    if(typeName == "serial") {
        IoAbstract* p_interface = nullptr;
        p_interface = new IoSerial("", std::pair<std::list<std::string>,std::list<std::string>>());
        if(p_interface != nullptr) {
            interfaceList = p_interface->getAvailableList();
            delete p_interface;
        }
    }
    return interfaceList;
}

//void ConnectionFactory::removeConnection(std::string name) {
//    lockInterface->lock();
////    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
////        if((*it)->getInterfaceAbstract()->getInterfaceName() == name) {
////            connectionList.erase(it);
////        }
////    }
//    lockInterface->unlock();
////    emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Removed);
//}

//void ConnectionFactory::removeConnection(int index) {
//    lockInterface->lock();
////    if(!connectionList.isEmpty()) {
////        if(index <= connectionList.size()-1) {
////            connectionList[index]->closeAndClear();
////            connectionList.erase(connectionList.begin() + index);
////            emit updateTree(connectionList.size() != 0 ? connectionList.size()-1 : 0, ConnectionFactory::Type_Update_Removed);
////        }
////    }
//    lockInterface->unlock();
//}

//void ConnectionFactory::removeAll() {
//    lockInterface->lock();
////    if(!connectionList.isEmpty()) {
////        for(int i=0; i<connectionList.size(); i++) {
////            connectionList[i].get()->closeAndClear();
////        }
////        connectionList.clear();
////        emit updateTree(0, ConnectionFactory::Type_Update_Removed);
////    }
//    lockInterface->unlock();
//}

//int ConnectionFactory::getCountConnection() const {
//    int res = 0;
////    if(lockInterface->tryLock(100)) {
////        res = connectionList.size();
////        lockInterface->unlock();
////    }
//    return res;
//}

//std::string ConnectionFactory::getIoName(int ioIndex) const {
////    if(!connectionList.empty()) {
////        if(ioIndex <= connectionList.size()-1) {
////            auto p_ret = connectionList.begin();
////            std::advance(p_ret, ioIndex);
////            return p_ret->get()->getInterfaceAbstract()->getInterfaceName();
////        }
////    }
//    return std::string("undefined");
//}

//bool ConnectionFactory::getIoNameIsExist(std::string ioName) const{
////    for(auto it = connectionList.begin(); it != connectionList.end(); it++) {
////        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
////            return true;
////        }
////    }
//    return false;
//}

//IoAbstract* ConnectionFactory::getIoAbstract(std::string ioName) {
////    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
////        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
////            return it->get()->getInterfaceAbstract();
////        }
////    }
//    return nullptr;
//}

//IoAbstract* ConnectionFactory::getIoAbstract(const int ioIndex) {
////    if(ioIndex <= connectionList.size()-1) {
////        auto p_ret = connectionList.begin();
////        std::advance(p_ret, ioIndex);
////        return p_ret->get()->getInterfaceAbstract();
////    }
//    return nullptr;
//}

//DeviceController* ConnectionFactory::getDeviceController(const std::string ioName) {
////    for(auto it = connectionList.begin(); it!=connectionList.end(); it++) {
////        if(it->get()->getInterfaceAbstract()->getInterfaceName() == ioName) {
////            return it->get()->getDeviceController();
////        }
////    }
//    return nullptr;
//}

//DeviceController* ConnectionFactory::getDeviceController(int ioIndex) {
////    auto ret_it = connectionList.begin();
////    std::advance(ret_it, ioIndex);
////    return  ret_it->get()->getDeviceController();
//}

//-----------------------------------------------------/
//---------------         SLOTS             -----------/
//-----------------------------------------------------/
//void ConnectionFactory::errorFromConnection(std::string conTypeName, std::string errMessage) {
//    qDebug() << "errorFromConnection -"  << conTypeName << " " << errMessage;
//}
