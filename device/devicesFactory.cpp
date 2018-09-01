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
    this->deviceMap.insert(uniqDevName, new Device(type, uniqDevName, uniqDevId, parameters)); // todo: unique memory
    return (bool)deviceMap.size();
}

bool DevicesFactory::removeDevice(DeviceAbstract::E_DeviceType type, QString uniqDevName, QStringList parameters) {
    bool res = false;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(((*it)->getUniqIdentName() == uniqDevName) && ((*it)->getType() == type)) {
            deviceMap.erase(it);
            res = true;
        }
    }
    return res;
}

int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QStringList DevicesFactory::getDeviceInfo(int indexDev) {
    QStringList res;
    QStringList tParam;
    int curIndex = 0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(curIndex == indexDev) {
            res = (*it)->getParameters();
        }
    }
    return res;
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
                if(dev->getUniqIdentName() == tcommandDev.deviceIdent) {
                    //-- stop sheduller while not reply or not timeout
                    devShedullerTimer->stop();
                    //-- when we send data
                    sendRes = writeCommandToDev(dev, tcommandDev);
                    lastRequestedDevice = dev;
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
        if(dev->getUniqIdentName() == lastRequestedDevice->getUniqIdentName()) {
            res = true;
            qDebug() << "placeReplyDataOfCommand -Ok len=" << data.length();
            dev->placeReplyDataOfCommand(data);
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
        oldestDevPoint = (*it);
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
            emit writeData(commandData.commandOptionData);
        } else {
            qDebug() << "DeviceFactory: writeCommandToDev res-FALSE";
        }
    } else {
        qDebug() << "deviceFactory: writeCommandToDev(dev==nullprt!!)";
    }
    return res;
}
