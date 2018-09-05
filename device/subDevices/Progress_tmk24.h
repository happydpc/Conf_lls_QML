#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Progress_tmk24Data.h"
#include "device/devicesFactory.h"

//#define USE_TEST_DEV_REPLY  1

class Progress_tmk24 : public DeviceAbstract
{
public:
    Progress_tmk24(QString uniqDevName);
    ~Progress_tmk24();

    static constexpr char* name = "Progress tmk24";

    QString getName() override;

    QStringList getSettings();
    bool setSettings(QStringList settigns);
    QStringList getPropertyData();

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
    Progress_tmk24Data tmk24Data;
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings newSettings;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;
    QList<int> *chartData;
};

#endif // Progress_tmk24_H
