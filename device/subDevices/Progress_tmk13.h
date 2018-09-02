#ifndef  Progress_tmk13_H
#define  Progress_tmk13_H

#include <QObject>
#include <QVector>
#include "Progress_tmk13Data.h"
#include "command/commandController.h"

#define USE_TEST_DEV_REPLY  1

class Progress_tmk13 : public Progress_tmk13Data
{
public:
    Progress_tmk13();
    ~Progress_tmk13();

    QStringList getSettings();
    bool setSettings(QStringList settigns);
    QStringList getCurrentData();

    bool makeDataToComand(CommandController::sCommandData &commandData);
    bool placeDataReplyToCommand(QByteArray &commandArrayReplyData);

#ifdef USE_TEST_DEV_REPLY
    bool makeDataRequestReply(QByteArray request, QByteArray &reply);
    uint16_t getFuel();
    uint16_t getFrequency();
    int8_t getTemperature();

    uint16_t fuel;
    uint16_t freq;
    int8_t temp;

    #define SERIALNUMBER_STRING_SIZE    12
    #define PERSONAL_DATA_SIZE          176
    #define VERSION_STRING_SIZE         8
    #define CPU_ID_SIZE                 12
    #define DUT_TYPE                    13
    T_settings settings;
    uint8_t serialNumber[64];
    uint8_t personalData[64];
    Progress_tmk13Data::T_calibrationTable calibrationTable;
    uint32_t passwordHash;
    uint8_t newSerialNumber[SERIALNUMBER_STRING_SIZE];
    uint8_t personalDataBuff[PERSONAL_DATA_SIZE];
    QString version;
    QString cpuId;
    uint32_t cnt;
    Progress_tmk13Data::T_settings newSettings;
#endif
    QList<CommandController::sCommandData> getCommandListToIdlePoll(QString deviceIdent, int deviceIdentId);

private:
    S_lls_data lls_data;
};

#endif // Progress_tmk13_H
