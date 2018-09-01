#include "./device/deviceAbstract.h"

DeviceAbstract::DeviceAbstract(QObject *parent) : QObject(parent)
{
    this->state = STATE_DISCONNECTED;
    this->lastDataRequestDev = 0;
    this->deviceUniqIdentName.clear();
    this->deviceUniqIdentId = 0;
    this->parameters.clear();
}

void DeviceAbstract::setState(E_State state) {
    this->state = state;
}

DeviceAbstract::E_State DeviceAbstract::getState() {
    return state;
}

time_t DeviceAbstract::getLastDataReqDev() {
    return lastDataRequestDev;
}

void DeviceAbstract::setLastDataReqDev(time_t curData) {
    lastDataRequestDev = curData;
}
