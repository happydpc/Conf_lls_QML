#include "interface.h"

Interface::Interface(interfacesAbstract::eInterfaceTypes type,
                     QString conName,
                     QStringList param) {
    this->interfaceType = type;

    if(type == interfacesAbstract::InterfaceTypeSerialPort) {
        this->serialPort = new InterfaceSerial();
    } else if(type == interfacesAbstract::InterfaceTypeBle) {
        this->ble = new InterfaceBLE();
    } else if(type == interfacesAbstract::InterfaceTypeEthrnet) {
        this->ethernet = new InterfaceEthernet();
    } else {
        throw QString("Error type connection");
    }

    this->deviceFactory = new DevicesFactory();

#ifdef USE_TEST_DEV_REPLY
    this->testDevReply = new TestDevReply();
#endif
}

Interface::Interface(const Interface & it) {
    this->interfaceType = it.interfaceType;
    if(this->interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        this->serialPort = it.serialPort;
    }
    if(this->interfaceType == interfacesAbstract::InterfaceTypeBle) {
        this->ble = it.ble;
    }
    if(this->interfaceType == interfacesAbstract::InterfaceTypeEthrnet) {
        this->ethernet = it.ethernet;
    }
}

Interface::~Interface() {
    delete deviceFactory;
}

bool Interface::openInterface(QString name, QStringList arg) {
    bool res = false;
    if(this->interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        res = serialPort->openInterface(name, arg);
        if(res) {
            connect(serialPort, SIGNAL(errorInterface(QString)), SLOT(errorInterface(QString)));
            connect(deviceFactory, SIGNAL(writeData(QByteArray)), this, SLOT(writeData(QByteArray)));
            connect(deviceFactory, SIGNAL(readReplyData()), this, SLOT(readData()));
        }
    }
    return res;
}

bool Interface::isOpen() {
    if(this->interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        return serialPort->isOpen();
    }
}

void Interface::closeInterface() {

}

QString Interface::getInterfaceName() {
    QString name;
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        name = serialPort->getInterfaceName();
    }
    return name;
}

QStringList Interface::getInfoInterface(QString name) {

}

QStringList Interface::getAvailableList() {
    QStringList list;
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        list = serialPort->getAvailableList();
    }
    return list;
}

interfacesAbstract::eInterfaceTypes Interface::getInterfaceType() {
    return interfaceType;
}

bool Interface::writeData(DeviceAbstract::E_DeviceType type, QByteArray data) {
    bool res = false;
#ifdef USE_TEST_DEV_REPLY
    testDevReply->writeDevRequestData(type, data);
#else
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        res = serialPort->sendData(data);
    }
#endif
    return res;
}

void Interface::readData() {
    QByteArray data;
#ifdef USE_TEST_DEV_REPLY
    testDevReply->readDevReplyData(data);
#else
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        serialPort->readData(data);
    }
#endif
    deviceFactory->placeReplyDataFromInterface(data);
}

void Interface::errorInterface(QString errorMessage) {
    emit errorConnection(interfaceType, getInterfaceName());
}

DevicesFactory* Interface::getDeviceFactory() {
    return deviceFactory;
}
