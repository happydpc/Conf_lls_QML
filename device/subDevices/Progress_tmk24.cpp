#include <QDebug>
#include "Progress_tmk24.h"
#include "other/crc.h"

Progress_tmk24::Progress_tmk24(QString uniqIdentId, QString passwordSession) {
    this->chartData = new QList<int>();
    this->uniqIdentId = uniqIdentId;
    this->state = STATE_DISCONNECTED;
    this->lls_data.password.session.value = passwordSession;
    this->lls_data.password.session.isValid = true;
    setDefaultValues();
}

Progress_tmk24::~Progress_tmk24() {

}

QString Progress_tmk24::getDevTypeName() {
    return QString::fromLocal8Bit(Progress_tmk24::name, strlen(Progress_tmk24::name));
}

void Progress_tmk24::setDefaultValues() {
    this->settings.k1 = 0;
    this->settings.k2 = 0;
    this->settings.netAddress = uniqIdentId.toInt();
    this->settings.thermoCompensationType = 0;
    this->settings.periodicSendType = 0;
    this->settings.periodicSendTime = 0;
    this->settings.outputValue = 0;
    this->settings.filterType = 0;
    this->settings.interpolationType = 0;
    this->settings.minLevel = 0;
    this->settings.maxLevel = 4095;
    this->settings.masterMode = 0x00;
    this->settings.rs232Speed = 3;
    this->settings.rs485Speed = 3;
    this->settings.slaveCount = 0;
    this->settings.slaveAddr[0] = 2;
    this->settings.slaveAddr[1] = 3;
    this->settings.slaveAddr[2] = 4;
    this->settings.slaveAddr[3] = 5;
    this->settings.avarageLength = 21;
    this->settings.medianLength = 7;
    this->settings.q = 0.001;
    this->settings.r = 5000;
    this->lls_data.serialNum.isValid = false;
    this->calibrationTable.TableSize = 0;
    memset(this->calibrationTable.x,0, sizeof(this->calibrationTable.x));
    memset(this->calibrationTable.y,0, sizeof(this->calibrationTable.y));
    this->newSettings = this->settings;
    this->lls_data.fuelLevel.isValid = false;
    this->lls_data.freq.isValid = false;
    this->lls_data.temp.isValid = false;
    this->lls_data.cnt.isValid = false;
    this->lls_data.firmware.isValid = false;
    this->lls_data.typeIsValid = false;
}

QList<int> Progress_tmk24::getChart() {
    return *chartData;
}

// TODO: is valid handler!
QStringList Progress_tmk24::getPropertyData() {
    QStringList res;
    res << lls_data.serialNum.value;
    res << QString::number(settings.netAddress);
    res << getDevTypeName();
    res << lls_data.firmware.value;
    res << QString::number(lls_data.password.get.isValid);
    res += getSettings();
    return res;
}

QStringList Progress_tmk24::getCurrentData() {
    QList<QString> res;
    res << QString::number(lls_data.fuelLevel.value.value_u32);
    res << QString::number(lls_data.fuelProcent.value.value_u16);
    res << QString::number(lls_data.cnt.value.value_u32);
    res << QString::number(lls_data.freq.value.value_u16);
    res << QString::number(lls_data.temp.value.value_i);
    return res;
}

