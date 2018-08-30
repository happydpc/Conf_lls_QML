#include "devicesFactory.h"
#include <QDebug>

DevicesFactory::DevicesFactory() {
    this->devShedullerTimer = new QTimer();
    connect(devShedullerTimer, SIGNAL(timeout()), this, SLOT(devShedullerSlot()));
    this->devShedullerTimer->start(devShedullerControlInterval);
}

bool DevicesFactory::addNewDevice(DeviceAbstract::E_DeviceType type, QStringList parameters) {
    device.insert(type, new Device(type, parameters)); // todo: unique memory
    return (bool)device.size();
}

bool DevicesFactory::removeDevice(DeviceAbstract::E_DeviceType type, QStringList parameters) {
    bool res = false;
    Device tDev(type, parameters);
    for(auto it = device.begin(); it != device.end(); it++) {
        device.find(type, &tDev);
        if(tDev.getParameters() == parameters) {
            device.erase(it);
            res = true;
        }
    }
    return res;
}

int DevicesFactory::getDeviceCount() {
    return device.size();
}

QStringList DevicesFactory::getDeviceInfo(int indexDev) {
    QStringList res;
    QStringList tParam;
    int curIndex = 0;
    Device tDev(DeviceAbstract::Type_Progress_Tmk324, tParam);
    for(auto it = device.begin(); it != device.end(); it++) {
        if(curIndex == indexDev) {
            res = tDev.getParameters();
        }
    }
    return res;
}

bool sendCommandDev(DeviceAbstract::E_DeviceType,
                    QStringList DevIdentParam,
                    int typeCommand,
                    QByteArray arg) {
    bool res = false;
    return res;
}

void DevicesFactory::devShedullerSlot() {
    bool sendRes = false;

    if(!device.empty()) {
        if(!commandController->isEmpty()) {
            if(sendRes) {
                QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, this, [&] {
                    tve =0;
                });
            }
        } else {
            Device *oldestDev = getDevOldest();
            if(oldestDev != nullptr) {
                QVector<int>tvectCommand = oldestDev->getCommandListToIdlePoll();
                if(!tvectCommand.empty()) {
                    for(auto commandIt = tvectCommand.begin(); it<tvectCommand.end(); it++) {
                        sendRes = sendCommandDev(oldestDev, commandIt, QByteArray());
                        if(sendRes) {
                            QTimer::singleShot(delayAfterSendCommandMs, Qt::PreciseTimer, this, [] {
                                QByteArray replyBuffArray;
                                emit readReplyData(replyBuffArray);
                                oldestDev->placeReplyDataOfCommand(replyBuffArray, commandIt);
                            });
                        }
                    }
                }
            }
        }
    }
}

Device* DevicesFactory::getDevOldest() {
    time_t oldestTime = 0;
    Device *oldestDevPoint = nullptr;
    for(auto it = device.begin(); it != device.end(); it++) {
        oldestDevPoint = (*it);
        if(oldestDevPoint->getLastDataReqDev() < oldestTime) {
            oldestTime = oldestDevPoint->getLastDataReqDev();
        }
    }
    return oldestDevPoint;
}

bool DevicesFactory::sendCommandDev(Device *pDev, int commandType, QByteArray commandArg) {
    bool res = false;
    QByteArray sendBuf;
    res = pDev->makeDataToCommand(sendBuf, commandType, commandArg);
    if(res) {
        emit writeData(sendBuf);
    } else {
        qDebug() << "DeviceFactory: sendCommandDev res-FALSE";
    }
    return res;
}
