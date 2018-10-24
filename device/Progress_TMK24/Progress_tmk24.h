#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "Progress_tmk24Data.h"
#include "Progress_tmk24Service.h"
#include "../service/serviceDevicesAbstract.h"
#include "device/deviceAbstract.h"
#include "command/commandController.h"

class Progress_tmk24 : public DeviceAbstract
{
public:
    Progress_tmk24(QString uniqIdentId, QString header,
                   QPair<QStringList,QStringList>param,
                   ServiceDevicesAbstract *pServiceAbstract);
    ~Progress_tmk24();

    static constexpr char* name = "PROGRESS TMK24";

    QString getDevTypeName() override;
    QString getDevHeader() override;
    void setDevHeader(QString header) override;

    QPair<QStringList,QStringList> getPropertyData() override;
    QPair<QStringList,QStringList> getCurrentData() override;
    DeviceAbstract::E_State getState() override;
    void setState(DeviceAbstract::E_State) override;
    QPair<QStringList,QStringList> getSettings() override;
    QPair<QStringList,QStringList> getErrors() override;
    QString getUniqId() override;
    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) override;

    CommandController::sCommandData getCommandToCheckConnected() override;
    CommandController::sCommandData getCommandToGetType() override;
    CommandController::sCommandData getCommandtoCheckPassword() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<CommandController::sCommandData> getCommandListToUpdate() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList> data) override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation) override;
    ServiceDevicesAbstract* getServiceAbstract() override;

    QList<QString>getCurrentOtherData();

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif  
private slots:
    void setDefaultValues();

private:
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings settings;
    Progress_tmk24Data::S_lls_data lls_data;

    struct {
        QString id;
        QString header;
    }deviceIdent;
};

#endif // Progress_tmk24_H
