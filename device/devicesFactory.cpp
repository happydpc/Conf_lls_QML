#include "devicesFactory.h"
#include <QtDebug>
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DevicesFactory::DevicesFactory() {
    this->devShedullerTimer = new QTimer();
    this->devShedullerTimer->start(100);
    this->devMutex = new QMutex();
    connect(this->devShedullerTimer, SIGNAL(timeout()), this, SLOT(devShedullerSlot()));
}

DevicesFactory::~DevicesFactory() {}

bool DevicesFactory::addNewDevice(E_DeviceType type, QString uniqDevName, QStringList parameters, ServiceDevicesAbstract *pDevService) {
    bool res = false;
    if(type == Type_Progress_Tmk24) {
        if(findDeviceByUnicIdent(uniqDevName) == nullptr) {
            lockMutextDevMap();
            deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Progress_tmk24(uniqDevName, parameters.at(0), pDevService)));
            unlockMutextDevMap();
            emit deviceUpdateTree(DevicesFactory::Type_Update_Added, 0); // TODO: 0
            res = true;
        }
    } else if(type == Type_Progress_tmk4UX) {
    } else if(type == Type_Nozzle_rev_0_00) {
        if(findDeviceByUnicIdent(uniqDevName) == nullptr) {
            lockMutextDevMap();
            deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Nozzle_Revision_0_00_Oct_2018(uniqDevName)));
            unlockMutextDevMap();
            emit deviceUpdateTree(DevicesFactory::Type_Update_Added, 0); // TODO: 0
            res = true;
        }
    } else {
        throw QString("undefined class");
    }

    // TODO: может быть лучше как-то подругому перехватывать указатаель?
    connect(findDeviceByUnicIdent(uniqDevName)->second,
            SIGNAL(eventDeviceUpdateState(DeviceAbstract::E_DeviceEvent,QString,int,QString,QStringList, CommandController::sCommandData)),
            this, SLOT(deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent,QString,int,QString,QStringList, CommandController::sCommandData)));
    return res;
}

bool DevicesFactory::removeDevice(QString uniqDevName) {
    bool res = false;
    lockMutextDevMap();
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByUnicIdent(uniqDevName);
    if(pDev != nullptr) {
        deviceMap.erase(pDev); // TOOD: 0
        res = true;
    }
    unlockMutextDevMap();
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return res;
}

bool DevicesFactory::removeDeviceByIndex(int index) {
    bool res = false;
    lockMutextDevMap();
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByIndex(index);
    if(pDev != nullptr) {
        deviceMap.erase(pDev); // TOOD: 0
        res = true;
    }
    unlockMutextDevMap();
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return res;
}

bool DevicesFactory::removeDeviceAll() {
    lockMutextDevMap();
    deviceMap.clear();
    unlockMutextDevMap();
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return true;
}


int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QString DevicesFactory::getDeviceName(int index) {
    return findDeviceByIndex(index)->second->getDevTypeName();
}

QString DevicesFactory::getDeviceTypeNameByType(DevicesFactory::E_DeviceType type) {
    if(type == DevicesFactory::Type_Progress_tmk4UX) {
        return QString::fromUtf8(Progress_tmk4UX::name, strlen(Progress_tmk4UX::name));
    } else if(type == DevicesFactory::Type_Progress_Tmk24) {
        return QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name));
    } else {
        qDebug() << "undefined type name!";
        throw QString("undefined type name!");
    }
}

DevicesFactory::E_DeviceType DevicesFactory::getDeviceType(QString typeText) {
    if(typeText == QString::fromUtf8(Progress_tmk4UX::name, strlen(Progress_tmk4UX::name))) {
        return DevicesFactory::Type_Progress_tmk4UX;
    } else if(typeText == QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name))) {
        return DevicesFactory::Type_Progress_Tmk24;
    } else if(typeText == QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018::name, strlen(Nozzle_Revision_0_00_Oct_2018::name))) {
        return DevicesFactory::Type_Nozzle_rev_0_00;
    }
    else {
        qDebug() << "undefined type name!";
        throw QString("undefined type name!");
    }
}

DevicesFactory::E_DeviceType DevicesFactory::getDeviceType(int index) {
    return getDeviceType(findDeviceByIndex(index)->second->getDevTypeName());
}

void DevicesFactory::setDeviceInitCommandByIndex(int index) {
    QList<CommandController::sCommandData>commands = findDeviceByIndex(index)->second->getCommandListToInit();
    for(auto i:commands) {
        findDeviceByIndex(index)->second->makeDataToCommand(i);
        i.isNeedAckMessage = false;
        commandList.push_back(i);
    }
}

