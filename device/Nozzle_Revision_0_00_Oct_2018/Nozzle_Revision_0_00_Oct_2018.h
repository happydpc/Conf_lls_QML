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
    Nozzle_Revision_0_00_Oct_2018(QString devId, QString header);
    ~Nozzle_Revision_0_00_Oct_2018();

    static constexpr char* name = "Nozzle Revision 0.00 Oct 2018";

    QString getDevTypeName() override;
    QString getDevHeader() override;
    QString getUniqId() override;
    void setDevHeader(QString header) override;
    QPair<QStringList,QStringList> getPropertyData() override;
    QPair<QStringList,QStringList> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    QPair<QStringList,QStringList> getSettings() override;
    QPair<QStringList,QStringList> getErrors() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArray, CommandController::sCommandData commandReqData) override;

    CommandController::sCommandData getCommandToCheckConnected() override;
    CommandController::sCommandData getCommandToGetType() override;
    CommandController::sCommandData getCommandtoCheckPassword() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList> data) override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation) override;
    ServiceDevicesAbstract* getServiceAbstract() override;

    QList<QString>getCurrentOtherData();
    QList<QPair<QString,QByteArray>> prepareReply(QByteArray &data);
    void parseCommandReply(QByteArray data, CommandController::sCommandData commandReqData);

private slots:
    void setDefaultValues();
    QPair<bool, QPair<int,int>> findTag(QString regExpValueBegin, QString regExpValueEnd, QByteArray data);

private:
    Nozzle_Revision_0_00_Oct_2018_Data::S_dev_data dev_data;
    QString serialNumber;
    QString versionFirmware;
    QByteArray commandArrayReplyData;

    struct {
        QString id;
        QString header;
    }deviceIdent;
};

#endif // NOZZLE_REV_0_00_H
