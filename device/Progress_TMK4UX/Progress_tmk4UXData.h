#ifndef Progress_tmk4UXData_H
#define Progress_tmk4UXData_H

#include <QObject>

class Progress_tmk4UXData : public QObject
{
    Q_OBJECT
public:

    Progress_tmk4UXData();
    ~Progress_tmk4UXData();

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
};

#endif // Progress_tmk4UXData_H
