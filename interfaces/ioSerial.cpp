#include "./interfaces/ioSerial.h"
#include "QDebug"

IoSerial::IoSerial(QString name, QPair<QStringList,QStringList>param) {
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

QString IoSerial::getInterfaceName() {
    return portHandler->portName();
}

QPair<QStringList,QStringList> IoSerial::getInterfaceProperty() {
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

QStringList IoSerial::getAvailableList() {
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

void IoSerial::errorHanler(QSerialPort::SerialPortError err) {
    qDebug() << "InterfaseSerial -ERR=" << err;
    if(err != QSerialPort::NoError) {
        disconnect(portHandler.get(), SIGNAL(error(QSerialPort::SerialPortError)), this, NULL);
        portHandler->close();
        emit errorInterface(portHandler->portName(), tr("Ошибка интерфейса\nПроверьте соединение"));
    }
}

QString IoSerial::getType() {
    return QString::fromLocal8Bit(typeName, strlen(typeName));
}
