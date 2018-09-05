#include "devicesFactory.h"
#include <QDebug>

DevicesFactory::DevicesFactory() {
    this->commandController = new CommandController();
    this->devShedullerTimer = new QTimer();
    this->devShedullerTimer->start(devShedullerControlInterval);

    connect(this->devShedullerTimer, SIGNAL(timeout()), this, SLOT(devShedullerSlot()));
}

DevicesFactory::~DevicesFactory() {}

bool DevicesFactory::addNewDevice(E_DeviceType type, QString uniqDevName, QStringList parameters) {
    if(type == Type_Progress_Tmk24) {
        this->deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Progress_tmk24(uniqDevName)));
    } else if(type == Type_Progress_Tmk13) {
        this->deviceMap.push_back(QPair<QString, DeviceAbstract*>(uniqDevName, new Progress_tmk13(uniqDevName)));
    } else {
        throw QString("undefined class");
    }
    return (bool)deviceMap.size();
}

bool DevicesFactory::removeDevice(QString uniqDevName) {
    QPair<QString,DeviceAbstract*>* pDev = findDeviceByUnicIdent(uniqDevName);
    if(pDev != nullptr) {
        deviceMap.erase(pDev);
        return true;
    }
    return false;
}

int DevicesFactory::getDeviceCount() {
    return deviceMap.size();
}

