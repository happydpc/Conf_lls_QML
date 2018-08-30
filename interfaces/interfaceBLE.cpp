#include "./interfaces/interfaceBLE.h"

InterfaceBLE::InterfaceBLE()
{

}

InterfaceBLE::InterfaceBLE(const InterfaceBLE & it) {

}

InterfaceBLE::~InterfaceBLE() {

}

void InterfaceBLE::initInterface()  {

}

bool InterfaceBLE::openInterface(QString name, QStringList arg) {
//    bool res = false;
//    QString *parg = &arg;
//    QStringList listArg;
//    while(*parg != nullptr) {
//        listArg << (*parg);
//        parg++;
//    }
//    if(listArg.size() >0) {
//        portHandler->setPortName(name);
//        portHandler->setBaudRate(QString(listArg.at(0)).toInt());
//        portHandler->setDataBits(QSerialPort::Data8);
//        portHandler->setParity(QSerialPort::NoParity);
//        portHandler->setStopBits(QSerialPort::OneStop);
//        portHandler->setFlowControl(QSerialPort::NoFlowControl);
//        res = portHandler->open(QIODevice::ReadWrite);
//    }
//    return res;
}

void InterfaceBLE::closeInterface() {
//    if(portHandler != nullptr) {
//        if(portHandler->isOpen()) {
//            portHandler->close();
//        }
//    }
}

bool InterfaceBLE::sendData(QByteArray &pData)  {
    return false;
}

bool InterfaceBLE::readData(QByteArray &pData)  {
    return false;
}

QString InterfaceBLE::getInterfaceName() {
//    return portHandler->portName();
}

QStringList InterfaceBLE::getInfoInterface(QString name) {
    QStringList list;
    return list;
}

bool InterfaceBLE::isOpen() {
    return portHandler->isOpen();
}

void InterfaceBLE::aboutClose() {
    emit closeIsNormal();
}

QStringList InterfaceBLE::getAvailableList() {
    QStringList list;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        if(!portHandler->isOpen()) {
            list << info.portName();
        }
    }
    return list;
}
