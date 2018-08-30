#ifndef PROGRESS_TMK324DATA_H
#define PROGRESS_TMK324DATA_H

#include <QObject>

class Progress_tmk324Data : public QObject
{
    Q_OBJECT
public:
    Progress_tmk324Data();
    ~Progress_tmk324Data();

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
        lls_run_application		=	0x6A,
        lls_download_settings	=	0x6B,
        lls_upload_settings		=	0x6C,
        lls_clear_settings		=	0x6D,
        lls_flash_unprotect		=	0x6F
    }E_type_operation;

    //    typedef enum {
    //        type_lls_tmk24 =  1,
    //        type_lls_tmk2u1 = 2,
    //        type_lls_tmk4ux = 13,
    //    }E_type_lls;

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
#pragma pack()
};

#endif // PROGRESS_TMK324DATA_H
