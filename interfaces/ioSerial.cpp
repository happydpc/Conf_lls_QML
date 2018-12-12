#include "./interfaces/ioSerial.h"
#include <iostream>

IoSerial::IoSerial(std::string name, std::pair<std::vector<std::string>,std::vector<std::string>>param) {
    this->portHandler = std::make_shared<QSerialPort>();
    this->name = name;
    this->param = param;
    this->isManualClosed = false;
}

IoSerial::~IoSerial() {
    if(portHandler->isOpen()) {
        portHandler->close();
    }
    portHandler.reset();
}

void IoSerial::initInterface()  {

}

bool IoSerial::openInterface() {
    bool res = false;
    std::string baudrate;
    auto iterValue = param.second.begin();
    for(auto iterKey: param.first) {
        if(iterKey == "baudrate") {
            baudrate = *iterValue;
        }
        iterValue++;
    }
    portHandler->setPortName(name.c_str());
    portHandler->setBaudRate(std::stoi(baudrate));
    portHandler->setDataBits(QSerialPort::Data8);
    portHandler->setParity(QSerialPort::NoParity);
    portHandler->setStopBits(QSerialPort::OneStop);
    portHandler->setFlowControl(QSerialPort::NoFlowControl);
    res  = portHandler->open(QIODevice::ReadWrite);
    if(res) {
        connect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(errorHanler(QSerialPort::SerialPortError)));
        isManualClosed = false;
    }
    std::cout << "openInterface = " << ((res) ? ("-Ok") : ("-ERR"));
    return res;
}

bool IoSerial::isOpen() {
    return portHandler->isOpen();
}

void IoSerial::closeInterface() {
    if(portHandler != nullptr) {
        if(portHandler->isOpen()) {
            isManualClosed = true;
            portHandler->close();
            disconnect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, NULL);
        }
    }
}

bool IoSerial::sendData(QByteArray data)  {
    bool res = false;
    if(portHandler != nullptr) {
        if(!portHandler->isOpen()) {
            if(!isManualClosed) {
                openInterface();
            }
        }
        if(portHandler->isOpen()) {
            res = portHandler->write(data);
        }
    }
    return res;
}

bool IoSerial::readData(QByteArray &pData) {
    if(!portHandler->isOpen()) {
        return false;
    }
    pData = portHandler->readAll();
    return !pData.isEmpty();
}

std::string IoSerial::getInterfaceName() {
    return std::string(portHandler->portName().toLocal8Bit());
}

std::pair<std::vector<std::string>,std::vector<std::string>> IoSerial::getInterfaceProperty() {
    std::pair<std::vector<std::string>,std::vector<std::string>> res;
    if(portHandler->isOpen()) {
        const auto infos = QSerialPortInfo::availablePorts();
        for(const QSerialPortInfo &info : infos) {
            if(info.portName().contains(portHandler->portName())) {
                QString description = info.description();
                QString manufacturer = info.manufacturer();
                QString serialNumber = info.serialNumber();
                std::string baudrate;
                if(portHandler->isOpen()) {
                    baudrate = std::to_string(portHandler->baudRate());
                }
                res.first.push_back("info.portName()");
                res.second.push_back(std::string(info.portName().toLocal8Bit()));
                res.first.push_back("baudrate");
                res.second.push_back(baudrate);
                res.first.push_back("description");
                res.second.push_back(std::string(description.toLocal8Bit()));
                res.first.push_back("manufacturer");
                res.second.push_back(std::string(manufacturer.toLocal8Bit()));
                res.first.push_back("serialNumber");
                res.second.push_back(std::string(serialNumber.toLocal8Bit()));
                break;
            }
        }
    }
    return res;
}

std::vector<std::string> IoSerial::getAvailableList() {
    std::vector<std::string> res;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        if(portHandler != nullptr) {
            if(!portHandler->isOpen()) {
                res.push_back(std::string(info.portName().toLocal8Bit()));
            }
        }
    }
    return res;
}

void IoSerial::errorHanler(QSerialPort::SerialPortError err) {
    std::cout << "InterfaseSerial -ERR";
    if(err != QSerialPort::NoError) {
        disconnect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, NULL);
        portHandler->close();
        emit errorInterface(std::string(portHandler->portName().toLocal8Bit()), "Ошибка интерфейса\nПроверьте соединение");
    }
}

std::string IoSerial::getType() {
    return std::string(typeName);
}
