#ifndef  Progress_tmk13_H
#define  Progress_tmk13_H

#include <QObject>
#include <QVector>
#include "Progress_tmk13Data.h"
#include "command/commandController.h"

//#define USE_TEST_DEV_REPLY  1

class Progress_tmk13 : public Progress_tmk13Data
{
public:
    Progress_tmk13();
    ~Progress_tmk13();

    QStringList getSettings();
    bool setSettings(QStringList settigns);
    QStringList getPropertyData();

    bool makeDataToComand(CommandController::sCommandData &commandData);
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData);

    QList<int> getChart();

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
    #endif

//    Progress_tmk13Data::T_calibrationTable calibrationTable;
//    uint32_t passwordHash;
//    uint8_t newSerialNumber[SERIALNUMBER_STRING_SIZE];
//    uint8_t personalDataBuff[PERSONAL_DATA_SIZE];
//    QString version;
//    QString cpuId;
//    uint32_t cnt;
//    Progress_tmk13Data::T_settings newSettings;

    QList<CommandController::sCommandData> getCommandListToIdlePoll(QString deviceIdent, int deviceIdentId);

private:
    S_lls_data lls_data;
    QList<int> *chartData;
};

#endif // Progress_tmk13_H
