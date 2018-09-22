#include "./device/deviceAbstract.h"

DeviceAbstract::DeviceAbstract(QObject *parent) : QObject(parent)
{
    this->state = STATE_DISCONNECTED;
}

ServiceDevicesAbstract* DeviceAbstract::getServiceAbstract() {
    return serviceAbstact;
}

int DeviceAbstract::getPriority() {
    return priority;
}

void DeviceAbstract::setPriority(int value) {
    priority = value;
}
