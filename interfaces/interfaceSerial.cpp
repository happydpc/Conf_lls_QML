#include "./interfaces/interfaceSerial.h"
#include "QDebug"

InterfaceSerial::InterfaceSerial(QString name, QPair<QStringList,QStringList>param) {
    this->deviceFactory = new DevicesFactory();
    this->portHandler = new QSerialPort();
    this->name = name;
    this->param = param;
}
InterfaceSerial::~InterfaceSerial() {}
void InterfaceSerial::initInterface()  {}

bool InterfaceSerial::openInterface() {
    QString baudrate;
    for(int key=0; key<param.second.size(); key++) {
        if(param.first[key] == "baudrate") {
            baudrate = param.second[key];
        }
    }
    portHandler->setPortName(name);
    portHandler->setBaudRate(baudrate.toInt());
    portHandler->setDataBits(QSerialPort::Data8);
    portHandler->setParity(QSerialPort::NoParity);
    portHandler->setStopBits(QSerialPort::OneStop);
    portHandler->setFlowControl(QSerialPort::NoFlowControl);
    //connect(portHandler, SIGNAL(errorInterface(QString)), SLOT(errorInterface(QString)));
    connect(deviceFactory, SIGNAL(writeData(QByteArray)),
            this, SLOT(writeData(QByteArray)));
    connect(deviceFactory, SIGNAL(readReplyData()), this, SLOT(readData()));
    return portHandler->open(QIODevice::ReadWrite);
}

bool InterfaceSerial::isOpen() {
    return portHandler->isOpen();
}

void InterfaceSerial::closeInterface() {
    if(portHandler != nullptr) {
        if(portHandler->isOpen()) {
            portHandler->close();
        }
    }
}

bool InterfaceSerial::sendData(QByteArray &pData)  {
    if(!portHandler->isOpen()) {
        return false;
    }
    return (bool)portHandler->write(pData);
}

bool InterfaceSerial::readData(QByteArray &pData)  {
    if(!portHandler->isOpen()) {
        return false;
    }
    pData = portHandler->readAll();
    return (bool)pData.length();
}

QString InterfaceSerial::getInterfaceName() {
    return portHandler->portName();
}

QStringList InterfaceSerial::getInterfaceProperty() {
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString baudrate;
    QStringList list;
    if(portHandler->isOpen()) {
        const auto infos = QSerialPortInfo::availablePorts();
        for(const QSerialPortInfo &info : infos) {
            if(info.portName().contains(portHandler->portName())) {
                description = info.description();
                manufacturer = info.manufacturer();
                serialNumber = info.serialNumber();
                if(portHandler->isOpen()) {
                    baudrate = QString::number(portHandler->baudRate());
                }
                list << description;
                list << manufacturer;
                list << serialNumber;
                list << info.portName();
                list << baudrate;
                break;
            }
        }
    }
    return list;
}

bool InterfaceSerial::writeData(QByteArray data) {
    return portHandler->write(data);
}

void InterfaceSerial::readData() {
    QByteArray data;
    data = portHandler->readAll();
    deviceFactory->placeReplyDataFromInterface(data);
}

QStringList InterfaceSerial::getAvailableList() {
    QStringList list;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        if(portHandler != nullptr) {
            if(!portHandler->isOpen()) {
                list << info.portName();
            }
        }
    }
    return list;
}

void InterfaceSerial::errorInterface(QString errorMessage) {
}

QString InterfaceSerial::getType() {
    return QString::fromLocal8Bit(typeName, strlen(typeName));
}

void InterfaceSerial::aboutClose() {
    emit closeIsNormal();
}


DevicesFactory* InterfaceSerial::getDeviceFactory() {
    return deviceFactory;
}
