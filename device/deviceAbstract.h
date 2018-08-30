#ifndef DEVICEABSTRACT_H
#define DEVICEABSTRACT_H

#include <QObject>

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
        Type_Progress_Tmk324,
        Type_Progress_Base
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

    virtual bool makeDataToCommand(QByteArray &array, int commandType, QByteArray commandArg) = 0;
    virtual bool placeReplyDataOfCommand(QByteArray &array, int commandType) = 0;

    // возвращает список команд, если нет активности и можно опросить
    virtual QVector<int> getCommandListToIdlePoll() = 0;


    DeviceAbstract::E_State state;

private:


};

#endif // DEVICEABSTRACT_H
