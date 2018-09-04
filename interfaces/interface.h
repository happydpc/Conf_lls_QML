#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QMultiMap>
#include "interfaceBLE.h"
#include "interfaceSerial.h"
#include "interfaceEthernet.h"
#include "device/devicesFactory.h"

//#define USE_TEST_DEV_REPLY  1
#ifdef USE_TEST_DEV_REPLY
#include "tests/testDevReply.h"
#endif

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
    void closeInterface();
    bool isOpen();

    QString getInterfaceName();
    QStringList getInterfaceProperty(QString name);
    QStringList getAvailableList();
    interfacesAbstract::eInterfaceTypes getInterfaceType();
    DevicesFactory* getDeviceFactory();

signals:
    void errorConnection(interfacesAbstract::eInterfaceTypes type, QString conName);
private slots:
    bool writeData(DeviceAbstract::E_DeviceType type, QByteArray data);
    void readData();

   void errorInterface(QString errorMessage);

private:
    interfacesAbstract::eInterfaceTypes interfaceType;
    InterfaceEthernet *ethernet;
    InterfaceBLE *ble;
    InterfaceSerial *serialPort;
    DevicesFactory *deviceFactory;
#ifdef USE_TEST_DEV_REPLY
    TestDevReply *testDevReply;
#endif
};

#endif // INTERFACE_H
