#ifndef  NOZZLE_REV_0_00_H
#define  NOZZLE_REV_0_00_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Nozzle_Revision_0_00_Oct_2018_Data.h"

class Nozzle_Revision_0_00_Oct_2018 : public DeviceAbstract
{
public:
    Nozzle_Revision_0_00_Oct_2018(std::list<std::string> keys, std::list<std::string> values);
    ~Nozzle_Revision_0_00_Oct_2018();

    static constexpr char* name = "Nozzle Rev 0.0";
    static constexpr char COMMAND_START_BYTE = (char) 0xC0;
    static constexpr char COMMAND_STOP_BYTE  = (char) 0xC5;
    static constexpr char COMMAND_ESC_BYTE   = (char) 0xC1;
    static constexpr char COMMAND_ESC_ESC_BYTE    = (char) 0xC2;

    std::string getDevTypeName() override;
    std::string getDevHeader() override;
    std::string getUniqId() override;
    void setDevHeader(std::string header) override;
    std::pair<std::list<std::string>,std::list<std::string>> getPropertyData() override;
    std::pair<std::list<std::string>,std::list<std::string>> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    std::pair<std::list<std::string>,std::list<std::string>> getSettings() override;
    std::pair<std::list<std::string>,std::list<std::string>> getErrors() override;
//    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
//    bool placeDataReplyToCommand(QByteArray &commandArray, CommandController::sCommandData commandReqData) override;

//    QList<CommandController::sCommandData> getCommandToCheckConnected() override;
//    QList<CommandController::sCommandData> getCommandToGetType() override;
//    QList<CommandController::sCommandData> getCommandtoCheckPassword() override;
//    QList<CommandController::sCommandData> getCommandListToInit() override;
//    QList<CommandController::sCommandData> getCommandListToUpdate() override;
//    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
//    QList<CommandController::sCommandData> getCommandCustom(std::string operation, std::pair<std::list<std::string>, std::list<std::string>> data) override;
    std::list<std::string> execCommand(std::string operation, std::pair<std::list<std::string>, std::list<std::string>>) override;
    ServiceDevicesAbstract* getServiceAbstract() override;
    std::list<int> getChart() override;
    QList<std::string> getCurrentOtherData() const;
    QList<std::pair<std::string,QByteArray>> prepareReply(QByteArray &data);
//    void parseCommandReply(const QByteArray data, const CommandController::sCommandData commandReqData);

private slots:
    void setDefaultValues();
    std::pair<bool, std::pair<int,int>> findTag(std::string regExpValueBegin, std::string regExpValueEnd, QByteArray data);

private:
    Nozzle_Revision_0_00_Oct_2018_Data::S_dev_data dev_data;
    std::string serialNumber;
    QByteArray commandArrayReplyData;
    QByteArray packData(QByteArray *commandData);

    struct {
        std::string id;
        std::string header;
    }deviceIdent;
};

#endif // NOZZLE_REV_0_00_H
