#include "commandController.h"

CommandController::CommandController(QObject *parent) : QObject(parent) {
    this->commandQueue = std::make_shared<std::deque<Command*>>();
    this->handlerThread = std::make_shared<std::thread>(handlerFunction, lock.get(), commandQueue.get());
    this->handlerThread->detach();
}

CommandController::~CommandController() {
    handlerThread.reset();
}

bool CommandController::addCommandToStack(QList<Command*> commandData) {
    std::lock_guard<std::mutex> guard(*lock.get());
    while(!(commandQueue->empty())) {
        commandQueue->push_back(commandData.takeLast());
    }
    return !commandQueue->empty();
}

Command* CommandController::getFirstCommand() const {
    std::lock_guard<std::mutex> guard(*lock.get());
    if(!commandQueue->empty()) {
        return commandQueue->front();
    }
    return nullptr;
}

void CommandController::removeFirstCommand() {
    std::lock_guard<std::mutex> guard(*lock.get());
    if(!commandQueue->empty()) {
        commandQueue->pop_front();
    }
}

bool CommandController::getIsEmpty() {
    return commandQueue->empty();
}

void CommandController::handlerFunction(std::mutex* pMutex, std::deque<Command*>* queue) {
    std::shared_ptr<Peripherals> peripherals = std::make_shared<Peripherals>();
    while(1) {
        if(pMutex->try_lock()) {
            if(!queue->empty()) {
                CommandController::commandInterprerator(queue->front(), peripherals.get());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void CommandController::commandInterprerator(Command* command, Peripherals* peripherals) {
    if(command->getCommand() == "getIoAddTypes") {
        //QStringList Controller::getIoAddTypes(QString typeName) {
        ////    return peripherals->getAvailableIo(typeName);
        //}
    }
    if(command->getCommand() == "addIo") {
        //bool Controller::addIo(QString ioTypeName, QString ioName, QStringList keys, QStringList values) {
        //    Command tcommand;
        //    tcommand.setDelayRequstMs(0);
        ////    std::shared_ptr<Command> command = std::make_shared<Command>();
        ////    command->setCommand("addIo");
        ////    keys << "ioTypeName" << "ioName";
        ////    values << ioTypeName << ioName;
        ////    command->setArgs(keys, values);
        ////    comma
        //    return true;
        //}
    }
    if(command->getCommand() == "removeIo") {
        //void Controller::removeIo(int ioIndex) {
        ////    peripherals->removeIo(ioIndex);
        ////    ioTreeModel.removeIo(ioIndex);
        //    emit removeIoSuccesSignal(ioIndex);
        //}
    }
    if(command->getCommand() == "addDevToIo") {
        //bool Controller::addDevToIo(int ioIndex, QString devTypeName, QStringList keys, QStringList param) {
        ////    bool res = peripherals->addDev(ioIndex, devTypeName, keys, param);
        ////    if(res) {
        ////        ioTreeModel.addDevToIo(ioIndex, devTypeName);
        ////        emit addDevSuccesSignal(ioIndex, devTypeName, keys, param);
        ////    } else {
        ////        emit addDevFailSignal(devTypeName, tr("Ошибка добавления устройства"));
        ////    }
        ////    return res;
        //}
    }
    if(command->getCommand() == "removeDev") {
        //void Controller::removeDev(int ioIndex, int devIndex) {
        ////    peripherals->removeDev(ioIndex, devIndex);
        ////    ioTreeModel.removeDevToConnection(ioIndex, devIndex);
        ////    emit removeDevSuccesSignal(ioIndex, devIndex);
        //}
    }
    if(command->getCommand() == "getDevAddTypes") {
        //QStringList Controller::getDevAddTypes() const {
        ////    return peripherals->getAvailableDev();
        //}
    }
    if(command->getCommand() == "devExecCommand") {
        //bool Controller::devExecCommand(int ioIndex, int devIndex, const QString commandType,
        //                                const QStringList keys, const QStringList params) {
        ////    return peripherals->devExecCommand(ioIndex, devIndex, commandType, keys, params);
        //}
    }
}

