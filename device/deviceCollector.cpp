#include "deviceCollector.h"

DeviceCollector::DeviceCollector(interfacesAbstract *p_int_abstract) {
    this->int_abstract = p_int_abstract;
    this->reqIsBusy = false;
    this->isIdle = false;
    this->reqTimerHanler = std::make_unique<QTimer>();
    this->commandController = std::make_unique<CommandController>();
    connect(reqTimerHanler.get(), &QTimer::timeout, this, &DeviceCollector::controllHandler);
    reqTimerHanler.get()->start(50);
}

void DeviceCollector::controllHandler() {
    if((!reqIsBusy) && (!commandController.get()->commandsIsEmpty())) {
        sendReqTimer.reset(new QTimer);
        sendReqTimer->setSingleShot(true);
        int_abstract->sendData(commandController.get()->getCommandFirstCommand().second.commandOptionData);
        reqIsBusy = true;
        connect(sendReqTimer.data(), &QTimer::timeout, this, &DeviceCollector::readyReadReply);
        sendReqTimer->start(commandController.get()->getCommandFirstCommand().second.delay_send_ms == 0 ? 100 : commandController.get()->getCommandFirstCommand().second.delay_send_ms);
    }
}

void DeviceCollector::readyReadReply() {
    QByteArray rxData;
    int_abstract->readData(rxData);
    auto command = commandController->getCommandFirstCommand().second;
    switch (command.commandType) {
    case CommandController::E_CommandType_send_typical_request:
    case CommandController::E_CommandType_command_without_request:
    case CommandController::E_CommandType_send_security_request:
        emit reqReadyReplyDataToDevice(rxData, commandController.get()->getCommandFirstCommand().second);
        break;
    }
    reqIsBusy = false;
    commandController->removeFirstCommand();
}

void DeviceCollector::addCommand(QList<CommandController::sCommandData> commands) {
    commandController.get()->addCommandToStack(commands);
}

bool DeviceCollector::getIsIdle() {
    return commandController.get()->commandsIsEmpty();
}
