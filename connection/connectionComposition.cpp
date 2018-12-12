#include "connectionComposition.h"
#include "interfaces/ioSerial.h"
#include <thread>

ConnectionComposition::ConnectionComposition() {

}

bool ConnectionComposition::addIo(IoAbstract * io) {
    ioList.push_back(io);
}

void ConnectionComposition::removeIo(int ioIndex) {

}

void ConnectionComposition::removeIoAll() {

}

std::pair<std::vector<std::string>, std::vector<std::string>> ConnectionComposition::getIoProperty(int ioIndex) const {

}

bool ConnectionComposition::addDev(int ioIndex, DeviceAbstract * dev) {

}

void ConnectionComposition::removeDev(int ioIndex, int devIndex) {

}

std::string ConnectionComposition::getIoStatus(int ioIndex) const {
    std::string res = "closed";
    if(!ioList.empty()) {
        if(ioIndex < ioList.size()) {
            res = (ioList.at(ioIndex)->isOpen()) ? "open" : "closed";
        }
    }
    return res;
}

std::string ConnectionComposition::getDevStatus(int ioIndex, int devIndex) const {
    std::string res = "disconnected";
    if(!ioList.empty()) {
        if(ioIndex < ioList.size()) {
            res = (ioList.at(ioIndex)->g isOpen()) ? "connected" : "disconnected";
        }
    }
    return res;
}

uint16_t ConnectionComposition::getIoCount() const {

}

uint16_t ConnectionComposition::getDevCount(int ioIndex) const {

}

std::pair<std::vector<std::string>, std::vector<std::string>> ConnectionComposition::getDevProperty(int ioIndex, int devIndex) const {

}

bool ConnectionComposition::devExecFutureCommand(int ioIndex, int devIndex, const std::string &commandType,
                                                 const std::vector<std::string> &keys, const std::vector<std::string> &params) {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    emit devExecReadyCommand(commandType);
}
