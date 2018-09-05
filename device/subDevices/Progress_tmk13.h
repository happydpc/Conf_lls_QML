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
    Progress_tmk13(QString uniqDevName);
    ~Progress_tmk13();

    static constexpr char *name = "Progress tmk13";

    QString getName() override;
    QStringList getPropertyData() override;



    QStringList getSettings();
    bool setSettings(QStringList settigns);

    bool makeDataToComand(CommandController::sCommandData &commandData);
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData);

    QList<int>getChart();

    QList<QString>getCurrentOtherData();

    QList<CommandController::sCommandData> getCommandListToIdlePoll(QString deviceIdent);

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif
private slots:
    void resetValues();

private:
    Progress_tmk13Data tmkData;
    Progress_tmk13Data::T_calibrationTable calibrationTable;
    Progress_tmk13Data::T_settings newSettings;
    Progress_tmk13Data::T_settings settings;
    Progress_tmk13Data::S_lls_data lls_data;
    QList<int> *chartData;
};

#endif // Progress_tmk13_H
