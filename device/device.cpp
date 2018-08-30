#include "./device/device.h"

Device::Device(DeviceAbstract::E_DeviceType type,
               QStringList &parameters) {
    this->parameters = parameters;
    this->type = type;
}

Device::~Device() {}

void Device::setState(E_State state) {
    this->state = state;
}

DeviceAbstract::E_State Device::getState() {
    return state;
}

DeviceAbstract::E_DeviceType Device::getType() {
    return type;
}

QStringList Device::getSettings() {
    QStringList ret;
    if(type == Type_Progress_Tmk324) {
        ret = progressTmk324->getSettings();
    }
    return ret;
}

bool Device::setSettings(QStringList setts) {
    bool res = false;
    if(type == Type_Progress_Tmk324) {
        res = progressTmk324->setSettings(setts);
    }
    return res;
}

QStringList Device::getCurrentData() {
    QStringList ret;
    if(type == Type_Progress_Tmk324) {
        ret = progressTmk324->getCurrentData();
    }
    return ret;
}

QVector<int> Device::getCommandListToIdlePoll() {
    QVector<int> retVect;
    if(type == Type_Progress_Tmk324) {
        retVect = progressTmk324->getCommandListToIdlePoll();
    }
    return retVect;
}

QStringList Device::getParameters() {
    return parameters;
}

bool Device::makeDataToCommand(QByteArray &array, int commandType, QByteArray commandArg) {

}

bool Device::placeReplyDataOfCommand(QByteArray &array, int commandType) {

}
