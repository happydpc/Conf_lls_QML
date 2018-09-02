#include "devicesFactory.h"
#include <QDebug>

DevicesFactory::DevicesFactory() {
    this->commandController = new CommandController();
    this->devShedullerTimer = new QTimer();
    connect(this->devShedullerTimer, SIGNAL(timeout()), this, SLOT(devShedullerSlot()));
    this->devShedullerTimer->start(devShedullerControlInterval);
    this->deviceMap.clear();
}

DevicesFactory::~DevicesFactory() {
}

bool DevicesFactory::addNewDevice(DeviceAbstract::E_DeviceType type, QString uniqDevName, int uniqDevId, QStringList parameters) {
    this->deviceMap.push_back(QPair<QString, Device*>(
                                  uniqDevName, // todo: unique memory
                                  new Device(type, uniqDevName, uniqDevId, parameters)));
    return (bool)deviceMap.size();
}

bool DevicesFactory::removeDevice(DeviceAbstract::E_DeviceType type, QString uniqDevName, QStringList parameters) {
    bool res = false;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(((*it).second->getUniqIdentName() == uniqDevName)
                && ((*it).second->getType() == type)) {
            deviceMap.erase(it);
            res = true;
        }
    }
    return res;
}

int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QStringList DevicesFactory::getDeviceHeaderByIndex(int index) {
    QStringList ret;
    int count = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(index == count) {
            ret << QString("%1 [%2]")
                   .arg(getCaptionToTypeDevice(((*it).second->getType())))
                   .arg((*it).second->getUniqIdentId());
            break;
        }
        count++;
    }
    return ret;
}

QString DevicesFactory::getDeviceTypeByIndex(int index) {
    QString ret;
    int count = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(index == count) {
            ret = getCaptionToTypeDevice(((*it).second->getType()));
            break;
        }
        count++;
    }
    return ret;
}


QStringList DevicesFactory::getDeviceCurrentPropertyByIndex(int index) {
    QStringList ret;
    int count = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(index == count) {
            ret << (*it).second->getCurrentData();
            break;
        }
        count++;
    }
    return ret;
}

QStringList DevicesFactory::getDeviceInfo(int indexDev) {
    QStringList res;
    QStringList tParam;
    int curIndex = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(curIndex == indexDev) {
            res = (*it).second->getParameters();
        }
    }
    return res;
}

// TODO: crash if dev name undefined!!!
QStringList DevicesFactory::getAvailableDeviceTypes() {
    QStringList strList;
    Device *device = new Device(DeviceAbstract::Type_Progress_Tmk24, "", 0, strList);
    strList = device->getDeviceAvaibleTypes();
    delete  device;
    return strList;
}

bool DevicesFactory::addCommandDevice(CommandController::sCommandData commandData) {
    return commandController->addCommandToStack(commandData);
}

void DevicesFactory::devShedullerSlot() {
    bool sendRes = false;
    CommandController::sCommandData tcommandDev;
    if(!deviceMap.empty()) {
        //-- if command queue is not empty
        if(!commandController->commandsIsEmpty()) {
            //-- give command struct for current device
            commandController->getCommandFirstCommandFromStack(tcommandDev);
            // search same dev from deviceMap
            for(auto dev: deviceMap) {
                if(dev.second->getUniqIdentName() == tcommandDev.deviceIdent) {
                    //-- stop sheduller while not reply or not timeout
                    devShedullerTimer->stop();
                    //-- when we send data
                    sendRes = writeCommandToDev(dev.second, tcommandDev);
                    lastRequestedDevice = dev.second;
                    if(sendRes) {
                        QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, [&] {
                            emit readReplyData();
                        });
                    }
                    break;
                }
            }
        } else {
            Device *oldestDev = getDevOldest();
            if(oldestDev != nullptr) {
                int idleCommandSize = oldestDev->getCommandListToIdlePoll().size();
                for(auto idleCounter=0; idleCounter<idleCommandSize; idleCounter++) {
                    tcommandDev = oldestDev->getCommandListToIdlePoll().at(idleCounter);
                    commandController->addCommandToStack(tcommandDev);
                }
            }
        }
    }
}

void DevicesFactory::placeReplyDataFromInterface(QByteArray data) {
    bool res = false;
    for(auto dev: deviceMap) {
        if(dev.second->getUniqIdentName() == lastRequestedDevice->getUniqIdentName()) {
            res = true;
            qDebug() << "placeReplyDataOfCommand -Ok len=" << data.length();
            dev.second->placeReplyDataOfCommand(data);
        }
    }
    if(!res) {
        qDebug() << "placeReplyDataFromInterface -same Device not found!";
    }
    //-- start sheduller after reply
    devShedullerTimer->start(devShedullerControlInterval);
}

Device* DevicesFactory::getDevOldest() {
    time_t oldestTime = 0;
    Device *oldestDevPoint = nullptr;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        oldestDevPoint = (*it).second;
        if(oldestDevPoint->getLastDataReqDev() < oldestTime) {
            oldestTime = oldestDevPoint->getLastDataReqDev();
        }
    }
    return oldestDevPoint;
}

bool DevicesFactory::writeCommandToDev(Device *pDev, CommandController::sCommandData commandData) {
    bool res = false;
    if(pDev != nullptr) {
        res = pDev->makeDataToCommand(commandData);
        if(res) {
            qDebug() << "DeviceFactory: writeCommandToDev -Ok " << commandData.commandOptionData;
            emit writeData(pDev->getType(), commandData.commandOptionData);
        } else {
            qDebug() << "DeviceFactory: writeCommandToDev res-FALSE";
        }
    } else {
        qDebug() << "deviceFactory: writeCommandToDev(dev==nullprt!!)";
    }
    return res;
}

QString DevicesFactory::getCaptionToTypeDevice(DeviceAbstract::E_DeviceType type) {
    QStringList tStrList;
    Device *tDevice = new Device(type, "", 0, tStrList);
    QString res = tDevice->getCaptionToTypeDevice(type);
    delete tDevice;
    return res;
}

DeviceAbstract::E_DeviceType DevicesFactory::getDeviceTypeFromTypeCaption(QString typeDevText) {
    DeviceAbstract::E_DeviceType res;
    QStringList tStrList;
    Device *tDevice = new Device(res, "", 0, tStrList);
    res = tDevice->getDeviceTypeFromTypeCaption(typeDevText);
    delete tDevice;
    return  res;
}
