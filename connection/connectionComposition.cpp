#include "connectionComposition.h"
#include "interfaces/ioSerial.h"
#include <QDebug>

ConnectionComposition::ConnectionComposition() {

}

bool ConnectionComposition::addIo(IoAbstract * io) {
    ioList.push_back(io);
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

bool ConnectionComposition::getIoIsConnected(int ioIndex) const {

}

bool ConnectionComposition::getDevIsConnected(int ioIndex, int devIndex) const {

}

uint16_t ConnectionComposition::getIoCount() const {

}

uint16_t ConnectionComposition::getDevCount(int ioIndex) const {

}

QPair<QString, QString> ConnectionComposition::getDevProperty(int ioIndex, int devIndex) const {

}

bool ConnectionComposition::devSendCustomCommand(int ioIndex, int devIndex, const QString &comandType,
                                                 const QStringList &keys, const QStringList &params) {

}

//IoAbstract* ConnectionComposition::getInterfaceAbstract(){
//    return connAbstract.get();
//}

//void ConnectionComposition::closeAndClear() {
//    connAbstract.get()->closeInterface();
//}

//DeviceController* ConnectionComposition::getDeviceController() {
//    return deviceController.get();
//}
