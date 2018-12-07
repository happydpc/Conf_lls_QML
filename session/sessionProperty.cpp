#include "sessionProperty.h"

SessionProperty::SessionProperty() : sessionName("default") {

}

SessionProperty::SessionProperty(std::string sessionName) {
    this->sessionName = sessionName;
    this->isValid = false;
}

void SessionProperty::setIsValid(bool value) {
    isValid = value;
}

bool SessionProperty::getIsValid() {
    return isValid;
}

void SessionProperty::setSessionName(std::string sessionName) {
    this->sessionName = sessionName;
}

std::string SessionProperty::getSessionName() {
    return sessionName;
}

void SessionProperty::addInterface(sInterface value) {
    session.push_back(value);
}

void SessionProperty::addDevice(sDevices device) {
    session.last().devices.push_back(device);
}

QList<SessionProperty::sInterface> SessionProperty::getInterfaces() {
    return session;
}
