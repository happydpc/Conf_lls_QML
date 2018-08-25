#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "connectionFactory.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();

    // говорим что нужен новый коннект
    Q_INVOKABLE void addConnectionRequest();
    Q_INVOKABLE void addConnection(QString nameInterface, QString subName, QString param);
    Q_INVOKABLE QStringList getAvailableListInterfaceOfType(int indexType); // первый - это имя интерфейса (SerialPort,Ble,Ethernet)


signals:
    // отсылает сколько каких коннектов можно создать
    void readyCreateNewConnections(int connecionsCountTypes);
    // горит что что-то там открылось
    void connectionOpened(QString nameInterface, QString subName);
    // закрылось штатно
    void connectionClosed(QString name);
    // закрылось изза ошибки
    void connectionClosedWithError(QString name);

private slots:
//    bool addConnection(interfacesAbstract::eInterfaceTypes, QString name, int *arg);
//    bool removeConnection(interfacesAbstract::eInterfaceTypes, QString name);
//    QStringList getAvailableInterfacesFromType(interfacesAbstract::eInterfaceTypes);

public slots:

//    void interfaceMessageSlot(InterfaceSerial::eInterfaceMessageType message, QString name);

private:
    ConnectionFactory *connectionFactory;

//    InterfaceSerial *interfaceSerial;
//    InterfaceEthernet *interfaceEthernet;
//    InterfaceBLE *interfaceBLE;


signals:

public slots:
};

#endif // CONNECTION_H
