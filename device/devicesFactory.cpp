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

bool DevicesFactory::addNewDevice(DeviceAbstract::E_DeviceType type, QString uniqDevName, QStringList parameters) {
    this->deviceMap.push_back(QPair<QString, Device*>(uniqDevName, new Device(type, uniqDevName)));
    return (bool)deviceMap.size();
}

bool DevicesFactory::removeDevice(DeviceAbstract::E_DeviceType type, QString uniqDevName) {
    bool res = false;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(((*it).second->getUniqIdent() == uniqDevName)
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
    if(deviceMap.empty()) {return QStringList("");}
    return QStringList(QString("%1 [%2]")
                       .arg(getCaptionToTypeDevice((findDeviceByIndex(index).second->getType())))
                       .arg(findDeviceByIndex(index).second->getUniqIdent()));
}

QList<int> DevicesFactory::getDeviceChartByIndex(int index) {
    if(deviceMap.empty()) {return QList<int>();}
    return findDeviceByIndex(index).second->getDeviceCurrentChart();
}

QList<QString> DevicesFactory::getDeviceCurrentDataByIndex(int index) {
    if(deviceMap.empty()) {return QList<QString>();}
    return findDeviceByIndex(index).second->getDeviceCurrentOtherData();
}

QString DevicesFactory::getDeviceTypeTextByIndex(int index) {
    if(deviceMap.empty()) {return QString();}
    return getCaptionToTypeDevice((findDeviceByIndex(index).second->getType()));
}

QStringList DevicesFactory::getDeviceCurrentPropertyByIndex(int index) {
    if(deviceMap.empty()) {return QStringList("");}
    return findDeviceByIndex(index).second->getPropertyData();
}

QString DevicesFactory::getDeviceIdTextByIndex(int index) {
    if(deviceMap.empty()) {return QString();}
    return findDeviceByIndex(index).second->getUniqIdent();
}

QStringList DevicesFactory::getDeviceProperty(int indexDev) {
    if(deviceMap.empty()) {return QStringList("");}
    return findDeviceByIndex(indexDev).second->getParameters();
}

// TODO: crash if dev name undefined!!!
QStringList DevicesFactory::getAvailableDeviceTypes() {
    Device *device = new Device(DeviceAbstract::Type_Progress_Tmk24, "");
    QStringList strList = device->getDeviceAvaibleTypes();
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
                if(dev.second->getUniqIdent() == tcommandDev.deviceIdent) {
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

QPair<QString,Device*> DevicesFactory::findDeviceByIndex(int index) {
    int counter=0;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        if(counter == index) {
            return (*it);
        }
    }
    return QPair<QString,Device*>();
}

void DevicesFactory::placeReplyDataFromInterface(QByteArray data) {
    bool res = false;
    for(auto dev: deviceMap) {
        if(dev.second->getUniqIdent() == lastRequestedDevice->getUniqIdent()) {
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
    Device *tDevice = new Device(type, "");
    QString res = tDevice->getCaptionToTypeDevice(type);
    delete tDevice;
    return res;
}

DeviceAbstract::E_DeviceType DevicesFactory::getDeviceTypeFromTypeCaption(QString typeDevText) {
    DeviceAbstract::E_DeviceType res;
    Device *tDevice = new Device(res, "");
    res = tDevice->getDeviceTypeFromTypeCaption(typeDevText);
    delete tDevice;
    return  res;
}

void DevicesFactory::setDeviceAsNotReadyByIndex(int index) {

}

DeviceAbstract::E_DeviceType DevicesFactory::getDeviceTypebyIndex(int indexDev) {
    if(deviceMap.empty()) {return DeviceAbstract::Type_Undefined;}
    return findDeviceByIndex(indexDev).second->getType();
}
