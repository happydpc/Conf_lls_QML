#include "devicesFactory.h"
#include <QtDebug>
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DevicesFactory::DevicesFactory() {}

DevicesFactory::~DevicesFactory() {}

bool DevicesFactory::addNewDevice(QString devType, QStringList keyParam, QStringList valueParam, ServiceDevicesAbstract *pDevService) {
    bool res = false;
    QString devId;
    QString devHeader;
    if(deviceMap.isEmpty()) {
        res = true;
    } else {
        QString factoryDevTypeNames;
        for(auto iTypeDev: deviceMap) {
            if(factoryDevTypeNames.isEmpty()) {
                factoryDevTypeNames = (iTypeDev).second->getDevTypeName();
                res = true;
            } else {
                if(factoryDevTypeNames != (iTypeDev).second->getDevTypeName()) {
                    res = false;
                }
            }
        }
    }
    if(!res) {
        return false;
    }

    for(int i=0; i<keyParam.size(); i++) {
        if(keyParam[i] == "id") {
            devId = valueParam[i];
        }
        if(keyParam[i] == "header") {
            devHeader = valueParam[i];
        }
    }
    if(!devId.isEmpty()) {
        if(findDeviceByUnicIdent(devId) == nullptr) {
            if(devHeader.isEmpty()) {
                devHeader = QString("dev_num_%2").arg(deviceMap.size());
            }
            if(devType.toLower() == QString(Progress_tmk24::name).toLower()) { // TODO: need uniqPtr
                deviceMap.push_back(QPair<QString, DeviceAbstract*>(devId, new Progress_tmk24(devId, devHeader, keyParam, valueParam, pDevService)));
            }
            if(devType.toLower() == QString(Nozzle_Revision_0_00_Oct_2018::name).toLower()) { // TODO: need uniqPtr
                deviceMap.push_back(QPair<QString, DeviceAbstract*>(devId, new Nozzle_Revision_0_00_Oct_2018(devId, devHeader)));
            }
            emit deviceUpdateTree(DevicesFactory::Type_Update_Added, 0);
            // TODO: может быть лучше как-то подругому перехватывать указатаель?
            connect(findDeviceByUnicIdent(devId)->second,
                    SIGNAL(eventDeviceUpdateState(DeviceAbstract::E_DeviceEvent,QString,QStringList,QStringList,CommandController::sCommandData)), this,
                    SLOT(deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent,QString,QStringList,QStringList,CommandController::sCommandData)));
        }
    }
}

bool DevicesFactory::removeDevice(QString uniqDevName) {
    bool res = false;
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByUnicIdent(uniqDevName);
    if(pDev != nullptr) {
        deviceMap.erase(pDev);
        res = true;
    }
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return res;
}

bool DevicesFactory::removeDeviceByIndex(int index) {
    bool res = false;
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByIndex(index);
    if(pDev != nullptr) {
        deviceMap.erase(pDev);
        res = true;
    }
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return res;
}

bool DevicesFactory::removeDeviceAll() {
    deviceMap.clear();
    emit deviceUpdateTree(DevicesFactory::Type_Update_Removed, 0);
    return true;
}

int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QString DevicesFactory::getDeviceName(int index) {
    return findDeviceByIndex(index)->second->getDevTypeName();
}

QString DevicesFactory::getDeviceNameWithId(int index) {
    return QString("%1[%2]").arg(findDeviceByIndex(index)->second->getDevTypeName()).arg(findDeviceByIndex(index)->second->getUniqId());
}

QString DevicesFactory::getDeviceHeader(int index) {
    return findDeviceByIndex(index)->second->getDevHeader();
}

void DevicesFactory::setDeviceHeader(int index, QString header) {
    return findDeviceByIndex(index)->second->setDevHeader(header);
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

QPair<QStringList,QStringList> DevicesFactory::getDeviceErrrors(int indexDev) {
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

// сюда приходят все сигналы от девайсов (смена состояние и рез кастомных команд)
void DevicesFactory::deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent devTypeEvent, QString devId, QStringList devKey, QStringList devValue, CommandController::sCommandData command) {
    switch (devTypeEvent) {
    case DeviceAbstract::Type_DeviceEvent_Connected:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceConnectedSignal(findDeviceByUnicIdent(devId)->second->getDevTypeName(), devId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_Disconnected:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceDisconnectedSignal(findDeviceByUnicIdent(devId)->second->getDevTypeName(), devId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_Inited:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceReadyInitSignal(findDeviceByUnicIdent(devId)->second->getDevTypeName(), devId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_ReadyReadProperties:
        //
        // TODO: пересылаем на верх
        // здесь ловим изменение с неинтита на инит и готовность отдать properties
        //
        emit deviceReadyPropertiesSignal(findDeviceByUnicIdent(devId)->second->getDevTypeName(), devId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_CurrentDataUpdated:
        // TODO: пересылаем на верх
        emit deviceReadyCurrentDataSignal(findDeviceByUnicIdent(devId)->second->getDevTypeName(), devId);
        // TODO: отловить реальное изменение статус
        // чтобы не высылать после каждого пакета
        emit deviceUpdateTree(DevicesFactory::Type_Update_ChangeStatus, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_PasswordError:
        // пароль не совпадает
        emit deviceUpdateTree(DevicesFactory::Type_Update_PasswordIncorrect, findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_TypeError:
        // тип не совпадает с заявленным
        emit deviceUpdateTree(DevicesFactory::Type_Update_TypeIncorrect, findDeviceIndex(devId));
        // удаляем устройство
        removeDeviceByIndex(findDeviceIndex(devId));
        break;
    case DeviceAbstract::Type_DeviceEvent_LogMessage:
        emit deviceReadyLog(findDeviceIndex(devId), devValue); // TODO: mayby rewrite key-value?
        break;
    case DeviceAbstract::Type_DeviceEvent_ExectCustomCommand: {
        int findDevIndex = findDeviceIndex(devId);
        emit deviceReadyCustomCommand(findDevIndex, findDeviceByUnicIdent(devId)->second->getDevTypeName(), devKey, devValue, command);
    }
        break;
    default: break;
    }
}

QList<int> DevicesFactory::getDeviceChartByIndex(int index) {
    if(deviceMap.empty()) {return QList<int>();}
    return findDeviceByIndex(index)->second->getChart();
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
