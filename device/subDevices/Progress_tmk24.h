#ifndef  Progress_tmk24_H
#define  Progress_tmk24_H

#include <QObject>
#include <QVector>
#include "Progress_tmk24Data.h"
#include "command/commandController.h"

//#define USE_TEST_DEV_REPLY  1

class Progress_tmk24 : public Progress_tmk24Data
{
public:
    Progress_tmk24();
    ~Progress_tmk24();

    QStringList getSettings();
    bool setSettings(QStringList settigns);
    QStringList getPropertyData();

    bool makeDataToComand(CommandController::sCommandData &commandData);
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData);

    QList<int>getChart();

    QList<QString>getCurrentOtherData();

    QList<CommandController::sCommandData> getCommandListToIdlePoll(QString deviceIdent, int deviceIdentId);

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
#endif  
private slots:
    void resetValues();

private:
    Progress_tmk24Data::T_calibrationTable calibrationTable;
    Progress_tmk24Data::T_settings newSettings;
    T_settings settings;
    S_lls_data lls_data;
    QList<int> *chartData;
};

#endif // Progress_tmk24_H
