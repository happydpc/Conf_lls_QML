#include "./device/deviceAbstract.h"

DeviceAbstract::DeviceAbstract(QObject *parent) : QObject(parent)
{
    this->state = STATE_DISCONNECTED;
}

int DeviceAbstract::getPriority() {
    return priority;
}

void DeviceAbstract::setPriority(int value) {
    priority = value;
}
