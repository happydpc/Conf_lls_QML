#include "./serviceDevicesAbstract.h"

ServiceDevicesAbstract::ServiceDevicesAbstract() {}

QString ServiceDevicesAbstract::getDeviceType() {
    return ownDeviceName;
}