QStringList DevicesFactory::getDeviceHeaderByIndex(int index) {
    if(deviceMap.empty()) {return QStringList("");}
    return QStringList(QString("%1 [%2]")
                       .arg(getDeviceName(index))
                       .arg(getDeviceIdTextByIndex(index)));
}

QList<int> DevicesFactory::getDeviceChartByIndex(int index) {
    if(deviceMap.empty()) {return QList<int>();}
    return findDeviceByIndex(index)->second->getChart();
}

QPair<QStringList,QStringList> DevicesFactory::getDeviceCurrentDataByIndex(int index) {
    if(deviceMap.empty()) {return QPair<QStringList,QStringList>();}
    return findDeviceByIndex(index)->second->getCurrentData();
}

QPair<QStringList,QStringList> DevicesFactory::getDevicePropertyByIndex(int index) {
    if(deviceMap.empty()) {return QPair<QStringList,QStringList>();}
    return findDeviceByIndex(index)->second->getPropertyData();
}

QString DevicesFactory::getDeviceIdTextByIndex(int index) {
    if(deviceMap.empty()) {return QString();}
    return findDeviceByIndex(index)->first;
}

QPair<QStringList,QStringList> DevicesFactory::getDeviceSettigns(int indexDev) {
    return findDeviceByIndex(indexDev)->second->getSettings();
}

QStringList DevicesFactory::getDeviceErrrors(int indexDev) {
    return findDeviceByIndex(indexDev)->second->getErrors();
}

int DevicesFactory::getDeviceStatusByIndex(int index) {
    if(deviceMap.empty()) {return false; }
    DeviceAbstract::E_State state = findDeviceByIndex(index)->second->getState();
    int ret = 0;
    switch(state) {
    case DeviceAbstract::STATE_DISCONNECTED :
        ret = 0;
        break;
    case DeviceAbstract::STATE_GET_TYPE :
    case DeviceAbstract::STATE_CHECK_PASSWORD :
    case DeviceAbstract::STATE_START_INIT :
    case DeviceAbstract::STATE_NORMAL_READY :
        ret = 1;
        break;
    }
    return ret;
}

DeviceAbstract::E_State DevicesFactory::getDevStateByIndex(int index) {
    return findDeviceByIndex(index)->second->getState();
}

QStringList DevicesFactory::getAvailableDeviceTypes() {
    QStringList types;
    types << QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name));
    types << QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018::name, strlen(Nozzle_Revision_0_00_Oct_2018::name));
    return types;
}

DeviceAbstract * DevicesFactory::getDeviceToDeviceAbstract(int index) {
    return deviceMap.at(index).second;
}

void DevicesFactory::devShedullerSlot() {
    int sizeCommand = 0;
    if(!deviceMap.empty()) {
        if(!commandList.isEmpty()) {
            devShedullerTimer->stop();
            emit writeData(commandList.first().commandOptionData);
            QTimer::singleShot(commandList.first().isNeedIncreasedDelay ? delayIncreasedCommandMs : delayTypicalCommandMs,
                               Qt::PreciseTimer, [&] {
                emit readReplyData();
            });
        } else {
            if(devMutex->tryLock(100)) {
                CommandController::sCommandData command;
                if(indexProcessedDev > deviceMap.size()-1) {
                    indexProcessedDev = 0;
                }
                auto dev = deviceMap.at(indexProcessedDev);
                if(!deviceMap.empty()) {
                    if(indexProcessedDev < deviceMap.size()-1) {
                        indexProcessedDev++;
                    } else {
                        indexProcessedDev = 0;
                    }
                }
                switch(dev.second->getState()) {
                case DeviceAbstract::STATE_DISCONNECTED:
                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
                        command = dev.second->getCommandToCheckConnected();
                        dev.second->makeDataToCommand(command);
                        commandList.push_back(command);
                    }
                    break;
                case DeviceAbstract::STATE_GET_TYPE:
                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
                        if(dev.second->getPriority() == 0) { // TODO: loop need priority
                            command = dev.second->getCommandToGetType();
                            dev.second->makeDataToCommand(command);
                            commandList.push_back(command);
                        }
                    }
                    break;
                case DeviceAbstract::STATE_CHECK_PASSWORD:
                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
                        command = dev.second->getCommandtoCheckPassword();
                        dev.second->makeDataToCommand(command);
                        commandList.push_back(command);
                    }
                    break;
                case DeviceAbstract::STATE_START_INIT:
                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
                        for(sizeCommand=0; sizeCommand!= dev.second->getCommandListToInit().size(); sizeCommand++) {
                            command = dev.second->getCommandListToInit().at(sizeCommand);
                            dev.second->makeDataToCommand(command);
                            commandList.push_back(command);
                        }
                    }
                    break;
                case DeviceAbstract::STATE_NORMAL_READY:
                    if(dev.second->getPriority() == 0) { // TODO: loop need priority
                        for(sizeCommand=0; sizeCommand != dev.second->getCommandListToCurrentData().size(); sizeCommand++) {
                            command = dev.second->getCommandListToCurrentData().at(sizeCommand);
                            dev.second->makeDataToCommand(command);
                            commandList.push_back(command);
                        }
                    }
                    break;
                }
                unlockMutextDevMap();
            }
        }
    }
}

