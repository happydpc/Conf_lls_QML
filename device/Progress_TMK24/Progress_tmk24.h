#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "Progress_tmk24Data.h"
#include "Progress_tmk24Service.h"
#include "../service/serviceDevicesAbstract.h"
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include <memory>

class Progress_tmk24 : public DeviceAbstract
{
public:
    explicit Progress_tmk24(std::list<std::string> keyValue, std::list<std::string> value);
    ~Progress_tmk24();

    static constexpr char* name = (char*)"PROGRESS TMK24";

    std::string getDevTypeName() override;
    std::string getDevHeader() override;
    void setDevHeader(std::string header) override;

    std::pair<std::list<std::string>,std::list<std::string>> getPropertyData() override;
    std::pair<std::list<std::string>,std::list<std::string>> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    std::pair<std::list<std::string>,std::list<std::string>> getSettings() override;
    std::pair<std::list<std::string>,std::list<std::string>> getErrors() override;
    std::string getUniqId() override;
//    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
//    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) override;

//    QList<CommandController::sCommandData> getCommandToCheckConnected() override;
//    QList<CommandController::sCommandData> getCommandToGetType() override;
//    QList<CommandController::sCommandData> getCommandtoCheckPassword() override;
//    QList<CommandController::sCommandData> getCommandListToInit() override;
//    QList<CommandController::sCommandData> getCommandListToUpdate() override;
//    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
//    QList<CommandController::sCommandData> getCommandCustom(std::string operation, std::pair<std::list<std::string>, std::list<std::string>> data) override;
    std::list<std::string> execCommand(std::string operation, std::pair<std::list<std::string>, std::list<std::string>>) override;
    std::list<int> getChart() override;
    ServiceDevicesAbstract* getServiceAbstract() override;
    QList<std::string>getCurrentOtherData();
private slots:
    void setDefaultValues();

private:
    std::shared_ptr<ServiceDevicesAbstract> service;
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;

    std::list<int>chartData;

    struct {
        std::string id;
        std::string header;
    }deviceIdent;
};

#endif // Progress_tmk24_H
