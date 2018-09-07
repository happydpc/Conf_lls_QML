#include "devicesFactory.h"
#include <QDebug>

DevicesFactory::DevicesFactory() {
    this->devShedullerTimer = new QTimer();
    this->devShedullerTimer->start(devShedullerControlInterval);

    connect(this->devShedullerTimer, SIGNAL(timeout()), this, SLOT(devShedullerSlot()));
}

DevicesFactory::~DevicesFactory() {}

bool DevicesFactory::addNewDevice(E_DeviceType type, QString uniqDevName, QStringList parameters) {
    if(type == Type_Progress_Tmk24) {
        deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Progress_tmk24(uniqDevName)));
        emit deviceUpdateTree(DevicesFactory::Type_Update_Added, 0); // TODO: 0
    } else if(type == Type_Progress_Tmk13) {
        deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Progress_tmk13(uniqDevName)));
        emit deviceUpdateTree(DevicesFactory::Type_Update_Added, 0); // TODO: 0
    } else {
        throw QString("undefined class");
    }

    // TODO: может быть лучше как-то подругому перехватывать указатаель?
    connect(findDeviceByUnicIdent(uniqDevName)->second, SIGNAL(eventDevice(DeviceAbstract::E_DeviceEvent,QString,QString)),
            this, SLOT(deviceEventSlot(DeviceAbstract::E_DeviceEvent,QString,QString)));

    return (bool)deviceMap.size();
}

bool DevicesFactory::removeDevice(QString uniqDevName) {
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByUnicIdent(uniqDevName);
    if(pDev != nullptr) {
        deviceMap.erase(pDev); // TOOD: 0
        emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
        return true;
    }
    return false;
}

int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QString DevicesFactory::getDeviceName(int index) {
    return findDeviceByIndex(index)->second->getDevTypeName();
}

QString DevicesFactory::getDeviceNameByType(DevicesFactory::E_DeviceType type) {
    if(type == DevicesFactory::Type_Progress_Tmk13) {
        return QString::fromUtf8(Progress_tmk13::name, strlen(Progress_tmk13::name));
    } else if(type == DevicesFactory::Type_Progress_Tmk24) {
        return QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name));
    } else {
        throw QString("undefined type name!");
    }
}

DevicesFactory::E_DeviceType DevicesFactory::getDeviceType(QString typeText) {
    if(typeText == QString::fromUtf8(Progress_tmk13::name, strlen(Progress_tmk13::name))) {
        return DevicesFactory::Type_Progress_Tmk13;
    } else if(typeText == QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name))) {
        return DevicesFactory::Type_Progress_Tmk24;
    } else {
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

QList<QString> DevicesFactory::getDeviceCurrentDataByIndex(int index) {
    if(deviceMap.empty()) {return QList<QString>();}
    return findDeviceByIndex(index)->second->getCurrentData();
}

QStringList DevicesFactory::getDevicePropertyByIndex(int index) {
    if(deviceMap.empty()) {return QStringList("");}
    return findDeviceByIndex(index)->second->getPropertyData();
}

QString DevicesFactory::getDeviceIdTextByIndex(int index) {
    if(deviceMap.empty()) {return QString();}
    return findDeviceByIndex(index)->first;
}

int DevicesFactory::getDeviceStatusByIndex(int index) {
    if(deviceMap.empty()) {return false; }
    DeviceAbstract::E_State state = findDeviceByIndex(index)->second->getState();
    int ret = 0;
    switch(state) {
        case DeviceAbstract::STATE_DISCONNECTED: ret = 0; break;
        case DeviceAbstract::STATE_NORMAL_READY: ret = 1;  break;
        case DeviceAbstract::STATE_NEED_INIT: ret = 2; break;
    }
    return ret;
}

QStringList DevicesFactory::getDeviceProperty(int indexDev) {
    if(deviceMap.empty()) {return QStringList("");}
    return findDeviceByIndex(indexDev)->second->getPropertyData();
}

DeviceAbstract::E_State DevicesFactory::getDevStateByIndex(int index) {
    return findDeviceByIndex(index)->second->getState();
}

QStringList DevicesFactory::getAvailableDeviceTypes() {
    QStringList types;
    types << QString::fromUtf8(Progress_tmk13::name, strlen(Progress_tmk13::name));
    types << QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name));
    return types;
}

void DevicesFactory::devShedullerSlot() {
    int sizeCommand = 0;
    if(!deviceMap.empty()) {
        if(!commandList.isEmpty()) {
            devShedullerTimer->stop();
            emit writeData(commandList.first().commandOptionData);
            QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, [&] {
                emit readReplyData();
            });
        } else {
            CommandController::sCommandData command;
            auto dev = deviceMap.at(indexProcessedDev);
            switch(dev.second->getState()) {
            case DeviceAbstract::STATE_DISCONNECTED:
                if(dev.second->getPriority() == 0) {
                    command = dev.second->getCommandToCheckConnected();
                    dev.second->makeDataToCommand(command);
                    commandList.push_back(command);
                }
                break;
            case DeviceAbstract::STATE_NEED_INIT:
                if(dev.second->getPriority() == 0) { // TOOD: loop
                    for(sizeCommand=0; sizeCommand!= dev.second->getCommandListToInit().size(); sizeCommand++) {
                        command = dev.second->getCommandListToInit().at(sizeCommand);
                        dev.second->makeDataToCommand(command);
                        commandList.push_back(command);
                    }
                }
                break;
            case DeviceAbstract::STATE_NORMAL_READY:
                if(dev.second->getPriority() == 0) { // TOOD: loop
                    for(sizeCommand=0; sizeCommand != dev.second->getCommandListToCurrentData().size(); sizeCommand++) {
                        command = dev.second->getCommandListToCurrentData().at(sizeCommand);
                        dev.second->makeDataToCommand(command);
                        commandList.push_back(command);
                    }
                }
                break;
            }
            if(!deviceMap.empty()) {
                if(indexProcessedDev < deviceMap.size()-1) {
                    indexProcessedDev++;
                } else {
                    indexProcessedDev = 0;
                }
            }
        }
    }
}

void DevicesFactory::placeReplyDataFromInterface(QByteArray data) {
    for(auto dev: deviceMap) {
        if(dev.second->getUniqIdent() == commandList.first().deviceIdent) {
            qDebug() << "placeDataReplyToCommand -len=" << data.length();
            dev.second->placeDataReplyToCommand(data);
            break;
        }
    }
    commandList.pop_front();
    //-- start sheduller after reply
    devShedullerTimer->start(devShedullerControlInterval);
}

// сюда приходят все сигналы от девайсов
void DevicesFactory::deviceEventSlot(DeviceAbstract::E_DeviceEvent eventType, QString devUniqueId, QString message) {
    qDebug() << "deviceEventSlot -" << message << "uniqId=" << devUniqueId;
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
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceReadyCurrentDataSignal(getDeviceType(findDeviceByUnicIdent(devUniqueId)->second->getDevTypeName()), devUniqueId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devUniqueId));
        break;
    default: qDebug() << "deviceEventSlot -type undefined!";
        break;
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
    return 0;
}

void DevicesFactory::setDeviceReInitByIndex(int index) {
    findDeviceByIndex(index)->second->setState(DeviceAbstract::STATE_DISCONNECTED);
}
