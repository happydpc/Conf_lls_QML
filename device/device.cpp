#include "./device/device.h"
#include <QDebug>
#include "other/crc.h"

Device::Device(DeviceAbstract::E_DeviceType type,
               QString deviceUniqIdentName,
               int deviceUniqIdentId,
               QStringList &parameters) {
    this->parameters = parameters;
    this->type = type;
    this->deviceUniqIdentName = deviceUniqIdentName;
    this->deviceUniqIdentId = deviceUniqIdentId;
    this->progressTmk324 = new Progress_tmk324();
}

Device::Device(const Device& val) {}

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

QList<CommandController::sCommandData> Device::getCommandListToIdlePoll() {
    QList<CommandController::sCommandData> retCommands;
    if(type == Type_Progress_Tmk324) {
        retCommands = progressTmk324->getCommandListToIdlePoll(deviceUniqIdentName, deviceUniqIdentId);
    }
    return retCommands;
}

QStringList Device::getParameters() {
    return parameters;
}

QString Device::getUniqIdentName() {
    return deviceUniqIdentName;
}

int Device::getUniqIdentId() {
    return deviceUniqIdentId;
}

//    void Lls::makeRequest(QByteArray *data, uint8_t id, S_command tcommand)
bool Device::makeDataToCommand(CommandController::sCommandData &commandData) {
    bool res = false;
    if(type == Type_Progress_Tmk324) {
        res = progressTmk324->makeDataToComand(commandData);
    }
    return res;
}

bool Device::placeReplyDataOfCommand(QByteArray &commandArray) {
    bool res = false;
    if(type == Type_Progress_Tmk324) {
        res = progressTmk324->placeDataReplyToCommand(commandArray);
    }
    return res;
}
