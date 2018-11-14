#include "connection.h"
#include "interfaces/interfaceSerial.h"
#include <QDebug>

Connection::Connection(const QString typeName, const QString name, const QPair<QStringList,QStringList> param) {
    bool res = false;
    if(typeName.toLower() == QString("serial")) {
        std::shared_ptr<interfacesAbstract> p_interface = std::make_shared<InterfaceSerial>(name, param);
        if(p_interface.get() != nullptr) {
            res  = p_interface->openInterface();
            this->connAbstract = std::move(p_interface);
            this->deviceController = std::make_shared<DeviceController>(connAbstract.get());
            if(res) {
                connect(p_interface.get(), &interfacesAbstract::errorInterface, this, [&](QString ioTypeName, QString message) {
                    emit errorConnection(ioTypeName, message);
                });
            }
        }
    }
    if(!res) {
        qDebug() << "addConnection -ERR " + name;
        throw QString("error create connection");
    }
}

interfacesAbstract* Connection::getInterfaceAbstract(){
    return connAbstract.get();
}

void Connection::closeAndClear() {
    connAbstract.get()->closeInterface();
}

DeviceController* Connection::getDeviceController() {
    return deviceController.get();
}
