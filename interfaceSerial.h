#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QObject>
#include "interfacesAbstract.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class InterfaceSerial : public interfacesAbstract
{
    Q_OBJECT
public:
    explicit InterfaceSerial();
    ~InterfaceSerial();

    QStringList getAvailableInterfaceList();

signals:
    QStringList updateAvailableInterfaceList();

public slots:
};

#endif // INTERFACESERIAL_H
