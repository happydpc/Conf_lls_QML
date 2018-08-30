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

}

bool Interface::openInterface(QString name, QStringList arg) {
    bool res = false;
    if(this->interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        res = serialPort->openInterface(name, arg);
        if(res) {
            connect(serialPort, SIGNAL(errorInterface(QString)), SLOT(errorInterface(QString)));
            connect(deviceFactory, SIGNAL(writeData(QByteArray)), this, SLOT(writeData(QByteArray)));
            connect(deviceFactory, SIGNAL(readReplyData(QByteArray&)), this, SLOT(readData(QByteArray&)));
        }
    }
}

bool Interface::isOpen() {
    if(this->interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        return serialPort->isOpen();
    }
}

void Interface::closeInterface() {

}

QString Interface::getInterfaceName() {
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        //        return serialPort.is
    }
}

QStringList Interface::getInfoInterface(QString name) {

}

QStringList Interface::getAvailableList() {
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        return serialPort->getAvailableList();
    }
}

bool Interface::writeData(QByteArray data) {
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        return serialPort->sendData(data);
    }
}

void Interface::readData(QByteArray &data) {
    if(interfaceType == interfacesAbstract::InterfaceTypeSerialPort) {
        serialPort->readData(data);
    }
}

void Interface::errorInterface(QString errorMessage) {
    emit errorConnection(interfaceType, getInterfaceName());
}

bool Interface::addNewDevice(DeviceAbstract::E_DeviceType type, QStringList parameters) {
    bool res = false;
    res = deviceFactory->addNewDevice(type, parameters);
    return res;
}

bool Interface::removeDevice(DeviceAbstract::E_DeviceType type, QStringList parameters) {
    return deviceFactory->removeDevice(type, parameters);
}

int Interface::getDeviceCount() {
    return deviceFactory->getDeviceCount();
}

QStringList Interface::getDeviceInfo(int indexDev) {
    return deviceFactory->getDeviceInfo(indexDev);
}
