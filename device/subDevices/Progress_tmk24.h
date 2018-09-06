#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Progress_tmk24Data.h"
#include "device/devicesFactory.h"

class Progress_tmk24 : public DeviceAbstract
{
public:
    Progress_tmk24(QString uniqIdentId);
    ~Progress_tmk24();

    static constexpr char* name = "Progress tmk24";

    QString getDevTypeName() override;
    QStringList getPropertyData() override;
    QStringList getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    QString getUniqIdent() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData) override;
    CommandController::sCommandData getCommandToCheckConnected() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<int> getChart() override;

    QStringList getSettings();
    bool setSettings(QStringList settigns);

    QList<QString>getCurrentOtherData();

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif  
private slots:
    void setDefaultValues();

private:
    Progress_tmk24Data tmk24Data;
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings newSettings;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;
    QList<int> *chartData;
    QString uniqIdentId;
};

#endif // Progress_tmk24_H
