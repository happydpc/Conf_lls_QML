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
        STATE_NORMAL_READY
    }E_State;

    virtual QString getDevTypeName() = 0;
    virtual QStringList getPropertyData() = 0;
    virtual QStringList getCurrentData() = 0;
    virtual QString getUniqIdent() = 0;
    virtual E_State getState() = 0;
    virtual bool makeDataToCommand(CommandController::sCommandData &commandData) = 0;
    virtual bool placeDataReplyToCommand(QByteArray &commandArrayReplyData) = 0;
    virtual QList<CommandController::sCommandData> getCommandListToIdlePoll() = 0;
    virtual QList<CommandController::sCommandData> getCommandListToInit() = 0;
    virtual QList<int> getChart() = 0;

    time_t getLastDataReqDev();
    void setLastDataReqDev(time_t date);

//    virtual void setState(E_State state) = 0;
//    virtual DeviceAbstract::E_State getState() = 0;

//    virtual QString getType() = 0;

//    virtual QStringList getSettings() = 0;
//    virtual bool setSettings(QStringList setts) = 0;

//    virtual QStringList getParameters() = 0;

//    // возвращает список команд, если нет активности и можно опросить

//    DeviceAbstract::E_State state;
//    QString deviceUniqIdentName;

    DeviceAbstract::E_State state;
private:
    // есть базовые команды, для определения что dev еще жив
    // это последнее время такой команды для этого устройства
    time_t devLastDataRequest;
};

#endif // DEVICEABSTRACT_H
