#include "connection/connectionFactory.h"
#include "interfaces/ioSerial.h"
#include <QDebug>

ConnectionFactory::ConnectionFactory() {
    this->lockInterface = std::make_shared<QMutex>(QMutex::NonRecursive);
}
ConnectionFactory::~ConnectionFactory() {}

IoAbstract* ConnectionFactory::createConnection(std::pair<std::vector<std::string>,std::vector<std::string>> param) {
    std::string ioTypeName;
    std::string ioName;
    uint8_t itemCount = 0;
    lockInterface->lock();
    try {
        for(auto keyItem : param.first) {
            if(keyItem == "ioTypeName") {
                ioTypeName = param.second[itemCount];
            }
            if(keyItem == "ioName") {
                ioName = param.second[itemCount];
            }
            itemCount++;
        }
        if(ioTypeName == "serial") {
            std::shared_ptr<IoAbstract> p_interface = std::make_shared<IoSerial>(ioName, param);
            if(p_interface.get() != nullptr) {
                p_interface->openInterface();
                lockInterface->unlock();
                return p_interface.get();
            }
        }
    } catch(...) {
        lockInterface->unlock();
        qDebug() << "ConnectionFactory: addConnection -ERR " << ioName.c_str();
    }
    return nullptr;
}

std::vector<std::string> ConnectionFactory::getAvailableName(std::string typeName) const {
    std::vector<std::string> res;
    if(typeName == "serial") {
        IoAbstract* p_interface = nullptr;
        p_interface = new IoSerial("", std::pair<std::vector<std::string>,std::vector<std::string>>());
        if(p_interface != nullptr) {
            res = p_interface->getAvailableList();
            delete p_interface;
        }
    }
    return res;
}
