#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <QObject>
#include "./connection/connectionFactory.h"
#include "./device/deviceController.h"

class ConnectionController : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionController();

    public slots:
    QStringList getListInterfacesConnection();

//    bool addConnection(QString interface, QString name, QStringList param);
//    bool removeConnection(QString interface, QString name, QString name);
//    QStringList getAvailableInterfaceItemsFromType(int intexType);

private:

//    Q_INVOKABLE bool addConnectionToSerialPort(QString portName, int baudrate);
//    Q_INVOKABLE bool addConnectionToBLE(QString portName);
//    Q_INVOKABLE bool addConnectionToEthernet(QString portName);

//    Q_INVOKABLE bool removeConnectionToSerialPort(QString portName);
//    Q_INVOKABLE bool removeConnectionToBLE(QString portName);
//    Q_INVOKABLE bool removeConnectionToEthernet(QString portName);

//    Q_INVOKABLE QStringList getAvailableInterfacesToSerialPort();
//    Q_INVOKABLE QStringList getAvailableInterfacesToBLE();
//    Q_INVOKABLE QStringList getAvailableInterfacesToEthernet();

private:
    ConnectionFactory *connectionFactory;
    DeviceController *devController;
};

#endif // CONNECTIONCONTROLLER_H





signals:
// отсылает сколько каких коннектов можно создать
void readyCreateNewConnections(int connecionsCountTypes);
// горит что что-то там открылось
void connectionOpened(QString nameInterface, QString subName);
// закрылось штатно
void connectionClosed(QString name);
// закрылось изза ошибки
void connectionClosedWithError(QString name);

// говорит какой из коннектов сейчас активен на форме
void activeCurrentInterface(QString nameInterface, int indexInterface,
                            int activeDeviceIndex);

private slots:
void currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes, QString name, int index);

public slots:

//    void interfaceMessageSlot(InterfaceSerial::eInterfaceMessageType message, QString name);

private:
ConnectionController *connectionController;
