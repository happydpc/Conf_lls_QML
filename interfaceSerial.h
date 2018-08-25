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
    InterfaceSerial(const InterfaceSerial &);


    QStringList getAvailableInterfaceList() override;
    bool openInterface(QString, int *arg) override;
    bool closeInterface() override;
    QString getPortName();
    QStringList getInfoAbortPort(QString portName);

signals:
    QStringList updateAvailableInterfaceList();

    void portMessage(InterfaceSerial::eInterfaceMessageType, QString name);

public slots:

private:
    QSerialPort *portHandler;

};

#endif // INTERFACESERIAL_H
