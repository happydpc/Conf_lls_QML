#include "./interfaces/interfaceSerial.h"
#include "QDebug"

InterfaceSerial::InterfaceSerial(QString name, QPair<QStringList,QStringList>param) {
    this->deviceController = std::make_shared<DeviceController>();
    this->portHandler = std::make_unique<QSerialPort>();
    this->name = name;
    this->param = param;
    this->isManualClosed = false;
//    connect(deviceFactory.get(), SIGNAL(writeData(QByteArray)),
//            this, SLOT(writeData(QByteArray)));
//    connect(deviceFactory.get(), SIGNAL(readReplyData()), this, SLOT(readData()));
}

InterfaceSerial::~InterfaceSerial() {
    if(portHandler->isOpen()) {
        portHandler->close();
    }
//    deviceFactory.reset();
    delete portHandler.release();
}

void InterfaceSerial::initInterface()  {

}

bool InterfaceSerial::openInterface() {
    bool res = false;
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
    res  = portHandler->open(QIODevice::ReadWrite);
    if(res) {
        connect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(errorHanler(QSerialPort::SerialPortError)));
        isManualClosed = false;
    }
    qDebug() << "openInterface = " << ((res) ? (QString("-Ok")) : (QString("-ERR")));
    return res;
}

bool InterfaceSerial::isOpen() {
    return portHandler->isOpen();
}

void InterfaceSerial::closeInterface() {
    if(portHandler != nullptr) {
        if(portHandler->isOpen()) {
            isManualClosed = true;
            portHandler->close();
            disconnect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, NULL);
        }
    }
}

bool InterfaceSerial::sendData(QByteArray &pData)  {
    if(!portHandler->isOpen()) {
        return false;
    }
    return (bool)portHandler->write(pData);
}

bool InterfaceSerial::readData(QByteArray &pData) {
    if(!portHandler->isOpen()) {
        return false;
    }
    pData = portHandler->readAll();
    return !pData.isEmpty();
}

QString InterfaceSerial::getInterfaceName() {
    return portHandler->portName();
}

QPair<QStringList,QStringList> InterfaceSerial::getInterfaceProperty() {
    QPair<QStringList,QStringList> res;
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString baudrate;
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
                res.first.push_back("info.portName()");
                res.second.push_back(info.portName());
                res.first.push_back("baudrate");
                res.second.push_back(baudrate);
                res.first.push_back("description");
                res.second.push_back(description);
                res.first.push_back("manufacturer");
                res.second.push_back(manufacturer);
                res.first.push_back("serialNumber");
                res.second.push_back(serialNumber);
                break;
            }
        }
    }
    return res;
}

//bool InterfaceSerial::writeData(QByteArray data) {
//    bool res = false;
//    if(portHandler != nullptr) {
//        if(!portHandler->isOpen()) {
//            if(!isManualClosed) {
//                openInterface();
//            }
//        }
//        if(portHandler->isOpen()) {
//            res = portHandler->write(data);
//        }
//    }
//    return res;
//}

//void InterfaceSerial::readData() {
//    QByteArray data;
//    if(portHandler->isOpen()) {
//        data = portHandler->readAll();
//    }
//    deviceCollector->placeReplyDataFromInterface(data);
//}

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

void InterfaceSerial::errorHanler(QSerialPort::SerialPortError err) {
    qDebug() << "InterfaseSerial -ERR=" << err;
    if(err != QSerialPort::NoError) {
        disconnect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, NULL);
        portHandler->close();
        emit errorInterface(portHandler->portName(), tr("Ошибка интерфейса\nПроверьте соединение"));
    }
}

QString InterfaceSerial::getType() {
//    return QString::fromLocal8Bit(typeName, strlen(typeName));
}

DevicesFactory* InterfaceSerial::getDeviceFactory() {
    return deviceController.get()->getDeviceFactory();
}