QString DevicesFactory::getDeviceName(int index) {
    return findDeviceByIndex(index)->second->getName();
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

QStringList DevicesFactory::getDeviceHeaderByIndex(int index) {
    if(deviceMap.empty()) {return QStringList("");}
    return QStringList(QString("%1 [%2]")
                       .arg(getDeviceName(index))
                       .arg(getDeviceIdTextByIndex(index)));
}

QList<int> DevicesFactory::getDeviceChartByIndex(int index) {
    //    if(deviceMap.empty()) {return QList<int>();}
    //    return findDeviceByIndex(index).second->getDeviceCurrentChart();
}

QList<QString> DevicesFactory::getDeviceCurrentDataByIndex(int index) {
    //    if(deviceMap.empty()) {return QList<QString>();}
    //    return findDeviceByIndex(index).second->getDeviceCurrentOtherData();
}

//QString DevicesFactory::getDeviceTypeTextByIndex(int index) {
//    if(deviceMap.empty()) {return QString();}
//    return getCaptionToTypeDevice((findDeviceByIndex(index).second->getType()));
//}

QStringList DevicesFactory::getDeviceCurrentPropertyByIndex(int index) {
    if(deviceMap.empty()) {return QStringList("");}
    return findDeviceByIndex(index)->second->getPropertyData();
}

QString DevicesFactory::getDeviceIdTextByIndex(int index) {
    if(deviceMap.empty()) {return QString();}
    return findDeviceByIndex(index)->first;
}

QStringList DevicesFactory::getDeviceProperty(int indexDev) {
    //    if(deviceMap.empty()) {return QStringList("");}
    //    return findDeviceByIndex(indexDev).second->getParameters();
}

QStringList DevicesFactory::getAvailableDeviceTypes() {
    QStringList types;
    types << QString::fromUtf8(Progress_tmk13::name, strlen(Progress_tmk13::name));
    types << QString::fromUtf8(Progress_tmk24::name, strlen(Progress_tmk24::name));
    return types;
}

bool DevicesFactory::addCommandDevice(CommandController::sCommandData commandData) {
    return commandController->addCommandToStack(commandData);
}

void DevicesFactory::devShedullerSlot() {
    //    bool sendRes = false;
    //    CommandController::sCommandData tcommandDev;
    //    if(!deviceMap.empty()) {
    //        //-- if command queue is not empty
    //        if(!commandController->commandsIsEmpty()) {
    //            //-- give command struct for current device
    //            commandController->getCommandFirstCommandFromStack(tcommandDev);
    //            // search same dev from deviceMap
    //            for(auto dev: deviceMap) {
    //                if(dev.second->getUniqIdent() == tcommandDev.deviceIdent) {
    //                    //-- stop sheduller while not reply or not timeout
    //                    devShedullerTimer->stop();
    //                    //-- when we send data
    //                    sendRes = writeCommandToDev(dev.second, tcommandDev);
    //                    lastRequestedDevice = dev.second;
    //                    if(sendRes) {
    //                        QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, [&] {
    //                            emit readReplyData();
    //                        });
    //                    }
    //                    break;
    //                }
    //            }
    //        } else {
    //            Device *oldestDev = getDevOldest();
    //            if(oldestDev != nullptr) {
    //                int idleCommandSize = oldestDev->getCommandListToIdlePoll().size();
    //                for(auto idleCounter=0; idleCounter<idleCommandSize; idleCounter++) {
    //                    tcommandDev = oldestDev->getCommandListToIdlePoll().at(idleCounter);
    //                    commandController->addCommandToStack(tcommandDev);
    //                }
    //            }
    //        }
    //    }
}

//
// TODO: BAD LOOP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

void DevicesFactory::placeReplyDataFromInterface(QByteArray data) {
    //    bool res = false;
    //    for(auto dev: deviceMap) {
    //        if(dev.second->getUniqIdent() == lastRequestedDevice->getUniqIdent()) {
    //            res = true;
    //            qDebug() << "placeReplyDataOfCommand -Ok len=" << data.length();
    //            dev.second->placeReplyDataOfCommand(data);
    //        }
    //    }
    //    if(!res) {
    //        qDebug() << "placeReplyDataFromInterface -same Device not found!";
    //    }
    //    //-- start sheduller after reply
    //    devShedullerTimer->start(devShedullerControlInterval);
}

//Device* DevicesFactory::getDevOldest() {
//    time_t oldestTime = 0;
//    Device *oldestDevPoint = nullptr;
//    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
//        oldestDevPoint = (*it).second;
//        if(oldestDevPoint->getLastDataReqDev() < oldestTime) {
//            oldestTime = oldestDevPoint->getLastDataReqDev();
//        }
//    }
//    return oldestDevPoint;
//}

//bool DevicesFactory::writeCommandToDev(Device *pDev, CommandController::sCommandData commandData) {
//    bool res = false;
//    if(pDev != nullptr) {
//        res = pDev->makeDataToCommand(commandData);
//        if(res) {
//            qDebug() << "DeviceFactory: writeCommandToDev -Ok " << commandData.commandOptionData;
//            emit writeData(pDev->getType(), commandData.commandOptionData);
//        } else {
//            qDebug() << "DeviceFactory: writeCommandToDev res-FALSE";
//        }
//    } else {
//        qDebug() << "deviceFactory: writeCommandToDev(dev==nullprt!!)";
//    }
//    return res;
//}

//QString DevicesFactory::getCaptionToTypeDevice(DevicesFactory::E_DeviceType type) {
//    switch(type) {
//    case Type_Progress_Tmk13: break;
//    case Type_Progress_Tmk24: break;
//    case Type_Undefined: break;
//    }
//    QString res = tDevice->getCaptionToTypeDevice(type);
//    delete tDevice;
//    return res;
//}

//DevicesFactory::E_DeviceType DevicesFactory::getDeviceTypeFromTypeCaption(QString typeDevText) {
//    DeviceAbstract::E_DeviceType res;
//    Device *tDevice = new Device(res, "");
//    res = tDevice->getDeviceTypeFromTypeCaption(typeDevText);
//    delete tDevice;
//    return  res;
//}

//QString Device::getCaptionToTypeDevice(DeviceAbstract::E_DeviceType type) {
//    QString res;
//    if(!deviceAvailableTypesList.empty()) {
//        auto it = deviceAvailableTypesList.begin();
//        while(it!=deviceAvailableTypesList.end()) {
//            if(type == (*it).first) {
//                return (*it).second;
//            }
//            it++;
//        }
//    }
//    return res;
//}

//DeviceAbstract::E_DeviceType Device::getDeviceTypeFromTypeCaption(QString typeDevText) {
//    DeviceAbstract::E_DeviceType retType = Type_Progress_default;
//    if(!deviceAvailableTypesList.empty()) {
//        auto it = deviceAvailableTypesList.begin();
//        while(it!=deviceAvailableTypesList.end()) {
//            if(typeDevText == (*it).second) {
//                return (*it).first;
//            }
//            it++;
//        }
//    }
//    return retType;
//}



void DevicesFactory::setDeviceAsNotReadyByIndex(int index) {

}

//DeviceAbstract::E_DeviceType DevicesFactory::getDeviceTypebyIndex(int indexDev) {
//    if(deviceMap.empty()) {return DeviceAbstract::Type_Undefined;}
//    return findDeviceByIndex(indexDev).second->getType();
//}