QStringList Progress_tmk24::getSettings() {
    QStringList ret;
    if(lls_data.settings.get.isValid) {
        ret << getDevTypeName();
        ret << QString::number(lls_data.settings.get.value.k1, 'f');
        ret << QString::number(lls_data.settings.get.value.k2, 'f');
        ret << QString::number(lls_data.settings.get.value.thermoCompensationType);
        ret << QString::number(lls_data.settings.get.value.periodicSendType);
        ret << QString::number(lls_data.settings.get.value.periodicSendTime);
        ret << QString::number(lls_data.settings.get.value.outputValue);
        ret << QString::number(lls_data.settings.get.value.interpolationType);
        ret << QString::number(lls_data.settings.get.value.filterType);
        ret << QString::number(lls_data.settings.get.value.medianLength);
        ret << QString::number(lls_data.settings.get.value.avarageLength);
        ret << QString::number(lls_data.settings.get.value.q, 'f');
        ret << QString::number(lls_data.settings.get.value.r, 'f');
        ret << QString::number(lls_data.settings.get.value.minLevel);
        ret << QString::number(lls_data.settings.get.value.maxLevel);
        ret << QString::number(lls_data.settings.get.value.rs232Speed);
        ret << QString::number(lls_data.settings.get.value.rs485Speed);
        ret << QString::number(lls_data.settings.get.value.slaveCount);
        ret << QString::number(lls_data.settings.get.value.slaveAddr[0]);
        ret << QString::number(lls_data.settings.get.value.slaveAddr[1]);
        ret << QString::number(lls_data.settings.get.value.slaveAddr[2]);
        ret << QString::number(lls_data.settings.get.value.slaveAddr[3]);
    }
    return ret;
}

void Progress_tmk24::setSettings(QStringList &settings) {

}

QStringList Progress_tmk24::getErrors() {
    QStringList ret;
    if(lls_data.errors.isValid) {
        ret << QString::number(lls_data.errors.errors.GenFreq0);
        ret << QString::number(lls_data.errors.errors.MaxFreqOut);
        ret << QString::number(lls_data.errors.errors.MinFreqOut);
        ret << QString::number(lls_data.errors.errors.NotCalibrated);
        ret << QString::number(lls_data.errors.errors.QeueManagerError);
        ret << QString::number(lls_data.errors.errors.ReplayNotComeRs232);
        ret << QString::number(lls_data.errors.errors.ReplayNotComeRs485);
        ret << QString::number(lls_data.errors.errors.Rs232Error);
        ret << QString::number(lls_data.errors.errors.Rs485Error);
        ret << QString::number(lls_data.errors.errors.Slave1Error);
        ret << QString::number(lls_data.errors.errors.Slave2Error);
        ret << QString::number(lls_data.errors.errors.Slave3Error);
        ret << QString::number(lls_data.errors.errors.Slave4Error);
    }
    return ret;
}

DeviceAbstract::E_State Progress_tmk24::getState() {
    return state;
}

void Progress_tmk24::setState(DeviceAbstract::E_State value) {
    state = value; // если дисконектим или сбрасываем - тогда сбрасываем и данные
    if((state == DeviceAbstract::STATE_DISCONNECTED) || (state == DeviceAbstract::STATE_START_INIT)) {
        setDefaultValues();
    }
}

QString Progress_tmk24::getUniqIdent() {
    return uniqIdentId;
}

