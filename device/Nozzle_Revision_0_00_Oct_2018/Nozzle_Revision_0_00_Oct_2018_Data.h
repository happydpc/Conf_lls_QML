#ifndef Nozzle_Revision_0_00_Oct_2018_Data_H
#define Nozzle_Revision_0_00_Oct_2018_Data_H

#include <QObject>
#include <QList>

class Nozzle_Revision_0_00_Oct_2018_Data : public QObject
{
    Q_OBJECT
public:

    Nozzle_Revision_0_00_Oct_2018_Data();
    ~Nozzle_Revision_0_00_Oct_2018_Data();

    static constexpr char* logHeaderBegind = "\02\<";
    static constexpr char* logHeaderEnd = "\03\>";
    static constexpr char* logCommandBegind = "A<";
    static constexpr char* logCommandEnd = "B>";

    static constexpr int SERIALNUMBER_STRING_SIZE            = 12;
    static constexpr int PERSONAL_DATA_SIZE                  = 176;
    static constexpr int FIRMWARE_VERSION_STRING_SIZE        = 8;
    static constexpr int CPU_ID_SIZE                         = 12;
    static constexpr int DUT_TYPE                            = 13;
    static constexpr int PASSWORD_SIZE                       = 32;
    static constexpr int TAR_TABLE_SIZE                      = 30;
    static constexpr int MAX_SIZE_HISTORY_CNT_LIST           = 10;
    static constexpr int CONSOLE_COMMAND_MAX_ARGS            = 5;
    static constexpr int CONSOLE_MAGIC_WORD                  = 0x1297;
    static constexpr int CONSOLE_DEVICE_IDENT                = 0x0012;
    static constexpr int CONSOLE_VERSION_PROTOCOL            = 0x0001;

    typedef enum {
        E_ConsoleCommandType_EmptyCommand,
        // init
        E_ConsoleCommandType_getPassword,
        E_ConsoleCommandType_getAccelConfig,
        E_ConsoleCommandType_getNetworkConfig,
        E_ConsoleCommandType_getIsReadyCommand,
        // current data
        E_ConsoleCommandType_getOtherData,
        E_ConsoleCommandType_getAccelData,
        E_ConsoleCommandType_getNetworkData,
        E_ConsoleCommandType_getCardData,
        E_ConsoleCommandType_getBatteryData,
        // set conf
        E_ConsoleCommandType_setPassword,
        E_ConsoleCommandType_setAccelConfig,
        E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint,
        E_ConsoleCommandType_setNetworkConfig
    }eConsoleCommandType;

#pragma pack(1)
typedef struct {
    uint32_t versionProtocol;
    uint32_t deviceIdent;
    uint8_t commandType; // eConsoleCommandType - warning size 4 bytes!
    struct {
        char data[128];
    }data;
    uint16_t magic_word;
}sConsoleBufData;

typedef struct{
    uint32_t versionProtocol;
    uint32_t deviceIdent;
    uint8_t commandType; // eConsoleCommandType - warning size enum 4 bytes!
    struct {
        char data[128];
    }data;
    uint16_t magic_word;
}sConsoleReplyBuff;
#pragma pack()

#pragma pack(1)
    typedef struct {
        uint8_t mode; // eConsoleMode
        bool isReadyNextCommand;
        struct {
            uint8_t pbuf[sizeof(sConsoleBufData)];
            uint16_t len;
        }raw_buf_input;

        struct {
            uint8_t pbuf[sizeof(sConsoleReplyBuff)];
        }raw_buf_out;
    }sConsole;
#pragma pack()

#pragma pack(1)
    typedef struct {
    }sCardConfig;

    typedef struct {
    }sBatteryConfig;

    typedef struct {
        char networkPassword[64];
    }sNetworkConfig;

    typedef struct {
        int thresholdX;
        int thresholdY;
        int thresholdZ;
        int delta;
    }sAccelConfig;

    typedef struct {
        char password[64];
    }sPasswordConfig;
#pragma pack()

#pragma pack(1)

    typedef struct {
        sCardConfig cardConfig;
        sNetworkConfig netConfig;
        sPasswordConfig passConfig;
        sAccelConfig accelConfig;
        sBatteryConfig batConfig;
        uint16_t magic_word;
    }Nozzle_config_t;
#pragma pack()

    typedef struct {
        bool isValid;
        union {
            float value_f;
            double value_d;
            int value_i;
            uint32_t value_u32;
            uint16_t value_u16;
        }value;
        QList<uint32_t>history;
    }sValue;

    typedef struct {
        bool isValid;
        QString value;
    }sValueText;

    typedef struct {
        sValue powerVoltage;
        sValueText powertypeBattery;
        // тока потребленно
        sValue powerCurrentAccumulate;
        // тока потребленно (часов)
        sValue powerCurrentAccumulateHourse;
        // ресурс осталось (часов)
        sValue powerCurrentResouresAvailable;
        sValue powerCurrentResouresAvailableHourse;
        sValue powerCurrent;

        sValue temperature;

        sValue accelX;
        sValue accelY;
        sValue accelZ;

        sValueText versionFirmware;

        sValueText networkParentIp;
        sValue rssi;
        sValue networkState;

        sValueText networkPassword;

        sValueText cardNumber;
        sValue cardState;

        struct {
            struct {
                Nozzle_config_t value;
                bool isValid;
            }get;
        }settings;
    }S_dev_data;
};

#endif // Nozzle_Revision_0_00_Oct_2018_Data_H
