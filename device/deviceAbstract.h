#ifndef DEVICEABSTRACT_H
#define DEVICEABSTRACT_H

#include <QObject>
#include "command/commandController.h"
#include "service/serviceDevicesAbstract.h"

class DeviceAbstract : public QObject
{
    Q_OBJECT
public:
    explicit DeviceAbstract(QObject *parent = nullptr);

    typedef enum {
        STATE_DISCONNECTED,
        STATE_CHECK_PASSWORD,
        STATE_START_INIT,
        STATE_GET_TYPE,
        STATE_NORMAL_READY
    }E_State;

    typedef enum {
        Type_DeviceEvent_Connected,
        Type_DeviceEvent_Disconnected,
        Type_DeviceEvent_ReadyReadProperties,
        Type_DeviceEvent_Inited,
        Type_DeviceEvent_CurrentDataUpdated,
        Type_DeviceEvent_PasswordError,
        Type_DeviceEvent_TypeError,
        Type_DeviceEvent_ExectCustomCommand,
        Type_DeviceEvent_LogMessage
    }E_DeviceEvent;

    virtual QString getDevTypeName() = 0;
    virtual QPair<QStringList,QStringList> getPropertyData() = 0;
    virtual QPair<QStringList,QStringList> getCurrentData() = 0;
    virtual QString getUniqIdent() = 0;
    virtual QPair<QStringList,QStringList> getSettings() = 0;
    virtual QPair<QStringList,QStringList> getErrors() = 0;
    virtual E_State getState() = 0;
    virtual void setState(DeviceAbstract::E_State) = 0;
    virtual bool makeDataToCommand(CommandController::sCommandData &commandData) = 0;

    virtual bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) = 0;
    virtual CommandController::sCommandData getCommandToCheckConnected() = 0;
    virtual CommandController::sCommandData getCommandToGetType() = 0;
    virtual CommandController::sCommandData getCommandtoCheckPassword() = 0;
    virtual QList<CommandController::sCommandData> getCommandListToInit() = 0;
    virtual QList<CommandController::sCommandData> getCommandListToCurrentData() = 0;
    virtual QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList>) = 0;
    virtual QList<CommandController::sCommandData> getCommandCustom(QString operation) = 0;
    virtual QList<int> getChart() = 0;

    virtual ServiceDevicesAbstract* getServiceAbstract() = 0;

    int getPriority();
    void setPriority(int value);

    DeviceAbstract::E_State state;
    ServiceDevicesAbstract* serviceAbstact;

signals:
    void eventDeviceUpdateState(DeviceAbstract::E_DeviceEvent typeEvent, QString deviceUniqueId,
                                int operation, QString operationResult, QStringList customData, CommandController::sCommandData commandData);
private:
    int priority = 0;
};

#endif // DEVICEABSTRACT_H
