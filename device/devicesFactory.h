#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include "command/commandController.h"
#include "device/deviceAbstract.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();
    ~DevicesFactory();

    typedef enum {
        Type_Progress_Tmk24,
        Type_Progress_tmk4UX,
        Type_Nozzle_rev_0_00,
        Type_Undefined
    }E_DeviceType;

    typedef enum {
        Type_Update_ChangeStatus,
        Type_Update_Removed,
        Type_Update_Added,
        Type_Update_RamakeAfterChangeInterface,
        Type_Update_PasswordIncorrect,
        Type_Update_TypeIncorrect
    }E_DeviceUpdateType;

public slots:

    bool addNewDevice(E_DeviceType type, QString uniqDevName, QStringList parameters, ServiceDevicesAbstract *pDevService);
    bool removeDevice(QString uniqDevName);
    bool removeDeviceByIndex(int index);
    bool removeDeviceAll();

    QString getDeviceName(int index);
    QString getDeviceNameByType(DevicesFactory::E_DeviceType type);
    E_DeviceType getDeviceType(QString typeText);
    E_DeviceType getDeviceType(int index);
    void setDeviceInitCommandByIndex(int index);
    int getDeviceCount();
    QStringList getAvailableDeviceTypes();
    QStringList getDeviceHeaderByIndex(int index);
    QString getDeviceIdTextByIndex(int index);
    QPair<QStringList,QStringList> getDeviceSettigns(int indexDev);
    QStringList getDeviceErrrors(int indexDev);
    int getDeviceStatusByIndex(int index);
    QList<int> getDeviceChartByIndex(int index);
    QList<QString> getDeviceCurrentDataByIndex(int index);
    QStringList getDevicePropertyByIndex(int index);
    QStringList getDeviceProperty(int indexDev);
    DeviceAbstract::E_State getDevStateByIndex(int index);

    DeviceAbstract* getDeviceToDeviceAbstract(int index);

    QPair<QString,DeviceAbstract*>* findDeviceByIndex(int index);
    QPair<QString,DeviceAbstract*>* findDeviceByUnicIdent(QString name);
    int findDeviceIndex(QString uniqNameId);

    void placeReplyDataFromInterface(QByteArray data);
    void setDeviceReInitByIndex(int index);
    void sendCustomCommadToDev(int indexDev, QString operation, QPair<QStringList, QStringList> arguments);
    void sendCustomCommadToDev(int indexDev, QString operation);

signals:
    void writeData(QByteArray data);
    void readReplyData();

    void deviceConnectedSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnectedSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInitSignal(DevicesFactory::E_DeviceType, QString uniqNameId);

    void deviceUpdateTree(DevicesFactory::E_DeviceUpdateType status, int index);
    void deviceReadyCustomCommand(int index, QString message, QStringList customData, CommandController::sCommandData);

private slots:
    void devShedullerSlot();

    void deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent type, QString devUniqueId,
                                        int commandType, QString,QStringList, CommandController::sCommandData commandData);

    void lockMutextDevMap();
    void unlockMutextDevMap();

private:
    QVector<QPair<QString,DeviceAbstract*>> deviceMap;

    QVector<CommandController::sCommandData> commandList;

    QTimer* devShedullerTimer;

    QMutex* devMutex;

    QList<ServiceDevicesAbstract*> serviceList;

    int indexProcessedDev = 0;

    const int delayAfterSendCommandMs = 150;
    const int devShedullerControlInterval = 1;
};

#endif // DEVICESFACTORY_H
