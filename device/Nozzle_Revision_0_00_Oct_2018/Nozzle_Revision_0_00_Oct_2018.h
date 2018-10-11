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
    Nozzle_Revision_0_00_Oct_2018(QString nameDevice);
    ~Nozzle_Revision_0_00_Oct_2018();

    const int CRITICAL_SIZE_BUF = 24000;
    static constexpr char* name = "Nozzle Revision 0.00 Oct 2018";

    QString getDevTypeName() override;
    QPair<QStringList,QStringList> getPropertyData() override;
    QPair<QStringList,QStringList> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    QPair<QStringList,QStringList> getSettings() override;
    QStringList getErrors() override;
    QString getUniqIdent() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) override;

    CommandController::sCommandData getCommandToCheckConnected() override;
    CommandController::sCommandData getCommandToGetType() override;
    CommandController::sCommandData getCommandtoCheckPassword() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList> data) override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation) override;
    QList<int> getChart() override;
    ServiceDevicesAbstract* getServiceAbstract() override;

    QList<QString>getCurrentOtherData();
    void parseCommandReply(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff command, CommandController::sCommandData commandReqData);

private slots:
    void setDefaultValues();

private:
    Nozzle_Revision_0_00_Oct_2018_Data::S_dev_data dev_data;
    QString serialNumber;
    QString versionFirmware;
    QList<int> *chartData;
    QByteArray inputBuffer;
    QString uniqIdentId;
};

#endif // NOZZLE_REV_0_00_H