bool Progress_tmk24::makeDataToCommand(CommandController::sCommandData &commandData) {
    bool res = false;
    if(!commandData.deviceIdent.isEmpty()) {
        try {
            commandData.commandOptionData.push_back(0x31);
            // id addr
            commandData.commandOptionData.push_back(commandData.deviceIdent.toInt());
            // command byte
            commandData.commandOptionData.push_back(commandData.devCommand);
            switch(commandData.devCommand) {
            case Progress_tmk24Data::lls_read_lvl_once: break;
            case Progress_tmk24Data::lls_send_data_enable: break;
            case Progress_tmk24Data::lls_set_send_time: break;
            case Progress_tmk24Data::lls_send_data_default: break;
            case Progress_tmk24Data::lls_read_cnt: break;
            case Progress_tmk24Data::lls_read_lvl_all: break;
            case Progress_tmk24Data::lls_read_settings: break;

            case Progress_tmk24Data::lls_write_settings: {
                // сперва заносим текущий пароль для разрешения доступа
                //                QString password = QString::fromUtf8(commandArg.Progress_tmk24::E_param_suquence::param_password_session), 0);
                //                for(uint8_t i=0; i<sizeof(password_session); i++) {
                //                    array.push_back(password_session[i]);
                //                }
                //                array.push_back(0xFF);
                //                array.push_back(0xFF);
                //                array.insert(13, (char*)&tcommand.data.settings_new, sizeof(T_settings));
                //                while(array.size() != 62) {
                //                    array.push_back(0xFF);
                //                }
            }
                break;

            case Progress_tmk24Data::lls_read_cal_table:
                break;

            case Progress_tmk24Data::lls_write_cal_table: {
            }
                break;
            case Progress_tmk24Data::lls_calibrate_min:
            case Progress_tmk24Data::lls_calibrate_max: {
                // заносим текущий пароль для разрешения доступа
                // значение заносится в самоме датчике
                QByteArray passArray;
                if(lls_data.password.session.isValid) {
                    if(!lls_data.password.session.value.isEmpty()) {
                        int passLen = lls_data.password.session.value.length();
                        for(int passCounter=0; passCounter<passLen; passCounter++) {
                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
                        }
                    }
                }
                while(passArray.size() < PASSWORD_SIZE) {
                    passArray.push_back((char)0);
                }
                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
            }
                break;
            case Progress_tmk24Data::lls_read_errors: break;
            case Progress_tmk24Data::lls_set_serial_number: break;
            case Progress_tmk24Data::lls_read_serial_number: break;
            case Progress_tmk24Data::lls_set_personal: break;
            case Progress_tmk24Data::lls_read_personal: break;
            case Progress_tmk24Data::lls_set_new_password: {
                if(!commandData.commandOptionData.isEmpty()) {
                    //                // сперва заносим текущий пароль для разрешения доступа
                    //                for(uint8_t i=0; i<sizeof(password_session); i++) {
                    //                    array.push_back(password_session[i]);
                    //                }
                    //                // потом новый пароль
                    //                for(uint8_t i=0; i<sizeof(password_session); i++) {
                    //                    array.push_back(tcommand.data.new_passw[i]);
                    //                }
                }
            }
                break;

            case Progress_tmk24Data::lls_check_address_and_pass: {
                // заносим текущий пароль для разрешения доступа
                // значение заносится в самоме датчике
                QByteArray passArray;
                if(lls_data.password.session.isValid) {
                    if(!lls_data.password.session.value.isEmpty()) {
                        int passLen = lls_data.password.session.value.length();
                        for(int passCounter=0; passCounter<passLen; passCounter++) {
                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
                        }
                    }
                }
                while(passArray.size() < PASSWORD_SIZE) {
                    passArray.push_back((char)0);
                }
                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
            }
                break;
            case Progress_tmk24Data::lls_run_bootloader: break;
            default : break;
            }
            Crc crcCalc;
            uint8_t crcResult = 0;
            crcResult = crcCalc.crc8_dallas(commandData.commandOptionData.data(), commandData.commandOptionData.length());
            commandData.commandOptionData.push_back(crcResult);
            res = true;
        } catch(...) {
            qDebug("Device: makeDataToCommand -catch!");
        }
    } else {
        qDebug() << "Device: makeDataToCommand paramIsNull!";
    }
    return res;
}

