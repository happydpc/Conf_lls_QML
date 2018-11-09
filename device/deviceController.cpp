#include "deviceController.h"

DeviceController::DeviceController() {
    this->deviceFactory = std::make_shared<DevicesFactory>();
    this->deviceCollector = std::make_shared<DeviceCollector>();

    this->updateTimer = std::make_unique<QTimer>();
    this->updateTimer->start(100);
    this->commandController = std::make_unique<CommandController>();
    connect(this->updateTimer.get(), SIGNAL(timeout()), this, SLOT(updater()));
}

DevicesFactory* DeviceController::getDeviceFactory() {
    DevicesFactory* p_ret_factoty = nullptr;
    p_ret_factoty = deviceFactory.get();
    return p_ret_factoty;
}

DeviceCollector* DeviceController::getDeviceCollector() {
    DeviceCollector* p_ret_collector = nullptr;
    p_ret_collector = deviceCollector.get();
    return p_ret_collector;
}

void DeviceController::updater() {
    static int indexProcessedDev = 0;
    int sizeCommand = 0;
    CommandController::sCommandData command;
    if(deviceCollector.get()->getIsIdle()) {
        if(deviceFactory.get()->getDeviceCount()) {
            if(!commandController->commandsIsEmpty()) {
                if(commandController->getCommandFirstCommand().first == true) {
                    //                    devShedullerTimer->stop();
                    //                    emit writeData(commandController->getCommandFirstCommand().second.commandOptionData);
                    //                    sendReqTimer.reset(new QTimer);
                    //                    sendReqTimer->setSingleShot(true);
                    //                    QObject::connect(sendReqTimer.data(), SIGNAL(timeout()), this, SLOT(onReplySend()));
                    //                    sendReqTimer->start(commandController->getCommandFirstCommand().second.isNeedIncreasedDelay
                    //                                        ? delayIncreasedCommandMs : delayTypicalCommandMs);
                }
            } else {
                DeviceAbstract *p_abstr_dev = nullptr;
                if(indexProcessedDev < deviceFactory.get()->getDeviceCount()-1) {
                    indexProcessedDev ++;
                } else {
                    indexProcessedDev = 0;
                }
                p_abstr_dev = getDeviceFactory()->getDeviceToDeviceAbstract(indexProcessedDev);
                if(p_abstr_dev != nullptr) {
                    switch(p_abstr_dev->getState()) {
                    case DeviceAbstract::STATE_DISCONNECTED:
                        if(p_abstr_dev->getPriority() == 0) { // TODO: loop need priority
                            commandController.get()->addCommandToStack(p_abstr_dev->getCommandToCheckConnected());
                        }
                        break;
                    case DeviceAbstract::STATE_GET_TYPE:
                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
                            if(dev.second->getPriority() == 0) { // TODO: loop need priority
                                command = dev.second->getCommandToGetType();
                                command.commandType = CommandController::E_CommandType_send_typical_request;
                                dev.second->makeDataToCommand(command);
                                commandController->addCommandToStack(command);
                            }
                        }
                        break;
                    case DeviceAbstract::STATE_CHECK_PASSWORD:
                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
                            command = dev.second->getCommandtoCheckPassword();
                            command.commandType = CommandController::E_CommandType_send_typical_request;
                            dev.second->makeDataToCommand(command);
                            commandController->addCommandToStack(command);
                        }
                        break;
                    case DeviceAbstract::STATE_START_INIT:
                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
                            for(sizeCommand=0; sizeCommand!= dev.second->getCommandListToInit().size(); sizeCommand++) {
                                command = dev.second->getCommandListToInit().at(sizeCommand);
                                command.commandType = CommandController::E_CommandType_send_typical_request;
                                dev.second->makeDataToCommand(command);
                                commandController->addCommandToStack(command);
                            }
                        }
                        break;
                    case DeviceAbstract::STATE_NORMAL_READY:
                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
                            for(sizeCommand=0; sizeCommand != dev.second->getCommandListToCurrentData().size(); sizeCommand++) {
                                command = dev.second->getCommandListToCurrentData().at(sizeCommand);
                                command.commandType = CommandController::E_CommandType_send_typical_request;
                                dev.second->makeDataToCommand(command);
                                commandController->addCommandToStack(command);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
