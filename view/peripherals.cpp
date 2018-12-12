#include "peripherals.h"
#include <thread>
#include <stdio.h>
#include <iostream>
#include <QTimer>

Peripherals::Peripherals(QObject *parent) : QObject(parent) {
    this->connFactory = std::make_shared<ConnectionFactory>();
    this->connComposition = std::make_shared<ConnectionComposition>();
    std::shared_ptr<QTimer>updateTimer = std::shared_ptr<QTimer>();

    updateTimer = std::make_shared<QTimer>();
    updateTimer->start(100);
    connect(updateTimer.get(), &QTimer::timeout, [&]() {

    });
}

std::vector<std::string> Peripherals::getAvailableIo(const std::string typeIoName) const {
    return connFactory->getAvailableName(typeIoName);
}

bool Peripherals::addIo(const std::vector<std::string> keyParam,
                        const std::vector<std::string> valueParam) {
    return connComposition->addIo(connFactory->createConnection(std::pair<std::vector<std::string>,std::vector<std::string>>(keyParam, valueParam)));
}

void Peripherals::removeIo(int ioIndex) {
    connComposition->removeIo(ioIndex);
}

std::pair<std::vector<std::string>, std::vector<std::string>> Peripherals::getIoProperty(int ioIndex) const {
    return connComposition->getIoProperty(ioIndex);
}

std::string Peripherals::getIoStatus(int ioIndex) const {
    return connComposition->getIoStatus(ioIndex);
}

int Peripherals::getIoCount(const int ioIndex) const {
    return connComposition->getIoCount();
}

bool Peripherals::addDev(int ioIndex, const std::vector<std::string> keyParam, const std::vector<std::string> valueParam) {
    bool res = false;
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    try {
        auto dev = devFactory->newDevice(keyParam, valueParam);
        if(dev != nullptr) {
            res = connComposition->addDev(ioIndex, dev);
        }
    } catch(...) {
        std::cout << "addDev -ERR type" << std::endl;
    }
    return res;
}

void Peripherals::removeDev(int ioIndex, int devIndex) {
    connComposition->removeDev(ioIndex, devIndex);
}

std::pair<std::vector<std::string>, std::vector<std::string>> Peripherals::getDevProperty(int ioIndex, int devIndex) const {
    return connComposition->getDevProperty(ioIndex, devIndex);
}

std::pair<std::vector<std::string>, std::vector<std::string>> Peripherals::getDevStatus(int ioIndex, int devIndex) const {
    return connComposition->getDevStatus(ioIndex, devIndex);
}

std::vector<std::string> Peripherals::getAvailableDev() const {
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    return devFactory->getAvailableTypeDevice();
}

int Peripherals::getDevCount(const int ioIndex, const int devIndex) const {
    return connComposition->getDevCount(ioIndex);
}

bool Peripherals::devExecCommand(int ioIndex, int devIndex,
                                 std::string commandType, std::vector<std::string> keys, std::vector<std::string> params) {
    if(connComposition->devExecFutureCommand(ioIndex, devIndex, commandType, keys, params)) {
        bool executed = false;
        QObject::connect(connComposition.get(), &ConnectionComposition::devExecReadyCommand, this, [&]() {
            executed = true;
        });
        while(!executed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        return executed;
    }
    return false;
}