void DevicesFactory::placeReplyDataFromInterface(QByteArray data) {
    for(auto dev: deviceMap) {
        if(dev.second->getUniqIdent() == commandList.first().deviceIdent) {
            dev.second->placeDataReplyToCommand(data, commandList.first());
            break;
        }
    }
    commandList.pop_front();
    //-- start sheduller after reply
    devShedullerTimer->start();
}

// сюда приходят все сигналы от девайсов (смена состояние и рез кастомных команд)
void DevicesFactory::deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent eventType, QString devUniqueId,
                                                    int command, QString operationResult, QStringList customData,
                                                    CommandController::sCommandData commandData) {
    switch (eventType) {
    case DeviceAbstract::Type_DeviceEvent_Connected:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceConnectedSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_Disconnected:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceDisconnectedSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_Inited:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceReadyInitSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_ReadyReadProperties:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceReadyPropertiesSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_CurrentDataUpdated:
        // TODO: пересылаем на верх
        emit deviceReadyCurrentDataSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_PasswordError:
        // пароль не совпадает
        emit deviceUpdateTree(DevicesFactory::Type_Update_PasswordIncorrect, findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_TypeError:
        // тип не совпадает с заявленным
        emit deviceUpdateTree(DevicesFactory::Type_Update_TypeIncorrect, findDeviceIndex(devUniqueId));
        // удаляем устройство
        removeDeviceByIndex(findDeviceIndex(devUniqueId));
        break;
    case DeviceAbstract::Type_DeviceEvent_LogMessage:
        emit deviceReadyLog(findDeviceIndex(devUniqueId), customData);
        break;
    case DeviceAbstract::Type_DeviceEvent_ExectCustomCommand:
        emit deviceReadyCustomCommand(findDeviceIndex(devUniqueId), operationResult, customData, commandData);
        break;
    default: break;
    }
}

void DevicesFactory::lockMutextDevMap() {
    //qDebug() << "-lockMutextDevMap";
    devMutex->lock();
}
void DevicesFactory::unlockMutextDevMap() {
    //qDebug() << "-unlockMutextDevMap";
    devMutex->unlock();
}

void DevicesFactory::sendCustomCommadToDev(int indexDev, QString operation) {
    QList<CommandController::sCommandData> command;
    command = findDeviceByIndex(indexDev)->second->getCommandCustom(operation);
    // что требует подтверждения о выполнении (на форме)
    for(auto cIt: command) {
        findDeviceByIndex(indexDev)->second->makeDataToCommand(cIt);
        commandList.push_back(cIt);
    }
}

void DevicesFactory::sendCustomCommadToDev(int indexDev, QString operation, QStringList keys, QStringList values) {
    QList<CommandController::sCommandData> command;
    QPair<QStringList,QStringList> arguments;
    for(int i=0; i<keys.size(); i++) {
        arguments.first.push_back(keys.at(i));
        arguments.second.push_back(values.at(i));
    }
    command = findDeviceByIndex(indexDev)->second->getCommandCustom(operation, arguments);
    // что требует подтверждения о выполнении (на форме)
    for(auto cIt: command) {
        findDeviceByIndex(indexDev)->second->makeDataToCommand(cIt);
        commandList.push_back(cIt);
    }
}

QPair<QString,DeviceAbstract*>* DevicesFactory::findDeviceByIndex(int index) {
    int counter=0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(counter == index) {
            return it;
        }
        counter++;
    }
    return nullptr;
}

QPair<QString,DeviceAbstract*>* DevicesFactory::findDeviceByUnicIdent(QString name) {
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(it->first == name) {
            return it;
        }
    }
    return nullptr;
}

int DevicesFactory::findDeviceIndex(QString uniqNameId) {
    int index = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(it->first == uniqNameId) {
            return index;
        }
        index++;
    }
    return -1;
}

void DevicesFactory::setDeviceReInitByIndex(int index) {
    findDeviceByIndex(index)->second->setState(DeviceAbstract::STATE_DISCONNECTED);
}
