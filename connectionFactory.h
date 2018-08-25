#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include "interfaceSerial.h"
#include "interfaceBLE.h"
#include "interfaceEthernet.h"
#include <QVector>

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:

    explicit ConnectionFactory(QObject *parent = nullptr);
    ~ConnectionFactory();

    bool serialPortIsAvailable();
    bool bleIsAvailable();
    bool ethernetIsAvailable();

    Q_INVOKABLE bool addConnectionToSerialPort(QString portName, int baudrate);
    Q_INVOKABLE bool addConnectionToBLE(QString portName);
    Q_INVOKABLE bool addConnectionToEthernet(QString portName);

    Q_INVOKABLE bool removeConnectionToSerialPort(QString portName);
    Q_INVOKABLE bool removeConnectionToBLE(QString portName);
    Q_INVOKABLE bool removeConnectionToEthernet(QString portName);

    Q_INVOKABLE QStringList getAvailableInterfacesToSerialPort();
    Q_INVOKABLE QStringList getAvailableInterfacesToBLE();
    Q_INVOKABLE QStringList getAvailableInterfacesToEthernet();

private slots:
    bool addConnection(interfacesAbstract::eInterfaceTypes, QString name, int *arg);
    bool removeConnection(interfacesAbstract::eInterfaceTypes, QString name);
    QStringList getAvailableInterfacesFromType(interfacesAbstract::eInterfaceTypes);

private:

    InterfaceSerial *interfaceSerial;
    InterfaceEthernet *interfaceEthernet;
    InterfaceBLE *interfaceBLE;

};

#endif // CONNECTIONFACTORY_H
