#include "calibrate.h"

Calibrate::Calibrate(QObject *parent) : QObject(parent) {
}

void Calibrate::reset() {

}
bool Calibrate::addDevice(QString devTypeName, QString devId, QString devSn) {
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
        devList.push_back(QPair<sDevIdentBlock, sDevValues>(idBlock, sDevValues()));
        res = true;
    } else {
        lastError = "Не удалось добавить т.к. такой номер уже есть в списке!";
    }
    return res;
}

void Calibrate::removeDevice(int index) {

}

int Calibrate::getDeviceCount() {
    return devList.size();
}

QStringList Calibrate::getDeviceProperty(int index) {
    QStringList res;
    res << devList.at(index).first.devTypeName;
    res << devList.at(index).first.devId;
    res << devList.at(index).first.devSn;
    return res;
}

QList<QStringList> Calibrate::getCalibrateList() {
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

bool Calibrate::addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs) {

}
bool Calibrate::changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs) {

}
void Calibrate::removeStep(int index) {

}

QString Calibrate::getLastError() {
    return lastError;
}
