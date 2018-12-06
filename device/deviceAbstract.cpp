#include "./device/deviceAbstract.h"

DeviceAbstract::DeviceAbstract(QObject *parent) : QObject(parent) {
    this->state = STATE_DISCONNECTED;
}
