#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QMultiMap>
#include "./interfaces/interfaceSerial.h"
#include "./interfaces/interfaceBLE.h"
#include "./interfaces/interfaceEthernet.h"

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionFactory(QObject *parent = nullptr);
    ~ConnectionFactory();

public slots:
//    bool addConnection(interfacesAbstract::eInterfaceTypes, QString name, int *arg);
//    bool removeConnection(interfacesAbstract::eInterfaceTypes, QString name);

    QStringList getAvailableInterfaces();
    QStringList getAvailableSubIterfaces(interfacesAbstract::eInterfaceTypes);

private:

    QMultiMap<QString, InterfaceSerial>interfacesSerial;
    QMultiMap<QString, InterfaceEthernet>interfaceEthernet;
    QMultiMap<QString, InterfaceBLE>interfaceBLE;
};

#endif // CONNECTIONFACTORY_H
