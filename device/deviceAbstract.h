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

    typedef enum {
        Type_Progress_Tmk24,
        Type_Progress_Tmk13,
        Type_Progress_default = Type_Progress_Tmk24
    }E_DeviceType;

    time_t getLastDataReqDev();
    void setLastDataReqDev(time_t curData);

    // есть базовые команды, для определения что dev еще жив
    // это последнее время такой команды для этого устройства
    time_t lastDataRequestDev;

    virtual void setState(E_State state) = 0;
    virtual DeviceAbstract::E_State getState() = 0;
    virtual E_DeviceType getType() = 0;
    virtual QStringList getSettings() = 0;
    virtual bool setSettings(QStringList setts) = 0;
    virtual QStringList getCurrentData() = 0;
    virtual QStringList getParameters() = 0;
    virtual QString getUniqIdentName() = 0;
    virtual int getUniqIdentId() = 0;

    virtual bool makeDataToCommand(CommandController::sCommandData &commandData) = 0;
    virtual bool placeReplyDataOfCommand(QByteArray &array) = 0;

    // возвращает список команд, если нет активности и можно опросить
    virtual QList<CommandController::sCommandData> getCommandListToIdlePoll() = 0;

    QString type_Progress_Tmk24_caption = "Progress TMK24";
    QString type_Progress_Tmk13_caption = "Progress TMK13";
    QList <QPair<E_DeviceType,QString>> deviceAvailableTypesList;

    DeviceAbstract::E_State state;
    QString deviceUniqIdentName;
    int deviceUniqIdentId;
    QStringList parameters;

private:


};

#endif // DEVICEABSTRACT_H
