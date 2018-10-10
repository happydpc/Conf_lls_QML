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
        E_ConsoleCommandType_getAccelData,
        E_ConsoleCommandType_getNetworkData,
        E_ConsoleCommandType_getCardProperty,
        E_ConsoleCommandType_getBatteryProperty,
        // set conf
        E_ConsoleCommandType_setNetworkPassword,
        E_ConsoleCommandType_setAccelConfig,
        E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint,
        E_ConsoleCommandType_setNetworkConfig
    }eConsoleCommandType;

    typedef enum {
        E_ConsoleMode_log,
        E_ConsoleMode_configuring
    }eConsoleMode;

    // eTypeData;
    const uint8_t eTypeData_integer = 0;
    const uint8_t eTypeData_string = 1;

#pragma pack(1)
    typedef struct {
        uint32_t versionProtocol;
        uint32_t devieIcdent;
        uint8_t commandType; //eConsoleCommandType
        uint8_t argCount;
        struct {
            uint8_t typeData; //eTypeData
            union {
                uint32_t data_uint32;
                char data_string[32];
            }data_union;
        }dataArg[CONSOLE_COMMAND_MAX_ARGS];
        uint16_t magic_word;
    }sConsoleBufData;
#pragma pack()

#pragma pack(1)
    typedef struct{
        uint32_t versionProtocol;
        uint32_t deviceIdent;
        uint8_t commandType; // eConsoleCommandType
        uint8_t data[128];
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
        uint8_t password[PASSWORD_SIZE];
    }T_settings;
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

        sValue temperature;

        sValue accelX;
        sValue accelY;
        sValue accelZ;

        sValue accelConfX;
        sValue accelConfY;
        sValue accelConfZ;
        sValue accelConfDelta;

        sValueText networkParentIp;
        sValue rssi;
        sValue networkState;

        sValueText networkPassword;

        sValueText cardNumber;
        sValue cardState;

        struct {
            struct {
                T_settings value;
                bool isValid;
            }get;
        }settings;
    }S_dev_data;
};

#endif // Nozzle_Revision_0_00_Oct_2018_Data_H
