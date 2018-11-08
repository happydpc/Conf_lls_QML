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

    static constexpr char* logHeaderBegind = {"\\02\\"};
    static constexpr char* logHeaderEnd = {"\\03\\"};
    static constexpr char* logCommandBegind = {"\\A0\\"};
    static constexpr char* logCommandEnd = {"\\Y9\\"};

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
        E_ConsoleCommandType_getAccelConfig,
        E_ConsoleCommandType_getNetworkConfig,
        E_ConsoleCommandType_getIsReadyCommand,
        E_ConsoleCommandType_getSecurityData,
        // current data
        E_ConsoleCommandType_getOtherData,
        E_ConsoleCommandType_getAccelData,
        E_ConsoleCommandType_getNetworkData,
        E_ConsoleCommandType_getCardData,
        E_ConsoleCommandType_getBatteryData,
        // set conf
        E_ConsoleCommandType_setSecurityData,
        E_ConsoleCommandType_setAccelConfig,
        E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint,
        E_ConsoleCommandType_setNetworkConfig,
        E_ConsoleCommandType_setBatteryNewAccum
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
        char clientToken[32];       // TCP_CLIENT_CONF_AUTH_TOKEN - "default-token"
        char clientUserName[32];    // TCP_CLIENT_CONF_USERNAME - "nozzletag"
        char serverIp[46];          // TCP_CLIENT_CONF_SERVER_IP_ADDR "fd00::1"
        uint16_t serverPort;        // TCP_CLIENT_CONF_SERVER_PORT 21000
        uint32_t panid;
    }sNetworkConfig;

    typedef struct {
        char networkCurrentIp[64];
        bool status;
        int rssi;
    }sNetworkData;

    typedef struct {
    }sCardConfig;

    typedef struct {
        int status;
        char cardNumber[64];
        uint16_t len;
    }sCardData;

    typedef struct {
    }sBatteryConfig;

    typedef struct {
        float powerVoltage;
        float powerCurrent;
        // тока потребленно
        float powerCurrentAccumulate_mA;
        // ресурс осталось
        float  powerCurrentResouresAvailable_mA;
    }sBatteryData;

    typedef struct {
        int x;
        int y;
        int z;
    }sAccelData;

    typedef struct {
        char version[32];
    }sOtherData;

    typedef struct {
        int thresholdX;
        int thresholdY;
        int thresholdZ;
        int delta;
    }sAccelConfig;

    typedef struct {
        bool passwordIsUsed;
        char password[64];
    }sSecurity;
#pragma pack()

#pragma pack(1)
    // raw settings
    typedef struct {
        sCardConfig cardConfig;
        sNetworkConfig netConfig;
        sAccelConfig accelConfig;
        sBatteryConfig batConfig;
        sSecurity security;
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
        sValue powerCurrent;
        sValueText powertypeBattery;
        // тока потребленно
        sValue powerCurrentAccumulate_mA;
        // ресурс осталось
        sValue powerCurrentResouresAvailable_mA;

        sValue temperature;

        sValue accelX;
        sValue accelY;
        sValue accelZ;
        sValue accelThresholdX;
        sValue accelThresholdY;
        sValue accelThresholdZ;
        sValue accelDelta;

        struct {
            sValue passwordIsUsed;
            sValueText password;
        }security;

        sValueText versionFirmware;

        sValueText networkCurrentIp;
        sValue rssi;
        sValue networkState;

        sValueText cardNumber;
        sValue cardState;

        struct {
            QString clientToken;
            QString clientUserName;
            QString serverIp;
            uint16_t serverPort;
            uint32_t panid;
            bool isValid;
        }networkConfig;
    }S_dev_data;
};

#endif // Nozzle_Revision_0_00_Oct_2018_Data_H
