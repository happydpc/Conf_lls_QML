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

std::pair<std::list<std::string>, std::list<std::string>> ConnectionComposition::getIoProperty(int ioIndex) const {

}

bool ConnectionComposition::addDev(int ioIndex, DeviceAbstract * dev) {

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

std::pair<std::list<std::string>, std::list<std::string>> ConnectionComposition::getDevProperty(int ioIndex, int devIndex) const {

}

bool ConnectionComposition::devExecFutureCommand(int ioIndex, int devIndex, const std::string &comandType,
                                                 const std::list<std::string> &keys, const std::list<std::string> &params) {

}
