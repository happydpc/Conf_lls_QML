#include "Progress_tmk24Service.h"

Progress_tmk24Service::Progress_tmk24Service(QString owDeviceName) {
    this->ownDeviceName = owDeviceName;
}

bool Progress_tmk24Service::addDevice(QString devTypeName, QString devId, QString devSn) {
    bool isDuplicate = false;
    bool res = false;
    // поиск дубликата id
    for(auto it: devList) {
        if(it->first.devId == devId) {
            isDuplicate = true;
            break;
        }
    }
    if(!isDuplicate) {
        sDevIdentBlock idBlock;
        idBlock.devTypeName = devTypeName;
        idBlock.devId = devId;
        idBlock.devSn = devSn;
        idBlock.isWhitedResult = 0;
        idBlock.writeIsNormal = 0;
        idBlock.currData.isValid = false;
        devList.push_back(new QPair<sDevIdentBlock, QList<sDevValues>*>(idBlock, new QList<sDevValues>()));
        res = true;
    } else {
        lastError = "Не удалось добавить т.к. такой номер уже есть в списке!";
    }
    return res;
}

void Progress_tmk24Service::removeDevice(QString devTypeName, QString devId) {
    for(auto it: devList) {
        if(it->first.devId == devId) {
            if(it->first.devTypeName == devTypeName) {
                devList.removeOne(it);
            }
        }
    }
}

int Progress_tmk24Service::getDeviceCount() {
    return devList.size();
}

QStringList Progress_tmk24Service::getDeviceProperty(int index) {
    QStringList res;
    res << devList.at(index)->first.devTypeName;
    res << devList.at(index)->first.devId;
    res << devList.at(index)->first.devSn;
    return res;
}

QList<QString> Progress_tmk24Service::requestGetTableFromAllDevice() {
    QList<QString>list;
    if(operation == OPERATION_IDLE){
        for(auto it: devList) {
            list.push_back(it->first.devId);
            it->first.isWhitedResult = true;
            operation = OPERATION_WHITE_GET;
        }
    }
    return list;
}


void Progress_tmk24Service::placeTableFromDevice(QString deviceIdentName, QStringList keys, QStringList values) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            it->second->clear();
            sDevValues tDevValues;
            for(int i=0; i<keys.size(); i++) {
                if(keys[i] == "y") {
                    tDevValues.valueFuelLevel = values[i].toUInt();
                } else if (keys[i] == "x") {
                    tDevValues.valueLiters = values[i].toUInt();
                    it->second->push_back(tDevValues);
                }
            }
            it->first.isWhitedResult = false;
        }
    }
    if(readTableAllDeviceIsReady()) {
        operation = OPERATION_IDLE;
    }
}

bool Progress_tmk24Service::readTableAllDeviceIsReady() {
    bool isAllReplyReady = true;
    for(auto it: devList) {
        if(it->first.isWhitedResult == true) {
            isAllReplyReady = false;
        }
    }
    return isAllReplyReady;
}

QStringList Progress_tmk24Service::getTableAtDevice(int index) {
    QStringList res;
    int devsLen = devList.at(index)->second->size();
    for(int i=0; i<devsLen; i++ ) {
        res << QString::number(devList.at(index)->second->at(i).valueLiters);
        res << QString::number(devList.at(index)->second->at(i).valueFuelLevel);
    }
    return res;
}

QPair<QStringList,QStringList> Progress_tmk24Service::getTableAtDeviceToPair(QString uniqDevNameId) {
    QPair<QStringList,QStringList> res;
    for(auto it: devList) {
        if(it->first.devId == uniqDevNameId) {
            int devsLen = it->second->size();
            for(int i=0; i<devsLen; i++ ) {
                res.first << QString::number(it->second->at(i).valueLiters);
                res.second << QString::number(it->second->at(i).valueFuelLevel);
            }
        }
    }
    return res;
}

// TODO: !!!!!
void Progress_tmk24Service::placeCurrenDataFromDevice(QString deviceIdentName, QPair<QStringList,QStringList>data) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            if(!data.first.isEmpty()) {
                if(data.first.indexOf("fuelLevel") >= 0) {
                    it->first.currData.fuelLevel = data.second.at(data.first.indexOf("fuelLevel")).toUInt();
                }
                if(data.first.indexOf("cnt") >= 0) {
                    it->first.currData.cntValue = data.second.at(data.first.indexOf("cnt")).toUInt();
                }
                it->first.currData.liters = 0; // TODO: liters  не известны и заносятся юзером
                it->first.currData.isValid = true;
            }
        }
    }
}

void Progress_tmk24Service::placeCurrentChartDataFromDevice(QString deviceIdentName, QList<int> currentChartData) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            if(!currentChartData.empty()) {
                it->first.chartData = currentChartData;
            }
        }
    }
}

QStringList Progress_tmk24Service::getCurrentDataDevice(int index) {
    QStringList res;
    if(devList.at(index)->first.currData.isValid) {
        res << QString::number(devList.at(index)->first.currData.fuelLevel);
        res << QString::number(devList.at(index)->first.currData.liters);
        res << QString::number(devList.at(index)->first.currData.cntValue);
    } else {
        res << "0";
        res << "0";
    }
    return res;
}

QList<int> Progress_tmk24Service::getCurrentChartDataDevice(int index) {
    QList<int> res;
    if(devList.at(index)->first.currData.isValid) {
        res = devList.at(index)->first.chartData;
    }
    return res;
}


int Progress_tmk24Service::getMaxCountStep() {
    int res = 0;
    for(auto itDev: devList) {
        if(res < itDev->second->size()) {
            res = itDev->second->size();
        }
    }
    return res;
}

void Progress_tmk24Service::placeTableFromFrontEnd(QString deviceIdentName, QStringList valueLiters, QStringList valueFuelLevel) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            it->second->clear();
            sDevValues tDevValues;
            for(int i=0; i<valueLiters.size(); i++) {
                tDevValues.valueLiters = valueLiters.at(i).toUInt();
                tDevValues.valueFuelLevel = valueFuelLevel.at(i).toUInt();
                it->second->push_back(tDevValues);
            }
            it->first.isWhitedResult = false;
        }
    }
}

void Progress_tmk24Service::placeAckReplyOfWriteTableFromDevice(QString deviceIdentName, bool writeIsNormal) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            it->first.isWhitedResult = false;
            it->first.writeIsNormal = writeIsNormal;
        }
    }
    if(readTableAllDeviceIsReady()) {
        operation = OPERATION_IDLE;
    }
}

bool Progress_tmk24Service::getAckStatusDeviceAffterWriteTable(QString deviceIdentName) {
    bool res = false;
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            res = it->first.writeIsNormal;
        }
    }
    return res;
}

QList<QString> Progress_tmk24Service::requestWriteTableToAllDevice() {
    QList<QString>list;
    if(operation == OPERATION_IDLE) {
        for(auto it: devList) {
            list.push_back(it->first.devId);
            it->first.isWhitedResult = true;
        }
        operation = OPERATION_WHITE_WRITE;
    }
    return list;
}
