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

    typedef enum {
        Type_Update_ChangeStatus,
        Type_Update_Removed,
        Type_Update_Added,
        Type_Update_RamakeAfterChangeInterface,
        Type_Update_PasswordIncorrect,
        Type_Update_TypeIncorrect
    }E_DeviceUpdateType;

public slots:

    bool addNewDevice(QString type, QPair<QStringList,QStringList>param, ServiceDevicesAbstract *pDevService);
    bool removeDevice(QString uniqDevName);
    bool removeDeviceByIndex(int index);
    bool removeDeviceAll();

    QString getDeviceName(int index);
    QString getDeviceNameWithId(int index);
    QString getDeviceHeader(int index);
    void setDeviceHeader(int index, QString header);
    int getDeviceCount();
    QStringList getAvailableDeviceTypes();
    QString getDeviceIdTextByIndex(int index);
    QPair<QStringList,QStringList> getDeviceSettigns(int indexDev);
    QPair<QStringList,QStringList> getDeviceErrrors(int indexDev);
    int getDeviceStatusByIndex(int index);
    QPair<QStringList,QStringList> getDeviceCurrentDataByIndex(int index);
    QPair<QStringList,QStringList> getDevicePropertyByIndex(int index);

    DeviceAbstract::E_State getDevStateByIndex(int index);

    DeviceAbstract* getDeviceToDeviceAbstract(int index);

    QPair<QString,DeviceAbstract*>* findDeviceByIndex(int index);
    QPair<QString,DeviceAbstract*>* findDeviceByUnicIdent(QString name);
    int findDeviceIndex(QString uniqNameId);

    QList<int>getDeviceChartByIndex(int index);

signals:
    void deviceConnectedSignal(QString devType, QString uniqNameId);
    void deviceDisconnectedSignal(QString devType, QString uniqNameId);
    void deviceReadyCurrentDataSignal(QString devType, QString uniqNameId);
    void deviceReadyPropertiesSignal(QString devType, QString uniqNameId);
    void deviceReadyInitSignal(QString devType, QString uniqNameId);
    void deviceUpdateTree(E_DeviceUpdateType status, int index);
    void deviceReadyCustomCommand(int devIndex, QString devType, QStringList keyData, QStringList valueData, CommandController::sCommandData);
    void deviceReadyLog(int indexDev, QStringList message);

private slots:
    void deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent devTypeEvent, QString devId, QStringList devKey, QStringList devValue, CommandController::sCommandData command);
    void lockMutextDevMap();
    void unlockMutextDevMap();
private:
    QVector<QPair<QString,DeviceAbstract*>> deviceMap;
    std::unique_ptr<QMutex> devMutex;
};

#endif // DEVICESFACTORY_H
