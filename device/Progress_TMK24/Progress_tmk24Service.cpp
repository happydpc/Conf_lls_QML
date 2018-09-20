#include "Progress_tmk24Service.h"

Progress_tmk24Service::Progress_tmk24Service() {
    
}

void Progress_tmk24Service::reset() {
    
}

bool Progress_tmk24Service::addDevice(QString devTypeName, QString devId, QString devSn) {
    bool isDuplicate = false;
    bool res = false;
    // поиск дубликата id
    for(auto it: devList) {
        if(it.first.devId == devId) {
            isDuplicate = true;
            break;
        }
    }
    if(!isDuplicate) {
        sDevIdentBlock idBlock;
        idBlock.devTypeName = devTypeName;
        idBlock.devId = devId;
        idBlock.devSn = devSn;
        devList.push_back(QPair<sDevIdentBlock, QList<sDevValues>*>(idBlock, new QList<sDevValues>()));
        res = true;
    } else {
        lastError = "Не удалось добавить т.к. такой номер уже есть в списке!";
    }
    return res;
}

void Progress_tmk24Service::removeDevice(int index) {
    
}

int Progress_tmk24Service::getDeviceCount() {
    return devList.size();
}

QStringList Progress_tmk24Service::getDeviceProperty(int index) {
    QStringList res;
    res << devList.at(index).first.devTypeName;
    res << devList.at(index).first.devId;
    res << devList.at(index).first.devSn;
    return res;
}

QList<QStringList> Progress_tmk24Service::getCalibrateList() {
    QList<QStringList>res;
    // 1 devTypeName
    // 2 devId
    // 3 devSn
    // 4 isChecked
    for(auto it: devList) {
        QStringList dev;
        dev.push_back(it.first.devTypeName);
        dev.push_back(it.first.devId);
        dev.push_back(it.first.devSn);
        res.push_back(dev);
    }
    return res;
}

bool Progress_tmk24Service::addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs) {
    
}
bool Progress_tmk24Service::changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs) {
    
}
void Progress_tmk24Service::removeStep(int index) {
    
}

QList<QString> Progress_tmk24Service::requestGetTableFromAllDevice() {
    QList<QString>list;
    for(auto it: devList) {
        list.push_back(it.first.devId);
        it.first.isWhitedResult = true;
    }
    return list;
}


void Progress_tmk24Service::placeTableFromDevice(QString deviceIdentName, QStringList table) {
    for(int i=0; i<devList.size(); i++) {
        if(devList.at(i).first.devId == deviceIdentName) {
            bool paritybit = false;
            devList.at(i).second->clear();
            sDevValues tDevValues;
            for(int i=0; i<table.size(); i++) {
                if(!paritybit) {
                    paritybit = true;
                    tDevValues.valueLiters = QString(table.at(i)).toInt();
                } else {
                    tDevValues.valueCnt = QString(table.at(i)).toInt();
                    paritybit = false;
                    devList.at(i).second->push_back(tDevValues);
                }
            }
            devList[i].first.isWhitedResult = false;
        }
    }
}

bool Progress_tmk24Service::readTableAllDeviceIsReady() {
    bool isAllReplyReady = true;
    for(auto it: devList) {
        if(it.first.isWhitedResult == true) {
            isAllReplyReady = false;
        }
    }
    return isAllReplyReady;
}

QStringList Progress_tmk24Service::getTableAtDevice(int index) {
    QStringList res;
    bool paritybit = false;
    QList<sDevValues>*tList = devList.at(index).second;
    for(int i=0; i<tList->size(); i++ ) {
        if(!paritybit) {
            paritybit = true;
            res << QString::number(tList->at(i).valueLiters);
        } else {
            res << QString::number(tList->at(i).valueCnt);
            paritybit = false;
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
