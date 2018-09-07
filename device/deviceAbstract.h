#ifndef DEVICEABSTRACT_H
#define DEVICEABSTRACT_H

#include <QObject>
#include "command/commandController.h"

class DeviceAbstract : public QObject
{
    Q_OBJECT
public:
    explicit DeviceAbstract(QObject *parent = nullptr);

    typedef enum {
        STATE_DISCONNECTED,
        STATE_NEED_INIT,
        STATE_NORMAL_READY
    }E_State;

    typedef enum {
        Type_DeviceEvent_Connected,
        Type_DeviceEvent_Disconnected,
        Type_DeviceEvent_ReadyReadProperties,
        Type_DeviceEvent_Inited,
        Type_DeviceEvent_CurrentDataUpdated
    }E_DeviceEvent;

    virtual QString getDevTypeName() = 0;
    virtual QStringList getPropertyData() = 0;
    virtual QStringList getCurrentData() = 0;
    virtual QString getUniqIdent() = 0;
    virtual E_State getState() = 0;
    virtual void setState(DeviceAbstract::E_State) = 0;
    virtual bool makeDataToCommand(CommandController::sCommandData &commandData) = 0;
    virtual void makeCustromCommand(QString operation, QStringList data, CommandController::sCommandData &commandData) = 0;

    virtual bool placeDataReplyToCommand(QByteArray &commandArrayReplyData) = 0;
    virtual CommandController::sCommandData getCommandToCheckConnected() = 0;
    virtual QList<CommandController::sCommandData> getCommandListToCurrentData() = 0;
    virtual QList<CommandController::sCommandData> getCommandListToInit() = 0;
    virtual QList<int> getChart() = 0;

    int getPriority();
    void setPriority(int value);

    DeviceAbstract::E_State state;

signals:

    void eventDevice(DeviceAbstract::E_DeviceEvent typeEvent, QString deviceUniqueId, QString message);

private:
    int priority = 0;
};

#endif // DEVICEABSTRACT_H
