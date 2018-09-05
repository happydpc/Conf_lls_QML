#include "./device/deviceAbstract.h"

DeviceAbstract::DeviceAbstract(QObject *parent) : QObject(parent)
{
    this->state = STATE_DISCONNECTED;
    this->devLastDataRequest = 0;
}

time_t DeviceAbstract::getLastDataReqDev() {
    return devLastDataRequest;
}

void DeviceAbstract::setLastDataReqDev(time_t date) {
    devLastDataRequest = date;
}
