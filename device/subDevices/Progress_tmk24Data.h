#ifndef PROGRESS_TMK24DATA_H
#define PROGRESS_TMK24DATA_H

#include <QObject>

#define SERIALNUMBER_STRING_SIZE            12
#define PERSONAL_DATA_SIZE                  176
#define FIRMWARE_VERSION_STRING_SIZE         8
#define CPU_ID_SIZE                         12
#define DUT_TYPE                            13
#define PASSWORD_SIZE                       8
#define TAR_TABLE_SIZE                      30

class Progress_tmk24Data : public QObject
{
    Q_OBJECT
public:

    Progress_tmk24Data();
    ~Progress_tmk24Data();

    typedef enum {
        param_id_address = 1,
        param_comamnd = 2,
        param_password_session = 3
    }E_param_suquence;

    typedef enum {
        type_lls_tmk24 =  1,
        type_lls_tmk2u1 = 2,
        type_lls_tmk4ux = 13,
    }E_type_lls;

    typedef enum {
        lls_read_lvl_once =         0x06,
        lls_send_data_enable =      0x07,
        lls_set_send_time =         0x13,
        lls_send_data_default =     0x17,
        lls_read_cnt =              0xf7,
        lls_read_lvl_all =          0x46,
        lls_read_settings =         0x47,
        lls_write_settings =        0x48,
        lls_read_cal_table =        0x26,
        lls_write_cal_table =       0x27,
        lls_calibrate_min =         0x08,
        lls_calibrate_max =         0x09,
        lls_read_errors =           0x30,
        lls_set_serial_number =     0x33,
        lls_read_serial_number =    0x32,
        lls_set_personal =          0x43,
        lls_read_personal =         0x42,
        lls_set_new_password =      0x16,
        lls_check_address_and_pass= 0x74,
        lls_run_bootloader =        0x67,
        lls_download_application = 	0x68,
        lls_upload_application	=	0x69,
        lls_run_applicapassword_sessiontion		=	0x6A,
        lls_download_settings	=	0x6B,
        lls_upload_settings		=	0x6C,
        lls_clear_settings		=	0x6D,
        lls_flash_unprotect		=	0x6F
    }E_type_operation;

#pragma pack(1)
    typedef struct {
        uint32_t cntEmpty;
        uint32_t cntFull;
        uint8_t netAddress;
        uint8_t periodicSendType; // T_DataSend
        uint8_t periodicSendTime;
        uint16_t minLevel;
        uint16_t maxLevel;
        uint8_t outputValue;
        uint8_t filterType;
        uint8_t avarageLength;
        uint8_t medianLength;
        float q;
        float r;
        uint8_t thermoCompensationType;
        float k1;
        float k2;
        uint8_t interpolationType;
        uint8_t rs232Speed;
        uint8_t rs485Speed;
        uint8_t masterMode; // T_MasterMode
        uint8_t slaveCount;
        uint8_t slaveAddr[4];
        uint8_t waterMode;
        uint8_t reserved;
    }T_settings;

    typedef struct {
        uint8_t NotCalibrated:1;//10%
        uint8_t MaxFreqOut:1;//10%
        uint8_t MinFreqOut:1;//10%
        uint8_t GenFreq0:1;
        uint8_t Slave1Error:1;
        uint8_t Slave2Error:1;
        uint8_t Slave3Error:1;
        uint8_t Slave4Error:1;
        uint8_t QeueManagerError:1;
        uint8_t Rs232Error:1;
        uint8_t Rs485Error:1;
        uint8_t ReplayNotComeRs232:1;
        uint8_t ReplayNotComeRs485:1;
    }T_errors;

    typedef struct {
        uint8_t TableSize;
        uint16_t x[TAR_TABLE_SIZE];
        uint16_t y[TAR_TABLE_SIZE];
    }T_calibrationTable;

    typedef struct {
        uint8_t slave_count;
        uint16_t summed_volume;
        uint16_t send_value;
        uint16_t Level[4];
        uint16_t Frequency[4];
        int8_t Temperature[4];
        uint8_t ActualFlag[4]; //if lost frame then 1!
    }T_dutValues;
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
    }sValue;

    typedef struct {
        bool isValid;
        QString value;
    }sValueText;

    typedef struct {
        sValue cnt;
        sValue fuelLevel;
        sValue fuelProcent;
        sValue freq;
        sValue temp;
        sValueText serialNum;
        sValueText firmware;

        struct {
            struct {
                sValueText value;
                bool authIsNormal;
            }get;
            sValueText set;
            sValueText session;
        }password;

        struct {
            struct {
                T_settings value;
                bool isValid;
            }get;
        }settings;

        struct {
            T_errors errors;
            bool isValid;
        }errors;

        struct {
            struct {
                T_calibrationTable table;
                bool isValid;
            }get;
        }calibrateTable;

        struct{
            T_dutValues values;
            bool isValid;
        }llssValues;

        bool typeIsValid;

    }S_lls_data;
};

#endif // PROGRESS_TMK24DATA_H
