#include "interfaceSerial.h"

InterfaceSerial::InterfaceSerial() {

}

InterfaceSerial::~InterfaceSerial() {

}

QStringList InterfaceSerial::getAvailableInterfaceList() {
    QStringList portList;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        QStringList list;
        list << info.portName();
        portList << list.first();
    }
    return portList;
}
