#include "session.h"

Session::Session() {

}

void Session::addInterface(sInterface value) {
    interface = value;
}

void Session::addDevice(sDevices value) {
    devices.push_back(value);
}
