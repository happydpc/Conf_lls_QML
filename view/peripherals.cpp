#include "peripherals.h"
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

//    return connFactory->getAvailableName(typeIoName);
std::list<std::string> Peripherals::getAvailableIo(const std::string typeIoName) const {
//    CommandController::sCommandData command;
//    command.command = "getAvailableIo";
//    command.args.key << "typeIoName";
//    command.args.value << typeIoName;
//    command.delay_request_ms = 0;
//    commandController->addCommandToStack(command);
}

//    return connComposition->addIo(connFactory->createConnection(typeIoName, ioName, std::pair<std::list<std::string>,std::list<std::string>>(keyParam, valueParam)));
bool Peripherals::addIo(const std::string typeIoName,
                        const std::string ioName,
                        const std::list<std::string> keyParam,
                        const std::list<std::string> valueParam) {
//    CommandController::sCommandData command;
//    command.command = "addIo";
//    command.args.key << "typeIoName" << "ioName" << "keyParam" << "valueParam";
//    command.args.value << typeIoName << ioName << keyParam << valueParam;
//    command.delay_request_ms = 0;
//    return commandController->addCommandToStack(command);
}

void Peripherals::removeIo(int ioIndex) {
    connComposition->removeIo(ioIndex);
}

std::pair<std::list<std::string>, std::list<std::string>> Peripherals::getIoProperty(int ioIndex) const {
    return connComposition->getIoProperty(ioIndex);
}

bool Peripherals::addDev(int ioIndex, const std::string devTypeName, const std::list<std::string> keyParam, const std::list<std::string> valueParam) {
    bool res = false;
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    auto dev = devFactory->newDevice(devTypeName, keyParam, valueParam);
    if(dev != nullptr) {
        connComposition->addDev(ioIndex, dev);
    }
    return res;
}

void Peripherals::removeDev(int ioIndex, int devIndex) {
    connComposition->removeDev(ioIndex, devIndex);
}

std::pair<std::list<std::string>, std::list<std::string>> Peripherals::getDevProperty(int ioIndex, int devIndex) const {
    return connComposition->getDevProperty(ioIndex, devIndex);
}

std::list<std::string> Peripherals::getAvailableDev() const {
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    return devFactory->getAvailableTypeDevice();
}

bool Peripherals::devExecCommand(int ioIndex, int devIndex,
                                 std::string commandType, std::list<std::string> keys, std::list<std::string> params) {
//    bool res = connComposition->devExecCommand(ioIndex, devIndex, commandType, keys, params);
//    QObject::connect(connComposition, ConnectionComposition::devExecFutureCommand())
//    void devExecComamndReadySignal(int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
//    return res;
}
