#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include <memory>
#include "command/commandController.h"
#include "device/deviceAbstract.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();
    ~DevicesFactory();

    typedef enum {
        Type_Undefined,
        Type_Progress_Tmk24,
        Type_Progress_tmk4UX,
        Type_Nozzle_rev_0_00
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

    bool addNewDevice(E_DeviceType type, QPair<QStringList,QStringList>param, ServiceDevicesAbstract *pDevService);
    void checkDeviceIsOnline(E_DeviceType type, QStringList keyParam, QStringList valParam);
    bool removeDevice(QString uniqDevName);
    bool removeDeviceByIndex(int index);
    bool removeDeviceAll();

    QString getDeviceName(int index);
    QString getDeviceNameWithId(int index);
    QString getDeviceHeader(int index);
    void setDeviceHeader(int index, QString header);
    QString getDeviceTypeNameByType(DevicesFactory::E_DeviceType type);
    E_DeviceType getDeviceType(QString typeText);
    E_DeviceType getDeviceType(int index);
    void setDeviceCommandUpdateByIndex(int index);
    void setDeviceInitCommandByIndex(int index);
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

    void placeReplyDataFromInterface(QByteArray data);
    void setDeviceReInitByIndex(int index);
    bool sendCustomCommadToDev(int indexDev, QString operation, QStringList keys, QStringList values);
    bool sendCustomCommadToDev(int indexDev, QString operation);
    void sendCustomCommandUseCallback(E_DeviceType type, QString operation, QStringList keys, QStringList values);

    QList<int>getDeviceChartByIndex(int index);

signals:
    void writeData(QByteArray data);
    void readReplyData();

    void deviceConnectedSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnectedSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInitSignal(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceCheckIsReady(DevicesFactory::E_DeviceType type, QString uniqNameId, bool isOnline);

    void deviceUpdateTree(DevicesFactory::E_DeviceUpdateType status, int index);
    void deviceReadyCustomCommand(int devIndex, QString devType, QStringList keyData, QStringList valueData, CommandController::sCommandData);
    void deviceReadyLog(int indexDev, QStringList message);

private slots:
    void devShedullerSlot();

    void deviceEventUpdateDevStatusSlot(DeviceAbstract::E_DeviceEvent devTypeEvent, QString devId, QStringList devKey, QStringList devValue, CommandController::sCommandData command);

    void lockMutextDevMap();
    void unlockMutextDevMap();

    void onReplySend();

private:
    QVector<QPair<QString,DeviceAbstract*>> deviceMap;
    std::unique_ptr<CommandController> commandController;
    std::unique_ptr<QTimer> devShedullerTimer;
    QScopedPointer<QTimer> sendReqTimer;
    std::unique_ptr<QMutex> devMutex;
    E_DeviceType factoryType;

    struct {
        QString checkedDeviceUniqName;
        E_DeviceType devType;
        bool isIdle = true;
        bool isProcessed = false;
        bool isReady = false;
        bool result = false;
    }checkDeviceStruct;

    int indexProcessedDev = 50;
    const int delayTypicalCommandMs = 150;
    const int delayIncreasedCommandMs = 300;
};

#endif // DEVICESFACTORY_H
