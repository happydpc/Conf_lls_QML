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

    std::vector<std::string> getAvailableTypeDevice() const;

    DeviceAbstract* newDevice(const std::vector<std::string> keyParam, std::vector<std::string> valueParam);
};

#endif // DEVICESFACTORY_H
