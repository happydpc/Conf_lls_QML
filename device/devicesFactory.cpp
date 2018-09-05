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
    QList<CommandController::sCommandData>commandList = findDeviceByIndex(index)->second->getCommandListToInit();
    for(auto command :commandList) {
        commandController->addCommandToStack(command);
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

//QString DevicesFactory::getDeviceTypeTextByIndex(int index) {
//    if(deviceMap.empty()) {return QString();}
//    return getCaptionToTypeDevice((findDeviceByIndex(index).second->getType()));
//}

QStringList DevicesFactory::getDevicePropertyByIndex(int index) {
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

DeviceAbstract::E_State DevicesFactory::getDevStateByIndex(int index) {
    return findDeviceByIndex(index)->second->getState();
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
    CommandController::sCommandData command;
    if(!deviceMap.empty()) {
        //-- if command queue is not empty
        if(commandController->getCommandFirstCommandFromStack(command)) {
            //-- give command struct for current device
            // search same dev from deviceMap
            for(auto dev: deviceMap) {
                if(dev.second->getUniqIdent() == command.deviceIdent) {
                    //-- make packet request
                    if(dev.second->makeDataToCommand(command)) {
                        qDebug() << "DeviceFactory: writeCommandToDev -Ok " << command.commandOptionData;
                        emit writeData(command.commandOptionData);

                        devLastRequested = dev.second;
                        //-- stop sheduller while not reply or not timeout
                        devShedullerTimer->stop();
                        QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, [&] {
                            emit readReplyData();
                        });
                    }
                }
            }
        } else { //-- command list is empty - add idle command list
            DeviceAbstract *oldestDev = getDevOldest();
            if(oldestDev != nullptr) {
                auto size = oldestDev->getCommandListToIdlePoll().size();
                for(auto i=0; i<size; i++) {
                    command = oldestDev->getCommandListToIdlePoll().at(i);
                    commandController->addCommandToStack(command);
                }
            }
        }
    }
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
    for(auto dev: deviceMap) {
        if(dev.second->getUniqIdent() == devLastRequested->getUniqIdent()) {
            qDebug() << "placeDataReplyToCommand -len=" << data.length();
            dev.second->placeDataReplyToCommand(data);
        }
    }
    //-- start sheduller after reply
    devShedullerTimer->start(devShedullerControlInterval);
}

DeviceAbstract* DevicesFactory::getDevOldest() {
    time_t oldestTime = 0;
    DeviceAbstract *oldestDevPoint = nullptr;
    for(auto it = deviceMap.begin(); it != deviceMap.end(); it++) {
        oldestDevPoint = (*it).second;
        if(oldestDevPoint->getLastDataReqDev() < oldestTime) {
            oldestTime = oldestDevPoint->getLastDataReqDev();
        }
    }
    return oldestDevPoint;
}

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
