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
    ~DevicesFactory();

public slots:
    bool addNewDevice(DeviceAbstract::E_DeviceType, QString uniqDevName, int uniqDevId, QStringList parameters);
    bool removeDevice(DeviceAbstract::E_DeviceType, QString uniqDevName, QStringList parameters);

    int getDeviceCount();

    QStringList getDeviceInfo(int indexDev);

    bool addCommandDevice(CommandController::sCommandData commandData);

    void placeReplyDataFromInterface(QByteArray data);

signals:
    void writeData(QByteArray data);
    void readReplyData();

private slots:
    //-- gives the oldest devices
    Device* getDevOldest();
    //-- sheduller slot
    void devShedullerSlot();
    //--
    bool writeCommandToDev(Device *pDev, CommandController::sCommandData commandData);

private:
    QMap<QString,Device*> deviceMap;
    CommandController *commandController;

    QTimer* devShedullerTimer;
    Device* lastRequestedDevice;

    const int delayAfterSendCommandMs = 500;
    const int devShedullerControlInterval = 500;
};

#endif // DEVICESFACTORY_H
