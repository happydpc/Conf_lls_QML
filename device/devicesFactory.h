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

    std::list<std::string> getAvailableTypeDevice() const;

    // keyParam need 2 args - 'id' and 'header'
    DeviceAbstract* newDevice(const std::string devType, const std::list<std::string> keyParam, std::list<std::string> valueParam);
};

#endif // DEVICESFACTORY_H
