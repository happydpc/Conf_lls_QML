#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include <memory>
#include "command/commandController.h"
#include "deviceCollector.h"
#include "device/deviceAbstract.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();
    ~DevicesFactory();

    // keyParam need 2 args - 'id' and 'header'
    DeviceAbstract* newDevice(const QString devType, const QStringList keyParam, QStringList valueParam,
                      ServiceDevicesAbstract *pDevService);
};

#endif // DEVICESFACTORY_H
