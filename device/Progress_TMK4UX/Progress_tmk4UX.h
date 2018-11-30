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

    static constexpr char *name = (char*)"PROGRESS TMK4UX";

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
    QList<int> getChart() override;
    QList<CommandController::sCommandData> getCommandToCheckConnected() override;
    QList<CommandController::sCommandData> getCommandToGetType() override;
    QList<CommandController::sCommandData> getCommandtoCheckPassword() override;
    QList<CommandController::sCommandData> getCommandListToInit() override;
    QList<CommandController::sCommandData> getCommandListToUpdate() override;
    QList<CommandController::sCommandData> getCommandListToCurrentData() override;
    QList<CommandController::sCommandData> getCommandCustom(QString operation, QPair<QStringList, QStringList> data) override;
    QStringList execCommand(QString operation, QPair<QStringList, QStringList> data);

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
