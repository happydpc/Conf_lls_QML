#include "connectionComposition.h"
#include "interfaces/ioSerial.h"
#include <QDebug>

ConnectionComposition::ConnectionComposition() {

}

bool ConnectionComposition::addIo(IoAbstract * io) {

}

void ConnectionComposition::removeIo(int ioIndex) {

}

void ConnectionComposition::removeIoAll() {

}

QPair<QString, QString> ConnectionComposition::getIoProperty(int ioIndex) const {

}

bool ConnectionComposition::addDev(DeviceAbstract & dev) {

}
void ConnectionComposition::removeDev(int ioIndex, int devIndex) {

}

bool ConnectionComposition::getIoIsConnected(int ioIndex) {

}

bool ConnectionComposition::getDevIsConnected(int ioIndex, int devIndex) {

}

uint16_t ConnectionComposition::getIoCount() {

}

uint16_t ConnectionComposition::getDevCount(int ioIndex) {

}

QPair<QString, QString> ConnectionComposition::getDevProperty(int ioIndex, int devIndex) const {

}

bool ConnectionComposition::devSendCustomCommand(int ioIndex, int devIndex, const QString &comandType,
                                                 const QStringList &keys, const QStringList &params) {

}

//bool res = false;
//if(typeName.toLower() == QString("serial")) {
//    std::shared_ptr<IoAbstract> p_interface = std::make_shared<IoSerial>(name, param);
//    if(p_interface.get() != nullptr) {
//        res  = p_interface->openInterface();
//        this->connAbstract = std::move(p_interface);
//        this->deviceController = std::make_shared<DeviceController>(connAbstract.get());
//        if(res) {
//            connect(p_interface.get(), &IoAbstract::errorInterface, this, [&](QString ioTypeName, QString message) {
//                emit errorConnection(ioTypeName, message);
//            });
//        }
//    }
//}
//if(!res) {
//    qDebug() << "addConnection -ERR " + name;
//    throw QString("error create connection");
//}

//IoAbstract* ConnectionComposition::getInterfaceAbstract(){
//    return connAbstract.get();
//}

//void ConnectionComposition::closeAndClear() {
//    connAbstract.get()->closeInterface();
//}

//DeviceController* ConnectionComposition::getDeviceController() {
//    return deviceController.get();
//}
