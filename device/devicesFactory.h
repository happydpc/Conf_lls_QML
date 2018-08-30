#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QMultiMap>
#include <QTimer>
#include "device.h"
#include "command/commandController.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();

public slots:
    bool addNewDevice(DeviceAbstract::E_DeviceType, QStringList parameters);
    bool removeDevice(DeviceAbstract::E_DeviceType, QStringList parameters);

    int getDeviceCount();
    QStringList getDeviceInfo(int indexDev);

    bool sendCommandDev(Device *pDev, int commandType, QByteArray commandArg);

signals:
    void writeData(QByteArray data);
    void readReplyData(QByteArray &data);

private slots:
    void devShedullerSlot();

    Device* getDevOldest();

private:
    QMultiMap<DeviceAbstract::E_DeviceType, Device*> device;
    CommandController *commandController;
    QTimer *devShedullerTimer;

    const int delayAfterSendCommandMs = 500;
    const int devShedullerControlInterval = 500;
};

#endif // DEVICESFACTORY_H
