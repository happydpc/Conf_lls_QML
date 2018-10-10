#ifndef Progress_tmk4UX_H
#define Progress_tmk4UX_H

#include <QObject>
#include <QVector>
#include "device/deviceAbstract.h"
#include "command/commandController.h"
#include "Progress_tmk4UXData.h"

class Progress_tmk4UX : public DeviceAbstract
{
public:
    Progress_tmk4UX(QString uniqIdentId, QString passwordSession);
    ~Progress_tmk4UX();

    static constexpr char *name = "PROGRESS TMK4UX";

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

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif
private slots:
    void setDefaultValues();

private:
    Progress_tmk4UXData tmkData;
    QList<int> *chartData;
    QString uniqIdentId;
};

#endif // Progress_tmk4UX_H
