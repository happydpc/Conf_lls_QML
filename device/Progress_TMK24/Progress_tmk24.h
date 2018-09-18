#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Progress_tmk24Data.h"
#include "calibrate/calibrate.h"

class Progress_tmk24 : public DeviceAbstract
{
public:
    Progress_tmk24(QString uniqIdentId, QString passwordSession);
    ~Progress_tmk24();

    static constexpr char* name = "PROGRESS TMK24";

    QString getDevTypeName() override;
    QStringList getPropertyData() override;
    QStringList getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    QPair<QStringList,QStringList> getSettings() override;
    QStringList getErrors() override;
    QString getUniqIdent() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, bool isNeedMessageAboutExecuted) override;
Progress_tmk24_H
    CommandController::sCommandData getCommandToCheckConnected() override;
    CommandController::sCommandData getCommandToGetType() override;
    CommandController::sCommandData getCommandtoCheckPassword() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList> data) override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation) override;

    QList<int> getChart() override;

    QList<QString>getCurrentOtherData();

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif  
private slots:
    void setDefaultValues();

private:   
    Calibrate *calibrateTmk24;
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings newSettings;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;
    QList<int> *chartData;
    QString uniqIdentId;
};

#endif // Progress_tmk24_H
