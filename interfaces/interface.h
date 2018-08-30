#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QMultiMap>
#include "interfaceBLE.h"
#include "interfaceSerial.h"
#include "interfaceEthernet.h"
#include "device/devicesFactory.h"

class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(interfacesAbstract::eInterfaceTypes type,
                       QString conName,
                       QStringList param);
    Interface(const Interface &);
    ~Interface();

public slots:

    bool openInterface(QString name, QStringList arg);
    bool isOpen();

    void closeInterface();

    // Interface
    QString getInterfaceName();
    QStringList getInfoInterface(QString name);
    QStringList getAvailableList();

    bool writeData(QByteArray data);
    void readData(QByteArray &data);

    // DevideFactory
    bool addNewDevice(DeviceAbstract::E_DeviceType, QStringList parameters);
    bool removeDevice(DeviceAbstract::E_DeviceType, QStringList parameters);
    int getDeviceCount();
    QStringList getDeviceInfo(int indexDev);

signals:
    void errorConnection(interfacesAbstract::eInterfaceTypes type, QString conName);
private slots:
   void errorInterface(QString errorMessage);

private:
    interfacesAbstract::eInterfaceTypes interfaceType;
    InterfaceEthernet *ethernet;
    InterfaceBLE *ble;
    InterfaceSerial *serialPort;
    DevicesFactory *deviceFactory;
};

#endif // INTERFACE_H
