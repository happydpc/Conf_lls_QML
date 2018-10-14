#ifndef SERVICEDEVICESABSTRACT_H
#define SERVICEDEVICESABSTRACT_H

#include <QObject>

class ServiceDevicesAbstract : public QObject
{
    Q_OBJECT
public:
    ServiceDevicesAbstract();

    QString getDeviceType();

signals:

public slots:

protected:
    QString ownDeviceName;
};

#endif // SERVICEDEVICESABSTRACT_H
