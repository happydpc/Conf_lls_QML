#ifndef SERVICEDEVICESABSTRACT_H
#define SERVICEDEVICESABSTRACT_H

#include <QObject>

class ServiceDevicesAbstract : public QObject
{
    Q_OBJECT
public:
    ServiceDevicesAbstract();

    std::string getDeviceType();

signals:

public slots:

protected:
    std::string ownDeviceName;
};

#endif // SERVICEDEVICESABSTRACT_H
