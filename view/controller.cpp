#include "controller.h"

//// io
//void addIoSucces(std::string ioType, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
//void addIoFail(std::string ioType, std::string ioName);
//void ioUpdateProperty(std::string ioType, int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
//void removeIoSucces(int ioIndex);
//void ioActivate(int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
//void ioTreeIsEmpty();

//// dev
//void addDevSucces(int ioIndex, std::string devType, std::list<std::string> devKeyProperty, std::list<std::string> devValueProperty);
//void addDeviceFail(std::string devName, std::string errorMessage);
//void removeDevSucces(int ioIndex, int devIndex);
//void devExecComamndReady(int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
//void devConnected(int ioIndex, int devIndex, std::string typeDev);
//void devReady(int ioIndex, int devIndex, std::string typeDev);
//void devDisconnected(int ioIndex, int devIndex, std::string typeDev);
//void devActivateProperty(std::string devType, int ioIndex, int devIndex);
//void devUpdatePeriodicData(std::string devType, int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
//void devUpdateLogMessage(int ioIndex, int devIndex, std::string codeMessage, std::string message);
//void ioAndDeviceFullFlushData();

void signal_get_availableIo(std::list<std::string> ioList);

Controller::Controller(QObject *parent) : QObject(parent) {
    this->commandController = std::make_shared<CommandController>();
    QObject::connect(commandController.get(), &CommandController::commandExecuted, [&](Command * command) {
        if(command->getCommand() == "requestGetIoAddTypes") {
            emit signal_get_availableIo(command->getArgs().first, command->getArgs().first);
        }
        if(command->getCommand() == "requestAddIo") {
            emit signal_get_availableIo(command->getArgs().first, command->getArgs().first);
        }
        if(command->getCommand() == "requestRemoveIo") {
            emit signal_getAvailableIo(command->getArgs().first, command->getArgs().first);
//            peripherals->getAvailableIo(typeName);
        }
        if(command->getCommand() == "requestAddDevToIo") {
//                bool res = peripherals->addDev(ioIndex, devTypeName, keys, param);
//                if(res) {
//                    ioTreeModel.addDevToIo(ioIndex, devTypeName);
//                    emit addDevSuccesSignal(ioIndex, devTypeName, keys, param);
//                } else {
//                    emit addDevFailSignal(devTypeName, tr("Ошибка добавления устройства"));
//                }
//                return res;
        }
        if(command->getCommand() == "requestRemoveDev") {
            //    peripherals->removeDev(ioIndex, devIndex);
            //    ioTreeModel.removeDevToConnection(ioIndex, devIndex);
            //    emit removeDevSuccesSignal(ioIndex, devIndex);
        }
        if(command->getCommand() == "requestGetDevAddTypes") {
//    return peripherals->getAvailableDev();
        }
        if(command->getCommand() == "requestDevExecCommand") {
//    return peripherals->devExecCommand(ioIndex, devIndex, commandType, keys, params);
        }
        if(command->getCommand() == " ") {
//    return peripherals->getAvailableIo(typeName);
        }
    });
}

void Controller::requestGetIoAddTypes(std::string typeName) {
    std::list<std::string> keys, values;
    std::shared_ptr<Command> command = std::make_shared<Command>();
    command->setCommand("getIoAddTypes");
    keys.push_back("typeName");
    values.push_back(typeName);
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

void Controller::requestAddIo(std::string ioTypeName, std::string ioName, std::list<std::string> keys, std::list<std::string> values) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    command->setCommand("addIo");
    keys.push_back("ioTypeName");
    keys.push_back("ioName");
    values.push_back(ioTypeName);
    values.push_back(ioName);
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

void Controller::requestRemoveIo(int ioIndex) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    std::list<std::string> keys, values;
    command->setCommand("removeIo");
    keys.push_back("ioIndex");
    values.push_back(std::to_string(ioIndex));
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
//    peripherals->removeIo(ioIndex);
//    ioTreeModel.removeIo(ioIndex);
//    emit removeIoSuccesSignal(ioIndex);
}

void Controller::requestAddDevToIo(int ioIndex, std::string devTypeName, std::list<std::string> keys, std::list<std::string> values) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    command->setCommand("addDevToIo");
    keys.push_back("ioIndex");
    keys.push_back("devTypeName");
    values.push_back(std::to_string(ioIndex));
    values.push_back(devTypeName);
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

void Controller::requestRemoveDev(int ioIndex, int devIndex) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    std::list<std::string> keys, values;
    command->setCommand("addDevToIo");
    keys.push_back("ioIndex");
    keys.push_back("devIndex");
    values.push_back(std::to_string(ioIndex));
    values.push_back(std::to_string(devIndex));
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

void Controller::requestGetDevAddTypes() {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    std::list<std::string> keys, values;
    command->setCommand("getDevAddTypes");
    keys.push_back("getDevAddTypes");
    values.push_back("getDevAddTypes");
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

void Controller::requestDevExecCommand(int ioIndex, int devIndex, const std::string commandType,
                                std::list<std::string> keys, std::list<std::string> values) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    command->setCommand("devExecCommand");
    keys.push_back("ioIndex");
    keys.push_back("devIndex");
    keys.push_back("commandType");
    values.push_back(std::to_string(ioIndex));
    values.push_back(std::to_string(devIndex));
    values.push_back(commandType);
    command->setArgs(keys, values);
    commandController->addCommandToStack(command.get());
}

std::string Controller::getTypeLogo() const {
#ifdef PROGRESS
    return "progress";
#endif
#ifdef GLOSSAV
    return("gs");
#endif
    return std::string();
}

ModelDevTree* Controller::getIoTreeModel() {
    return &ioTreeModel;
}
