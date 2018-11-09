#include "deviceCollector.h"

DeviceCollector::DeviceCollector() {
    this->isIdle = false;
}

bool DeviceCollector::getIsIdle() {
    return isIdle;
}

void DeviceCollector::addCommand(QList<CommandController::sCommandData> commands) {

}

void DeviceCollector::checkDeviceIsOnline(QString devType, QStringList keyParam, QStringList valParam) {
//    sendCustomCommandUseCallback(devType, "check device is connected", keyParam, valParam);
//    checkDeviceStruct.devType = devType;
//    QTimer *t_timer = new QTimer();
//    connect(t_timer , &QTimer::timeout, [=]() {
//        if(checkDeviceStruct.isReady) {
//            QString devFindId = checkDeviceStruct.checkedDeviceUniqName;
//            bool findResult = checkDeviceStruct.result;
//            checkDeviceStruct.checkedDeviceUniqName.clear();
//            checkDeviceStruct.isIdle = true;
//            checkDeviceStruct.isProcessed = false;
//            checkDeviceStruct.isReady = false;
//            checkDeviceStruct.result = false;
//            t_timer ->stop();
//            disconnect(t_timer , &QTimer::timeout, this, nullptr);
//            delete t_timer ;
//            emit deviceCheckIsReady(checkDeviceStruct.devType,
//                                    devFindId, findResult);
//        }
//    });
//    t_timer->start(100);
}

void DeviceCollector::onReplySend() {
//    emit readReplyData();
}

void DeviceCollector::devShedullerSlot() {
//    CommandController::sCommandData command;
//    if(!commandController->commandsIsEmpty()) {
//        if(commandController->getCommandFirstCommand().first == true) {
//            devShedullerTimer->stop();
//            emit writeData(commandController->getCommandFirstCommand().second.commandOptionData);
//            sendReqTimer.reset(new QTimer);
//            sendReqTimer->setSingleShot(true);
//            QObject::connect(sendReqTimer.data(), SIGNAL(timeout()), this, SLOT(onReplySend()));
//            sendReqTimer->start(commandController->getCommandFirstCommand().second.isNeedIncreasedDelay
//                                ? delayIncreasedCommandMs : delayTypicalCommandMs);
//        }
//    } else {
//        if(!deviceMap.empty()) {
//            if(devMutex->tryLock(100)) {
//                if(indexProcessedDev > deviceMap.size()-1) {
//                    indexProcessedDev = 0;
//                }
//                int sizeCommand = 0;
//                auto dev = deviceMap.at(indexProcessedDev);
//                if(!deviceMap.empty()) {
//                    if(indexProcessedDev < deviceMap.size()-1) {
//                        indexProcessedDev++;
//                    } else {
//                        indexProcessedDev = 0;
//                    }
//                }
//                switch(dev.second->getState()) {
//                case DeviceAbstract::STATE_DISCONNECTED:
//                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                        command = dev.second->getCommandToCheckConnected();
//                        command.commandType = CommandController::E_CommandType_send_typical_request;
//                        dev.second->makeDataToCommand(command);
//                        commandController->addCommandToStack(command);
//                    }
//                    break;
//                case DeviceAbstract::STATE_GET_TYPE:
//                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                            command = dev.second->getCommandToGetType();
//                            command.commandType = CommandController::E_CommandType_send_typical_request;
//                            dev.second->makeDataToCommand(command);
//                            commandController->addCommandToStack(command);
//                        }
//                    }
//                    break;
//                case DeviceAbstract::STATE_CHECK_PASSWORD:
//                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                        command = dev.second->getCommandtoCheckPassword();
//                        command.commandType = CommandController::E_CommandType_send_typical_request;
//                        dev.second->makeDataToCommand(command);
//                        commandController->addCommandToStack(command);
//                    }
//                    break;
//                case DeviceAbstract::STATE_START_INIT:
//                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                        for(sizeCommand=0; sizeCommand!= dev.second->getCommandListToInit().size(); sizeCommand++) {
//                            command = dev.second->getCommandListToInit().at(sizeCommand);
//                            command.commandType = CommandController::E_CommandType_send_typical_request;
//                            dev.second->makeDataToCommand(command);
//                            commandController->addCommandToStack(command);
//                        }
//                    }
//                    break;
//                case DeviceAbstract::STATE_NORMAL_READY:
//                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
//                        for(sizeCommand=0; sizeCommand != dev.second->getCommandListToCurrentData().size(); sizeCommand++) {
//                            command = dev.second->getCommandListToCurrentData().at(sizeCommand);
//                            command.commandType = CommandController::E_CommandType_send_typical_request;
//                            dev.second->makeDataToCommand(command);
//                            commandController->addCommandToStack(command);
//                        }
//                    }
//                    break;
//                }
//                unlockMutextDevMap();
//            }
//        }
//    }
}

