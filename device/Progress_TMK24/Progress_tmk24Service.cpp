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

QList<QStringList> Progress_tmk24Service::getCalibrateList() {
    QList<QStringList>res;
    for(auto it: devList) {
        QStringList dev;
        dev.push_back(it->first.devTypeName);
        dev.push_back(it->first.devId);
        dev.push_back(it->first.devSn);
        res.push_back(dev);
    }
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


void Progress_tmk24Service::placeTableFromDevice(QString deviceIdentName, QStringList table) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            bool paritybit = false;
            it->second->clear();
            sDevValues tDevValues;
            for(int i=0; i<table.size(); i++) {
                if(!paritybit) {
                    paritybit = true;
                    tDevValues.valueLiters = QString(table.at(i)).toUInt();
                } else {
                    tDevValues.valueCnt = QString(table.at(i)).toUInt();
                    paritybit = false;
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
        res << QString::number(devList.at(index)->second->at(i).valueCnt);
    }
    return res;
}

void Progress_tmk24Service::placeCurrenDataFromDevice(QString deviceIdentName, QList<QString> currentData) {
    for(auto it: devList) {
        if(it->first.devId == deviceIdentName) {
            if(currentData.length() >= 2) {
                it->first.currData.cnt = currentData.at(2).toUInt();
                it->first.currData.liters = currentData.at(0).toUInt();
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
        res << QString::number(devList.at(index)->first.currData.cnt);
        res << QString::number(devList.at(index)->first.currData.liters);
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

//void Progress_tmk24Service::setLastRealTimeValuesToStep(int indexStep) {
//    if(indexStep == -1) {
//        indexStep = 0;
//    }
//    for(auto itDev: devList) {
//        while(itDev->second->size() < indexStep+1) {
//            itDev->second->push_back(*new sDevValues);
//        }
//        sDevValues tDevValues = itDev->second->at(indexStep);
//        if(itDev->first.currData.isValid) {
//            tDevValues.valueCnt = itDev->first.currData.cnt;
//            tDevValues.valueLiters = itDev->first.currData.liters;
//        } else {
//            tDevValues.valueCnt = 0;
//            tDevValues.valueLiters = 0;
//        }
//        itDev->second->replace(indexStep, tDevValues);
//    }
//}

int Progress_tmk24Service::getMaxCountStep() {
    int res = 0;
    for(auto itDev: devList) {
        if(res < itDev->second->size()) {
            res = itDev->second->size();
        }
    }
    return res;
}

////1) запрос от viewcontroller->QML
//// считать таблицу с добавленных устройств
//void Calibrate::requestGetTableFromAllDevice() {
//    setStatus(CALIBRATE_STATUS_NEED_GET_TABLE_FROM_DEVICES);
//}

//// ответы от devs
//void Calibrate::placeDeviceDataAtCurrentData(QString uniqNameId, uint32_t cntValue, uint32_t freq, uint32_t fuelLevel) {

//}
//// ответы от devs
//void Calibrate::placeDeviceDataAtTableData(QString unqNameId, QStringList tarListValueLiters, QStringList tarListValueCnt) {

//}

//// командный планировщик
//// опрашивает устройства
//// отправляет им команды
//QList<CommandController::sCommandData> Calibrate::getCommandList() {
//    QList<CommandController::sCommandData> listCommand;
//    CommandController::sCommandData command;
//    switch(getStatus()) {
//    // нормальное ожидание
//    case Calibrate::CALIBRATE_STATUS_IDLE:
//        break;

//        // надо отправить запрос на чтение таблицы со всех устройств
//    case Calibrate::CALIBRATE_STATUS_NEED_GET_TABLE_FROM_DEVICES:
//        command.deviceIdent = getUniqIdent();
//        command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//        listCommand.push_back(command);
//        for(auto it: devList) {
//            it.first.devId
//        }
//        setStatus(Calibrate::CALIBRATE_STATUS_WHITE_REPLY_READ_TABLE_FROM_DEVICES);
//        break;

//        // запрос отправили, теперь надо собрать ответы
//    case Calibrate::CALIBRATE_STATUS_WHITE_REPLY_READ_TABLE_FROM_DEVICES:
//        // если все собрали
//        setStatus(Calibrate::CALIBRATE_STATUS_GET_TABLE_FROM_DEVICE_NORMAL_READY);
//        break;

//        // ответы собрали
//        // здесь надо оптравить сигнла в DeviceFactory
//        // в custom разбор ответов от dev
//        // там разобрать и передать в viewControl -> QML
//        // после emit поменять статус на idle
//    case Calibrate::CALIBRATE_STATUS_GET_TABLE_FROM_DEVICE_NORMAL_READY:
////        emit ();
//        setStatus(Calibrate::CALIBRATE_STATUS_IDLE);
//        break;
//    }

//    //    int calibrateSize = calibrateTmk24->getDeviceCount();
//    //    for(int i=0; i<calibrateSize; i++) {
//    //        calibrateTmk24->get
//    //    }

//    //    command.deviceIdent = getUniqIdent();
//    //    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
//    //    listCommand.push_back(command);
//    //    command.devCommand = (int)Progress_tmk24Data::lls_read_cnt;
//    //    listCommand.push_back(command);
//    //    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
//    //    listCommand.push_back(command);
//    //    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
//    //    listCommand.push_back(command);
//    return listCommand;
//}

//Calibrate::eStatus Calibrate::getStatus() {
//    return status;
//}

//void Calibrate::setStatus(Calibrate::eStatus status) {
//    this->status = status;
//}

//QString Calibrate::getLastError() {
//    return lastError;
//}
