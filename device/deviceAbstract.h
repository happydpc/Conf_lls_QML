#ifndef DEVICEABSTRACT_H
#define DEVICEABSTRACT_H

#include <QObject>
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

    virtual std::string getDevTypeName() = 0;
    virtual std::string getDevHeader() = 0;
    virtual void setDevHeader(std::string header) = 0;

    virtual std::pair<std::vector<std::string>,std::vector<std::string>> getPropertyData() = 0;
    virtual std::pair<std::vector<std::string>,std::vector<std::string>> getCurrentData() = 0;
    virtual std::string getUniqId() = 0;
    virtual std::pair<std::vector<std::string>,std::vector<std::string>> getSettings() = 0;
    virtual std::pair<std::vector<std::string>,std::vector<std::string>> getErrors() = 0;
    virtual E_State getState() = 0;
    virtual void setState(DeviceAbstract::E_State) = 0;

//    virtual bool makeDataToCommand(Command &commandData) = 0;
//    virtual bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandToCheckConnected() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandToGetType() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandtoCheckPassword() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandvectorToInit() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandvectorToUpdate() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandvectorToCurrentData() = 0;
//    virtual Qvector<CommandController::sCommandData> getCommandCustom(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>>) = 0;
    virtual std::vector<std::string> execCommand(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>>) = 0;

    virtual std::vector<int> getChart() = 0;
    virtual ServiceDevicesAbstract* getServiceAbstract() = 0;

    int getPriority();
    void setPriority(int value);

    DeviceAbstract::E_State state;

signals:
//    void eventDeviceUpdateState(DeviceAbstract::E_DeviceEvent typeEvent, std::string deviceUniqueId,
//                                std::vector<std::string> keyCustomData, std::vector<std::string> valueCustomData,
//                                CommandController::sCommandData commandData);
private:
    int priority = 0;
};

#endif // DEVICEABSTRACT_H