void DeviceCollector::placeReplyDataFromInterface(QByteArray data) {
//    if(commandController->getCommandFirstCommand().first) {
//        auto command = commandController->getCommandFirstCommand().second;
//        switch (command.commandType) {
//        case CommandController::E_CommandType_send_typical_request:
//        case CommandController::E_CommandType_command_without_request:
//            for(auto dev: deviceMap) {
//                if(dev.second->getUniqId() == command.deviceIdent) {
//                    dev.second->placeDataReplyToCommand(data, command);
//                    break;
//                }
//            }
//            commandController->removeFirstCommand();
//            break;
//        case CommandController::E_CommandType_send_security_request: {
//            if(command.deviceTypeName == QString(Progress_tmk24::name)) {
//                Progress_tmk24 *p_device = nullptr;
//                // TODO: need uniqPtr
//                p_device = new Progress_tmk24(checkDeviceStruct.checkedDeviceUniqName,
//                                              "header", QPair<QStringList,QStringList>(QStringList(),QStringList()), nullptr);
//                if(p_device != nullptr) {
//                    checkDeviceStruct.result = p_device->placeDataReplyToCommand(data, commandController->getCommandFirstCommand().second);
//                    checkDeviceStruct.isReady = true;
//                    commandController->removeFirstCommand();
//                    delete p_device;
//                }
//            } else if(factoryType == Type_Progress_tmk4UX) {
//            } else  {}
//        }
//            break;
//        default:
//            qDebug() << "deviceFactoty: [placeReplyDataFromInterface] - undefined command -ERR = " << command.commandType;
//            commandController->removeFirstCommand();
//            break;
//        }
//    }
//    //-- start sheduller after reply
//    devShedullerTimer->start();
}

//void DeviceCollector::lockMutextDevMap() {
//    devMutex->tryLock(1000);
//}
//void DeviceCollector::unlockMutextDevMap() {
//    devMutex->unlock();
//}

bool DeviceCollector::sendCustomCommadToDev(int indexDev, QString operation) {
//    QList<CommandController::sCommandData> command;
//    bool res = false;
//    if(!deviceMap.isEmpty()) {
//        if((indexDev >= 0) && (indexDev <= deviceMap.size()-1)) {
//            command = findDeviceByIndex(indexDev)->second->getCommandCustom(operation);
//            // что требует подтверждения о выполнении (на форме)
//            for(auto cIt: command) {
//                findDeviceByIndex(indexDev)->second->makeDataToCommand(cIt);
//                cIt.commandType = CommandController::E_CommandType_send_typical_request;
//                commandController->addCommandToStack(cIt);
//                res = true;
//            }
//        }
//    }
//    return res;
}

bool DeviceCollector::sendCustomCommadToDev(int indexDev, QString operation, QStringList keys, QStringList values) {
//    QList<CommandController::sCommandData> command;
//    QPair<QStringList,QStringList> arguments;
//    bool res = false;
//    for(int i=0; i<keys.size(); i++) {
//        arguments.first.push_back(keys.at(i));
//        arguments.second.push_back(values.at(i));
//    }
//    command = findDeviceByIndex(indexDev)->second->getCommandCustom(operation, arguments);
//    // что требует подтверждения о выполнении (на форме)
//    for(auto cIt: command) {
//        findDeviceByIndex(indexDev)->second->makeDataToCommand(cIt);
//        cIt.commandType = CommandController::E_CommandType_send_typical_request;
//        commandController->addCommandToStack(cIt);
//        res = true;
//    }
//    return res;
}

void DeviceCollector::sendCustomCommandUseCallback(QString devType, QString operation, QStringList keys, QStringList values) {
//    QList<CommandController::sCommandData> commands;
//    if(type == Type_Progress_Tmk24) {
//        lockMutextDevMap();
//        QString uniqIdDevice;
//        for(int keyCoun = 0; keyCoun<keys.size(); keyCoun++) {
//            if(keys.at(keyCoun) == "id") {
//                uniqIdDevice = values.at(keyCoun);
//            }
//        }
//        if(uniqIdDevice.length() != 0) {
//            Progress_tmk24 *pdevice = new Progress_tmk24(uniqIdDevice, "tHeader", QPair<QStringList,QStringList>(keys, values), nullptr);
//            checkDeviceStruct.checkedDeviceUniqName = uniqIdDevice;
//            checkDeviceStruct.isProcessed = true;
//            checkDeviceStruct.isIdle = false;
//            checkDeviceStruct.isReady = false;
//            checkDeviceStruct.result = false;
//            commands = pdevice->getCommandCustom(operation);
//            for(int i=0; i<commands.size(); i++) {
//                auto tcommand = commands.at(i);
//                tcommand.commandType = CommandController::E_CommandType_send_security_request;
//                tcommand.deviceTypeName = QString(pdevice->name);
//                pdevice->makeDataToCommand(tcommand);
//                commandController->addCommandToStack(tcommand);
//            }
//            delete pdevice;
//        }
//        unlockMutextDevMap();
//    } else { // TODO:

//    }
}

void DeviceCollector::setDeviceReInitByIndex(int index) {
//    findDeviceByIndex(index)->second->setState(DeviceAbstract::STATE_DISCONNECTED);
}
