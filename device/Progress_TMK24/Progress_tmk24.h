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
#include <vector>

class Progress_tmk24 : public DeviceAbstract
{
public:
    explicit Progress_tmk24(std::vector<std::string> keyValue, std::vector<std::string> value);
    ~Progress_tmk24();

    static constexpr char* name = (char*)"PROGRESS TMK24";

    std::string getDevTypeName() override;
    std::string getDevHeader() override;
    void setDevHeader(std::string header) override;

    std::pair<std::vector<std::string>,std::vector<std::string>> getPropertyData() override;
    std::pair<std::vector<std::string>,std::vector<std::string>> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    std::pair<std::vector<std::string>,std::vector<std::string>> getSettings() override;
    std::pair<std::vector<std::string>,std::vector<std::string>> getErrors() override;
    std::string getUniqId() override;
//    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
//    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) override;

//    Qvector<CommandController::sCommandData> getCommandToCheckConnected() override;
//    Qvector<CommandController::sCommandData> getCommandToGetType() override;
//    Qvector<CommandController::sCommandData> getCommandtoCheckPassword() override;
//    Qvector<CommandController::sCommandData> getCommandvectorToInit() override;
//    Qvector<CommandController::sCommandData> getCommandvectorToUpdate() override;
//    Qvector<CommandController::sCommandData> getCommandvectorToCurrentData() override;
//    Qvector<CommandController::sCommandData> getCommandCustom(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>> data) override;
    std::vector<std::string> execCommand(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>>) override;
    std::vector<int> getChart() override;
    ServiceDevicesAbstract* getServiceAbstract() override;
    std::vector<std::string>getCurrentOtherData();
private slots:
    void setDefaultValues();

private:
    std::shared_ptr<ServiceDevicesAbstract> service;
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;

    std::vector<int>chartData;

    struct {
        std::string id;
        std::string header;
    }deviceIdent;
};

#endif // Progress_tmk24_H
