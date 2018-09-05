#ifndef  Progress_tmk13_H
#define  Progress_tmk13_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Progress_tmk13Data.h"
#include "device/devicesFactory.h"

class Progress_tmk13 : public DeviceAbstract
{
public:
    Progress_tmk13(QString uniqIdentId);
    ~Progress_tmk13();

    static constexpr char *name = "Progress tmk13";

    QString getDevTypeName() override;
    QStringList getPropertyData() override;
    QStringList getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    QString getUniqIdent() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData) override;
    QList<CommandController::sCommandData> getCommandListToIdlePoll() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<int> getChart() override;

//    time_t getLastDataReqDev();
//    void setLastDataReqDev(time_t curData);

//    QStringList getSettings();
//    bool setSettings(QStringList settigns);

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif
private slots:
    void setDefaultValues();

private:
    Progress_tmk13Data tmkData;
    Progress_tmk13Data::T_calibrationTable calibrationTable;
    Progress_tmk13Data::T_settings newSettings;
    Progress_tmk13Data::T_settings settings;
    Progress_tmk13Data::S_lls_data lls_data;
    QList<int> *chartData;
    QString uniqIdentId;
};

#endif // Progress_tmk13_H