bool Progress_tmk24::placeDataReplyToCommand(QByteArray &commandArrayReplyData, bool isNeedMessageAboutExecuted) {
    bool res = false;
    uint8_t crcCalcResult = 0;
    uint16_t frequency = 0;
    uint16_t value = 0;
    Crc *crc = new Crc();

    // if gived reply with data - device CONNECTED
    if(!commandArrayReplyData.isEmpty()) {
        if(getState() == STATE_DISCONNECTED) {
            setState(DeviceAbstract::STATE_START_INIT); // после этой команды настройки уже считаны
            emit eventDevice(DeviceAbstract::Type_DeviceEvent_Connected, getUniqIdent(), QString("Connected"));
        }
        //-- caculate crc
        crcCalcResult = crc->crc8_dallas(commandArrayReplyData.data(),
                                         commandArrayReplyData.length()-1);
        //-- if result crc is valid
        if(crcCalcResult == (0xff & commandArrayReplyData.at(
                                 commandArrayReplyData.length()-1))) {
            //-- byte is command
            switch(commandArrayReplyData.at(2)) {
            case Progress_tmk24Data::lls_read_lvl_once: {
                if(lls_data.typeIsValid) {
                    lls_data.temp.value.value_i = (int8_t)(0xFF & commandArrayReplyData.at(3));
                    lls_data.temp.isValid = true;
                    value = 0xFF & commandArrayReplyData.at(5);
                    value = value << 8;
                    value |= 0xFF & commandArrayReplyData.at(4);
                    frequency = 0xFF & commandArrayReplyData.at(7);
                    frequency = frequency << 8;
                    frequency |= 0xFF & commandArrayReplyData.at(6);
                    lls_data.fuelLevel.value.value_u32 = value;
                    if(lls_data.settings.get.isValid) {
                        lls_data.fuelProcent.value.value_u32 = ((float)((float)value/lls_data.settings.get.value.maxLevel)*100);
                    } else {
                        lls_data.fuelProcent.value.value_u32 = 0;
                    }
                    lls_data.fuelLevel.isValid = true;
                    lls_data.freq.value.value_u32  = frequency;
                    lls_data.freq.isValid = true;
                    // TODO: random ok?
                    chartData->push_back(lls_data.fuelLevel.value.value_u32 + (rand()%1));
                    while(chartData->size() > 50) {
                        chartData->pop_front();
                    }
                    emit eventDevice(DeviceAbstract::Type_DeviceEvent_CurrentDataUpdated, getUniqIdent(), QString("Ready current data"));
                    res = true;
                }
            }
                break;
            case Progress_tmk24Data::lls_send_data_enable: break;
            case Progress_tmk24Data::lls_set_send_time: break;
            case Progress_tmk24Data::lls_send_data_default: break;
            case Progress_tmk24Data::lls_read_lvl_all: {
                if(lls_data.typeIsValid) {
                    lls_data.llssValues.values.slave_count = (0xFF & commandArrayReplyData.at(3));
                    lls_data.llssValues.values.summed_volume = (0xFF & commandArrayReplyData.at(5));
                    lls_data.llssValues.values.summed_volume = lls_data.llssValues.values.summed_volume << 8;
                    lls_data.llssValues.values.summed_volume |= (0xFF & commandArrayReplyData.at(4));
                    //
                    lls_data.llssValues.values.send_value = 0xFF & commandArrayReplyData.at(8);
                    lls_data.llssValues.values.send_value = lls_data.llssValues.values.send_value << 8;
                    lls_data.llssValues.values.send_value |= (0xFF & commandArrayReplyData.at(7));
                    //
                    int offset_counter = 11;
                    for(uint8_t i=0; i<4; i++) {
                        lls_data.llssValues.values.Temperature[i] = (int8_t)(0xFF & commandArrayReplyData.at(offset_counter));
                        offset_counter++;
                        //--
                        lls_data.llssValues.values.Level[i] = 0xFF & commandArrayReplyData.at(offset_counter);
                        offset_counter++;
                        //--
                        lls_data.llssValues.values.Level[i] |= (0xFF & commandArrayReplyData.at(offset_counter)) << 8;
                        offset_counter++;
                        //--
                        lls_data.llssValues.values.Frequency[i] = 0xFF & commandArrayReplyData.at(offset_counter);
                        lls_data.llssValues.values.Frequency[i] = lls_data.llssValues.values.Frequency[i] << 8;
                        offset_counter++;
                        lls_data.llssValues.values.Frequency[i] |= (0xFF & commandArrayReplyData.at(offset_counter));
                        lls_data.llssValues.values.Frequency[i] = lls_data.llssValues.values.Frequency[i] << 8;
                        offset_counter++;
                    }
                    lls_data.llssValues.isValid = true;
                }
                res = true;
            }
                break;

            case Progress_tmk24Data::lls_read_settings: {
                if(commandArrayReplyData.size() > 22) {
                    char *pbuf = (commandArrayReplyData.data() + 4);
                    lls_data.serialNum.value = QString::fromUtf8(pbuf, SERIALNUMBER_STRING_SIZE);

                    pbuf = (commandArrayReplyData.data() + 4 + SERIALNUMBER_STRING_SIZE);
                    lls_data.firmware.value = QString::fromUtf8(pbuf,  FIRMWARE_VERSION_STRING_SIZE);

                    // проверка типа
                    if(commandArrayReplyData.at(3) != Progress_tmk24Data::type_lls_tmk24) {
                        lls_data.typeIsValid = false;
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_TypeError, getUniqIdent(), QString("Type Error!"));
                    } else { // TODO: is valid conversion?
                        lls_data.typeIsValid = true;
                        Progress_tmk24Data::T_settings *pSettings = (Progress_tmk24Data::T_settings*)(commandArrayReplyData.data() + 34);
                        if(pSettings->netAddress == commandArrayReplyData.at(Progress_tmk24Data::param_id_address)) {
                            lls_data.settings.get.value = *pSettings;
                            lls_data.settings.get.isValid = true;
                        }
                        if(isNeedMessageAboutExecuted) {
                            emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_read_settings"));
                        }
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_ReadyReadProperties, getUniqIdent(), QString("Ready read properties"));
                    }
                    res = true;
                }
            }
                break;

            case Progress_tmk24Data::lls_write_settings:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 4) {
                        if(commandArrayReplyData.at(3) == 0) {
                            if(isNeedMessageAboutExecuted) {
                                emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_write_settings"));
                            }
                            res = true;
                        }
                    }
                }
                break;

            case Progress_tmk24Data::lls_read_cal_table: {
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 45) {
                        memset(&lls_data.calibrateTable.get.table, 0, sizeof(Progress_tmk24Data::T_calibrationTable));
                        lls_data.calibrateTable.get.table.TableSize = commandArrayReplyData.at(3);
                        int index = 0;
                        for(int i=0; i<lls_data.calibrateTable.get.table.TableSize; i++) {
                            lls_data.calibrateTable.get.table.x[i] = (0xFF & commandArrayReplyData.at(index+4));
                            index++;
                            lls_data.calibrateTable.get.table.x[i] |= ((0xFF & commandArrayReplyData.at(index+4)) << 8);
                            index++;
                            lls_data.calibrateTable.get.table.y[i] = (0xFF & commandArrayReplyData.at(index+4));
                            index++;
                            lls_data.calibrateTable.get.table.y[i] |= ((0xFF & commandArrayReplyData.at(index+4)) << 8);
                            index++;
                        }
                        lls_data.calibrateTable.get.isValid = true;
                        if(isNeedMessageAboutExecuted) {
                            emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_read_cal_table"));
                        }
                        res = true;
                    }
                }
            }
                break;

            case Progress_tmk24Data::lls_write_cal_table:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 4) {
                        if(commandArrayReplyData.at(3) == 0) {
                            if(isNeedMessageAboutExecuted) {
                                emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_write_cal_table"));
                            }
                            res = true;
                        }
                    }
                }
                break;
            case Progress_tmk24Data::lls_calibrate_min:
                if(commandArrayReplyData.size() > 3) {
                    if(commandArrayReplyData.at(3) == 0) {
                        if(isNeedMessageAboutExecuted) {
                            emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_calibrate_min"));
                        }
                        res = true;
                    } else {
                        // TODO: обработка ошибки
                    }
                }
                break;

            case Progress_tmk24Data::lls_calibrate_max:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 3) {
                        if(commandArrayReplyData.at(3) == 0) {
                            if(isNeedMessageAboutExecuted) {
                                emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_calibrate_max"));
                            }
                            res = true;
                        } else {
                            // TODO: обработка ошибки
                        }
                    }
                }
                break;

            case Progress_tmk24Data::lls_read_errors:
            {
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 5) { // TODO: 10?
                        Progress_tmk24Data::T_errors t_erros;
                        memcpy(&t_erros, (commandArrayReplyData.data() + 3), sizeof(t_erros));
                        memcpy(&lls_data.errors, &t_erros, sizeof(lls_data.errors));
                        if(isNeedMessageAboutExecuted) {
                            emit eventDevice(DeviceAbstract::Type_DeviceEvent_ExectCustomCommandNorlal, getUniqIdent(), QString("lls_read_errors"));
                        }
                        lls_data.errors.isValid = true;
                        res = true;
                    }
                }
            }
                break;
            case Progress_tmk24Data::lls_set_serial_number: break;
            case Progress_tmk24Data::lls_read_serial_number: {
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 22) {
                        lls_data.serialNum.value = QString::fromUtf8((commandArrayReplyData.data() + 3),
                                                                     SERIALNUMBER_STRING_SIZE);
                        lls_data.serialNum.isValid = true;
                    }
                    res = true;
                }
            }
                break;

            case Progress_tmk24Data::lls_set_personal: break;
            case Progress_tmk24Data::lls_read_personal: break;
            case Progress_tmk24Data::lls_set_new_password:
                if(commandArrayReplyData.size() >= 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        if(isNeedMessageAboutExecuted) {

                        }
                        res = true;
                    }
                }
                break;

            case Progress_tmk24Data::lls_check_address_and_pass:
                if(commandArrayReplyData.size() > 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        lls_data.password.get.isValid = true; // TOOD: обработка ошибок
                    } else {
                        lls_data.password.get.isValid = false;
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_PasswordError, getUniqIdent(), QString("Password error"));
                    }
                    res = true;
                }
                break;

            case Progress_tmk24Data::lls_run_bootloader:
                if(isNeedMessageAboutExecuted) {

                }
                break;
            case Progress_tmk24Data::lls_read_cnt: {
                uint32_t cnt = 0;
                if(commandArrayReplyData.size() >= 8) {
                    cnt = 0xFF & commandArrayReplyData.at(7);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(6);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(5);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(4);
                    lls_data.cnt.value.value_u32 = cnt;
                    lls_data.cnt.isValid = true;
                    res = true;
                }
            }
                break;
            default : break;
            }

            if(getState() == STATE_START_INIT) {
                if((lls_data.settings.get.isValid) && (lls_data.errors.isValid)
                        && (lls_data.password.get.isValid) && (lls_data.calibrateTable.get.isValid)
                        && (lls_data.llssValues.isValid)) {
                    setState(DeviceAbstract::STATE_NORMAL_READY);
                    emit eventDevice(DeviceAbstract::Type_DeviceEvent_Inited, getUniqIdent(), QString("Inited"));
                }
            }
        } else {
            qDebug() << "parce -ERROR crc\n";
        }
    } else {
        state = STATE_DISCONNECTED;
        emit eventDevice(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqIdent(), QString("Status disconnected"));
    }
    return res;
}

