#ifndef DEVICESFACTORY_H
#define DEVICESFACTORY_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "command/commandController.h"
#include "device/deviceAbstract.h"
#include "device/subDevices/Progress_tmk13.h"
#include "device/subDevices/Progress_tmk24.h"

class DevicesFactory : public QObject
{
    Q_OBJECT
public:
    explicit DevicesFactory();
    ~DevicesFactory();

    typedef enum {
        Type_Progress_Tmk24,
        Type_Progress_Tmk13,
        Type_Undefined
    }E_DeviceType;

public slots:

    bool addNewDevice(E_DeviceType type, QString uniqDevName, QStringList parameters);
    bool removeDevice(QString uniqDevName);

    QString getDeviceName(int index);
    E_DeviceType getDeviceType(QString typeText);
    QString getDeviceNameByType(DevicesFactory::E_DeviceType type);

    int getDeviceCount();
    QStringList getDeviceHeaderByIndex(int index);

    QList<int> getDeviceChartByIndex(int index);
    QList<QString> getDeviceCurrentDataByIndex(int index);


    QStringList getDeviceCurrentPropertyByIndex(int index);

    QString getDeviceIdTextByIndex(int index);

    QStringList getDeviceProperty(int indexDev);

    QStringList getAvailableDeviceTypes();

    bool addCommandDevice(CommandController::sCommandData commandData);

    void placeReplyDataFromInterface(QByteArray data);

//    QString getCaptionToTypeDevice(DeviceAbstract::E_DeviceType type);
//    DeviceAbstract::E_DeviceType getDeviceTypeFromTypeCaption(QString typeDevText);
//    DeviceAbstract::E_DeviceType getDeviceTypebyIndex(int index);

    void setDeviceAsNotReadyByIndex(int index);

signals:
//    void writeData(DeviceAbstract::E_DeviceType type, QByteArray data);
    void readReplyData();

private slots:
    //-- find device by index
    QPair<QString,DeviceAbstract*>* findDeviceByIndex(int index);
    QPair<QString,DeviceAbstract*>* findDeviceByUnicIdent(QString name);

    //-- gives the oldest devices
//    Device* getDevOldest();
    //-- sheduller slot
    void devShedullerSlot();
    //--
//    bool writeCommandToDev(Device *pDev, CommandController::sCommandData commandData);

private:
    QVector<QPair<QString,DeviceAbstract*>> deviceMap;
    CommandController *commandController;

    QTimer* devShedullerTimer;
//    Device* lastRequestedDevice;

    const int delayAfterSendCommandMs = 500;
    const int devShedullerControlInterval = 500;
};

#endif // DEVICESFACTORY_H
