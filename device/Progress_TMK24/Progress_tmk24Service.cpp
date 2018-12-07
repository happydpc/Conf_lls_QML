#include "Progress_tmk24Service.h"

Progress_tmk24Service::Progress_tmk24Service(std::string ownDeviceName) {
    this->ownDeviceName = ownDeviceName;
}

Progress_tmk24Service::~Progress_tmk24Service() {
}

bool Progress_tmk24Service::addDevice(std::string devTypeName, std::string devId, std::string devSn) {
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
        // TODO: need uniqPtr
        devList.push_back(new std::pair<sDevIdentBlock, QList<sDevValues>*>(idBlock, new QList<sDevValues>()));
        res = true;
    } else {
        lastError = "Не удалось добавить т.к. такой номер уже есть в списке!";
    }
    return res;
}

void Progress_tmk24Service::removeDevice(std::string devTypeName, std::string devId) {
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

std::list<std::string> Progress_tmk24Service::getDeviceProperty(int index) {
    std::list<std::string> res;
    res.push_back(devList.at(index)->first.devTypeName);
    res.push_back(devList.at(index)->first.devId);
    res.push_back(devList.at(index)->first.devSn);
    return res;
}

QList<std::string> Progress_tmk24Service::requestGetTableFromAllDevice() {
    QList<std::string>list;
    if(operation == OPERATION_IDLE){
        for(auto it: devList) {
            list.push_back(it->first.devId);
            it->first.isWhitedResult = true;
            operation = OPERATION_WHITE_GET;
        }
    }
    return list;
}


void Progress_tmk24Service::placeTableFromDevice(std::string deviceIdentName, std::list<std::string> keys, std::list<std::string> values) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            it->second->clear();
            sDevValues tDevValues;
            auto valueIter = values.begin();
            for(auto itemKey:keys) {
                if(itemKey == "y") {
                    tDevValues.valueFuelLevel = std::stoi(*valueIter);
                } else if (itemKey == "x") {
                    tDevValues.valueLiters = std::stoi(*valueIter);
                    it->second->push_back(tDevValues);
                }
                valueIter++;
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

std::list<std::string> Progress_tmk24Service::getTableAtDevice(int index) {
    std::list<std::string> res;
    int devsLen = devList.at(index)->second->size();
    for(int i=0; i<devsLen; i++ ) {
        res.push_back(std::to_string(devList.at(index)->second->at(i).valueLiters));
        res.push_back(std::to_string(devList.at(index)->second->at(i).valueFuelLevel));
    }
    return res;
}

std::pair<std::list<std::string>,std::list<std::string>> Progress_tmk24Service::getTableAtDeviceToPair(std::string uniqDevNameId) {
    std::pair<std::list<std::string>,std::list<std::string>> res;
    for(auto it: devList) {
        if(it->first.devId == uniqDevNameId) {
            int devsLen = it->second->size();
            for(int i=0; i<devsLen; i++ ) {
                res.first.push_back(std::to_string(it->second->at(i).valueLiters));
                res.second.push_back(std::to_string(it->second->at(i).valueFuelLevel));
            }
        }
    }
    return res;
}

// TODO: !!!!!
void Progress_tmk24Service::placeCurrenDataFromDevice(std::string deviceIdentName, std::pair<std::list<std::string>,std::list<std::string>>data) {
//    for(auto it: devList) {
//        if(it->first.devId == deviceIdentName) {
//            if(!data.first.empty()) {
//                if(data.first.indexOf("fuelLevel") >= 0) {
//                    it->first.currData.fuelLevel = data.second.at(data.first.indexOf("fuelLevel")).toUInt();
//                }
//                if(data.first.indexOf("cnt") >= 0) {
//                    it->first.currData.cntValue = data.second.at(data.first.indexOf("cnt")).toUInt();
//                }
//                it->first.currData.liters = 0; // TODO: liters  не известны и заносятся юзером
//                it->first.currData.isValid = true;
//            }
//        }
//    }
}

void Progress_tmk24Service::placeCurrentChartDataFromDevice(std::string deviceIdentName, QList<int> currentChartData) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            if(!currentChartData.empty()) {
                it->first.chartData = currentChartData;
            }
        }
    }
}

std::list<std::string> Progress_tmk24Service::getCurrentDataDevice(int index) {
    std::list<std::string> res;
//    if(devList.at(index)->first.currData.isValid) {
//        res << std::to_string(devList.at(index)->first.currData.fuelLevel);
//        res << std::to_string(devList.at(index)->first.currData.liters);
//        res << std::to_string(devList.at(index)->first.currData.cntValue);
//    } else {
//        res << "0";
//        res << "0";
//    }
//    return res;
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

void Progress_tmk24Service::placeTableFromFrontEnd(std::string deviceIdentName, std::list<std::string> valueLiters, std::list<std::string> valueFuelLevel) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            it->second->clear();
            auto litersItem = valueLiters.begin();
            auto fuelItem = valueLiters.begin();
            while(litersItem != valueLiters.end()) {
                sDevValues tDevValues;
                tDevValues.valueLiters = std::stoi(*litersItem);
                tDevValues.valueFuelLevel = std::stoi(*fuelItem);
                litersItem++;
                fuelItem++;
                it->second->push_back(tDevValues);
            }
            it->first.isWhitedResult = false;
        }
    }
}

void Progress_tmk24Service::placeAckReplyOfWriteTableFromDevice(std::string deviceIdentName, bool writeIsNormal) {
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

bool Progress_tmk24Service::getAckStatusDeviceAffterWriteTable(std::string deviceIdentName) {
    bool res = false;
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            res = it->first.writeIsNormal;
        }
    }
    return res;
}

QList<std::string> Progress_tmk24Service::requestWriteTableToAllDevice() {
    QList<std::string>list;
    if(operation == OPERATION_IDLE) {
        for(auto it: devList) {
            list.push_back(it->first.devId);
            it->first.isWhitedResult = true;
        }
        operation = OPERATION_WHITE_WRITE;
    }
    return list;
}