CommandController::sCommandData Progress_tmk24::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    return command;
}

CommandController::sCommandData Progress_tmk24::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk24::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
    listCommand.push_back(command);
    return listCommand;
}

CommandController::sCommandData Progress_tmk24::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
    return command;
}

CommandController::sCommandData Progress_tmk24::getCommandCustom(QString operation, QStringList data) {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_read_settings;

    if(operation == "set current level value as min") {
        command.devCommand = (int)Progress_tmk24Data::lls_calibrate_min;
    } else if(operation == "set current level value as max") {
        command.devCommand = (int)Progress_tmk24Data::lls_calibrate_max;
    } else if(operation == "get current dev settings") {
        command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
    } else if(operation == "set current dev settings") {
        command.devCommand = (int)Progress_tmk24Data::lls_write_settings;
        for(auto i:data) {
            command.commandOptionArg.push_back(i.toInt());
        }
    } else if(operation == "read current dev errors") {
        command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    } else if(operation == "set current dev cal table") {
        command.devCommand = (int)Progress_tmk24Data::lls_write_cal_table;
    } else if(operation == "read current dev cal table") {
        command.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
    } else {
        qDebug() << "getCommandCustom -type unknown!";
    }
    return command;
}


QList<CommandController::sCommandData> Progress_tmk24::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.commandOptionData.clear();
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    listCommand.push_back(command);
    return listCommand;
}
