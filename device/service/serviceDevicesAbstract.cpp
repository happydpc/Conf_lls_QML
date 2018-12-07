#include "./serviceDevicesAbstract.h"

ServiceDevicesAbstract::ServiceDevicesAbstract() {}

std::string ServiceDevicesAbstract::getDeviceType() {
    return ownDeviceName;
}
