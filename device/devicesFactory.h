#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
//#include <QMultiMap>
//#include <device/device.h>

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();

private slots:
//    bool addConnection(interfacesAbstract::eInterfaceTypes, QString name, int *arg);
//    bool removeConnection(interfacesAbstract::eInterfaceTypes, QString name);
//    QStringList getAvailableInterfacesFromType(interfacesAbstract::eInterfaceTypes);

private:

//    QMultiMap<QString, Device> device;
};

#endif // DEVICESFACTORY_H
