#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include "device/deviceAbstract.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();
    ~DevicesFactory();

    QStringList getAvailableTypeDevice() const;

    // keyParam need 2 args - 'id' and 'header'
    DeviceAbstract* newDevice(const QString devType, const QStringList keyParam, QStringList valueParam);
};

#endif // DEVICESFACTORY_H
