#include "session.h"

Session::Session() : Session("defaultName") {}

Session::Session(QString sessionName) {
    this->sessionName = sessionName;
    this->isValid = false;
}

void Session::setIsValid(bool value) {
    isValid = value;
}

bool Session::getIsValid() {
    return isValid;
}

void Session::setSessionName(QString sessionName) {
    this->sessionName = sessionName;
}

QString Session::getSessionName() {
    return sessionName;
}

void Session::addInterface(sInterface value) {
    session.push_back(value);
}

void Session::addDevice(sDevices device) {
    session.last().devices.push_back(device);
}

QList<Session::sInterface> Session::getInterfaces() {
    return session;
}

//QList<Session::sDevices> Session::getDevices() {
//    return devices;
//}
