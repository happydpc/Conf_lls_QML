#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QVector>
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
    QStringList getDeviceHeaderByIndex(int index);

    QList<int> getDeviceChartByIndex(int index);
    QList<QString> getDeviceCurrentDataByIndex(int index);

    QString getDeviceTypeByIndex(int index);
    QStringList getDeviceCurrentPropertyByIndex(int index);

    QStringList getDeviceInfo(int indexDev);

    QStringList getAvailableDeviceTypes();

    bool addCommandDevice(CommandController::sCommandData commandData);
    void addCommandDeviceReadAfterInitByIndex(int index);

    void placeReplyDataFromInterface(QByteArray data);

    QString getCaptionToTypeDevice(DeviceAbstract::E_DeviceType type);
    DeviceAbstract::E_DeviceType getDeviceTypeFromTypeCaption(QString typeDevText);

signals:
    void writeData(DeviceAbstract::E_DeviceType type, QByteArray data);
    void readReplyData();

private slots:
    //-- gives the oldest devices
    Device* getDevOldest();
    //-- sheduller slot
    void devShedullerSlot();
    //--
    bool writeCommandToDev(Device *pDev, CommandController::sCommandData commandData);

private:
    QVector<QPair<QString,Device*>> deviceMap;
    CommandController *commandController;

    QTimer* devShedullerTimer;
    Device* lastRequestedDevice;

    const int delayAfterSendCommandMs = 500;
    const int devShedullerControlInterval = 500;
};

#endif // DEVICESFACTORY_H
