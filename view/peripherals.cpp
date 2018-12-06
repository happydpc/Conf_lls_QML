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
QStringList Peripherals::getAvailableIo(const QString typeIoName) const {
//    CommandController::sCommandData command;
//    command.command = "getAvailableIo";
//    command.args.key << "typeIoName";
//    command.args.value << typeIoName;
//    command.delay_request_ms = 0;
//    commandController->addCommandToStack(command);
}

//    return connComposition->addIo(connFactory->createConnection(typeIoName, ioName, QPair<QStringList,QStringList>(keyParam, valueParam)));
bool Peripherals::addIo(const QString typeIoName,
                        const QString ioName,
                        const QStringList keyParam,
                        const QStringList valueParam) {
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

QPair<QStringList, QStringList> Peripherals::getIoProperty(int ioIndex) const {
    return connComposition->getIoProperty(ioIndex);
}

bool Peripherals::addDev(int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam) {
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

QPair<QStringList, QStringList> Peripherals::getDevProperty(int ioIndex, int devIndex) const {
    return connComposition->getDevProperty(ioIndex, devIndex);
}

QStringList Peripherals::getAvailableDev() const {
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    return devFactory->getAvailableTypeDevice();
}

bool Peripherals::devExecCommand(int ioIndex, int devIndex,
                                 QString commandType, QStringList keys, QStringList params) {
//    bool res = connComposition->devExecCommand(ioIndex, devIndex, commandType, keys, params);
//    QObject::connect(connComposition, ConnectionComposition::devExecFutureCommand())
//    void devExecComamndReadySignal(int ioIndex, int devIndex, QStringList keys, QStringList values);
//    return res;
}
