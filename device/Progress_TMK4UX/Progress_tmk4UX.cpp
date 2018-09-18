#include <QDebug>
#include "Progress_tmk4UX.h"
#include "other/crc.h"

Progress_tmk4UX::Progress_tmk4UX(QString uniqIdentId, QString passwordSession) {
    this->chartData = new QList<int>();
    this->uniqIdentId = uniqIdentId;
    this->state = STATE_DISCONNECTED;
    this->lls_data.password.session.value = passwordSession;
    this->lls_data.password.session.isValid = true;
    setDefaultValues();
}

Progress_tmk4UX::~Progress_tmk4UX() {

}

QString Progress_tmk4UX::getDevTypeName() {
    return QString::fromLocal8Bit(Progress_tmk4UX::name, strlen(Progress_tmk4UX::name));
}

void Progress_tmk4UX::setDefaultValues() {
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

QList<int> Progress_tmk4UX::getChart() {
    return *chartData;
}

// TODO: is valid handler!
QStringList Progress_tmk4UX::getPropertyData() {
    QStringList res;
    res << lls_data.serialNum.value;
    res << QString::number(settings.netAddress);
    res << getDevTypeName();
    res << lls_data.firmware.value;
    res << QString::number(lls_data.password.get.isValid);
    return res;
}

QStringList Progress_tmk4UX::getCurrentData() {
    QList<QString> res;
    res << QString::number(lls_data.fuelLevel.value.value_u32);
    res << QString::number(lls_data.fuelProcent.value.value_u16);
    res << QString::number(lls_data.cnt.value.value_u32);
    res << QString::number(lls_data.freq.value.value_u16);
    res << QString::number(lls_data.temp.value.value_i);
    return res;
}

QStringList Progress_tmk4UX::getErrors() {
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

DeviceAbstract::E_State Progress_tmk4UX::getState() {
    return state;
}

QPair<QStringList,QStringList> Progress_tmk4UX::getSettings() {

}

void Progress_tmk4UX::setState(DeviceAbstract::E_State value) {
    state = value; // если дисконектим или сбрасываем - тогда сбрасываем и данные
    if((state == DeviceAbstract::STATE_DISCONNECTED) || (state == DeviceAbstract::STATE_START_INIT)) {
        setDefaultValues();
    }
}

QString Progress_tmk4UX::getUniqIdent() {
    return uniqIdentId;
}

bool Progress_tmk4UX::makeDataToCommand(CommandController::sCommandData &commandData) {
    bool res = false;
    if(!commandData.deviceIdent.isEmpty()) {
        try {
            commandData.commandOptionData.push_back(0x31);
            // id addr
            commandData.commandOptionData.push_back(commandData.deviceIdent.toInt());
            // command byte
            commandData.commandOptionData.push_back(commandData.devCommand);
            switch(commandData.devCommand) {
            case Progress_tmk4UXData::lls_read_lvl_once: break;
            case Progress_tmk4UXData::lls_send_data_enable: break;
            case Progress_tmk4UXData::lls_set_send_time: break;
            case Progress_tmk4UXData::lls_send_data_default: break;
            case Progress_tmk4UXData::lls_read_cnt: break;
            case Progress_tmk4UXData::lls_read_lvl_all: break;
            case Progress_tmk4UXData::lls_read_settings: break;

            case Progress_tmk4UXData::lls_write_settings: {
                // сперва заносим текущий пароль для разрешения доступа
                //                QString password = QString::fromUtf8(commandArg.Progress_tmk4UX::E_param_suquence::param_password_session), 0);
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

            case Progress_tmk4UXData::lls_read_cal_table:
                break;

            case Progress_tmk4UXData::lls_write_cal_table: {
            }
                break;
            case Progress_tmk4UXData::lls_calibrate_min:
            case Progress_tmk4UXData::lls_calibrate_max: {
                // заносим текущий пароль для разрешения доступа
                // значение заносится в самоме датчике
                QByteArray passArray;
                if(lls_data.password.session.isValid) {
                    if(!lls_data.password.session.value.isEmpty()) {
                        int passLen = lls_data.password.session.value.length();
                        for(int passCounter=0; passCounter<passLen; passCounter++) {
                            commandData.commandOptionData.push_back(
                                        lls_data.password.session.value.at(passCounter).toLatin1());
                        }
                    }
                }
                while(passArray.size() < PASSWORD_SIZE) {
                    passArray.push_back((char)0);
                }
                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
            }
                break;
            case Progress_tmk4UXData::lls_read_errors: break;
            case Progress_tmk4UXData::lls_set_serial_number: break;
            case Progress_tmk4UXData::lls_read_serial_number: break;
            case Progress_tmk4UXData::lls_set_personal: break;
            case Progress_tmk4UXData::lls_read_personal: break;
            case Progress_tmk4UXData::lls_set_new_password: {
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

            case Progress_tmk4UXData::lls_check_address_and_pass: {
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
            case Progress_tmk4UXData::lls_run_bootloader: break;
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

bool Progress_tmk4UX::placeDataReplyToCommand(QByteArray &commandArrayReplyData, bool isNeedMessageAboutExecuted) {
    bool res = false;
    uint8_t crcCalcResult = 0;
    uint16_t frequency = 0;
    uint16_t value = 0;
    Crc *crc = new Crc();

    // if gived reply with data - device CONNECTED
    if(!commandArrayReplyData.isEmpty()) {
        if(getState() == STATE_DISCONNECTED) {
            setState(DeviceAbstract::STATE_START_INIT); // после этой команды настройки уже считаны
            emit eventDevice(DeviceAbstract::Type_DeviceEvent_Connected, getUniqIdent(), QString("Connected"), QStringList(""));
        }
        //-- caculate crc
        crcCalcResult = crc->crc8_dallas(commandArrayReplyData.data(),
                                         commandArrayReplyData.length()-1);
        //-- if result crc is valid
        if(crcCalcResult == (0xff & commandArrayReplyData.at(
                                 commandArrayReplyData.length()-1))) {
            //-- byte is command
            switch(commandArrayReplyData.at(2)) {
            case Progress_tmk4UXData::lls_read_lvl_once: {
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
                    chartData->push_back(lls_data.fuelLevel.value.value_u32 + (rand()%10));
                    while(chartData->size() > 50) {
                        chartData->pop_front();
                    }
                    emit eventDevice(DeviceAbstract::Type_DeviceEvent_CurrentDataUpdated, getUniqIdent(), QString("Ready current data"), QStringList(""));
                    res = true;
                }
            }
                break;
            case Progress_tmk4UXData::lls_send_data_enable: break;
            case Progress_tmk4UXData::lls_set_send_time: break;
            case Progress_tmk4UXData::lls_send_data_default: break;
            case Progress_tmk4UXData::lls_read_lvl_all: {
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

            case Progress_tmk4UXData::lls_read_settings: {
                if(commandArrayReplyData.size() > 22) {
                    char *pbuf = (commandArrayReplyData.data() + 4);
                    lls_data.serialNum.value = QString::fromUtf8(pbuf, SERIALNUMBER_STRING_SIZE);

                    pbuf = (commandArrayReplyData.data() + 4 + SERIALNUMBER_STRING_SIZE);
                    lls_data.firmware.value = QString::fromUtf8(pbuf,  FIRMWARE_VERSION_STRING_SIZE);

                    // проверка типа
                    if(commandArrayReplyData.at(3) != Progress_tmk4UXData::type_lls_tmk4ux) {
                        lls_data.typeIsValid = false;
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_TypeError, getUniqIdent(), QString("Type Error!"), QStringList(""));
                    } else { // TODO: is valid conversion?
                        Progress_tmk4UXData::T_settings *pSettings = (Progress_tmk4UXData::T_settings*)(commandArrayReplyData.data() + 34);
                        if(pSettings->netAddress == commandArrayReplyData.at(Progress_tmk4UXData::param_id_address)) {
                            lls_data.settings.get.value = *pSettings;
                            lls_data.settings.get.isValid = true;
                        }
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_ReadyReadProperties, getUniqIdent(), QString("Ready read properties"), QStringList(""));
                    }
                    res = true;
                }
            }
                break;

            case Progress_tmk4UXData::lls_write_settings:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 4) {
                        if(commandArrayReplyData.at(3) == 0) {
                            res = true;
                        }
                    }
                }
                break;

            case Progress_tmk4UXData::lls_read_cal_table: {
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 45) {
                        memset(&lls_data.calibrateTable.get.table, 0, sizeof(Progress_tmk4UXData::T_calibrationTable));
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
                        res = true;
                    }
                }
            }
                break;

            case Progress_tmk4UXData::lls_write_cal_table:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 4) {
                        if(commandArrayReplyData.at(3) == 0) {
                            res = true;
                        }
                    }
                }
                break;
            case Progress_tmk4UXData::lls_calibrate_min:
            case Progress_tmk4UXData::lls_calibrate_max:
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 3) {
                        if(commandArrayReplyData.at(3) == 0) {
                            // TODO: обработка ок
                            res = true;
                        } else {
                            // TODO: обработка ошибки
                        }
                    }
                }
                break;

            case Progress_tmk4UXData::lls_read_errors:
            {
                if(lls_data.typeIsValid) {
                    if(commandArrayReplyData.size() > 5) { // TODO: 10?
                        Progress_tmk4UXData::T_errors t_erros;
                        memcpy(&t_erros, (commandArrayReplyData.data() + 3), sizeof(t_erros));
                        memcpy(&lls_data.errors, &t_erros, sizeof(lls_data.errors));
                        lls_data.errors.isValid = true;
                        res = true;
                    }
                }
            }
                break;
            case Progress_tmk4UXData::lls_set_serial_number: break;
            case Progress_tmk4UXData::lls_read_serial_number: {
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

            case Progress_tmk4UXData::lls_set_personal: break;
            case Progress_tmk4UXData::lls_read_personal: break;
            case Progress_tmk4UXData::lls_set_new_password:
                if(commandArrayReplyData.size() >= 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        res = true;
                    }
                }
                break;

            case Progress_tmk4UXData::lls_check_address_and_pass:
                if(commandArrayReplyData.size() > 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        lls_data.password.get.isValid = true; // TOOD: обработка ошибок
                    } else {
                        lls_data.password.get.isValid = false;
                        emit eventDevice(DeviceAbstract::Type_DeviceEvent_PasswordError, getUniqIdent(), QString("Password error"), QStringList(""));
                    }
                    res = true;
                }
                break;

            case Progress_tmk4UXData::lls_run_bootloader: break;
            case Progress_tmk4UXData::lls_read_cnt: {
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
                    emit eventDevice(DeviceAbstract::Type_DeviceEvent_Inited, getUniqIdent(), QString("Inited"), QStringList(""));
                }
            }
        } else {
            qDebug() << "parce -ERROR crc\n";
        }
    } else {
        state = STATE_DISCONNECTED;
        emit eventDevice(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqIdent(), QString("Status disconnected"), QStringList(""));
    }
    return res;
}

CommandController::sCommandData Progress_tmk4UX::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_errors;
    return command;
}

CommandController::sCommandData Progress_tmk4UX::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk4UXData::lls_check_address_and_pass;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_cal_table;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_check_address_and_pass;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_read_errors;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_read_settings;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_read_lvl_all;
    listCommand.push_back(command);
    return listCommand;
}

CommandController::sCommandData Progress_tmk4UX::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_settings;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
//    command.deviceIdent = getUniqIdent();
//    command.devCommand = (int)Progress_tmk4UXData::lls_read_settings;

//    if(operation == "set current level value as min") {
//        command.devCommand = (int)Progress_tmk4UXData::lls_calibrate_min;
//    } else if(operation == "set current level value as max") {
//        command.devCommand = (int)Progress_tmk4UXData::lls_calibrate_max;
//    } else {
//        qDebug() << "getCommandCustom -type unknown!";
//    }
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandCustom(QString operation) {

}


QList<CommandController::sCommandData> Progress_tmk4UX::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.commandOptionData.clear();
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_lvl_once;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_read_lvl_all;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk4UXData::lls_read_errors;
    listCommand.push_back(command);
    return listCommand;
}

#ifdef USE_TEST_DEV_REPLY
bool Progress_tmk4UX::makeDataRequestReply(QByteArray request, QByteArray &reply) {
    bool res = false;
    uint8_t crcCalcResult = 0;
    Crc *crc = new Crc();
    reply.clear();

    uint16_t fuel =  getFuel();
    uint16_t frequency = getFrequency();
    int8_t temperature = getTemperature();
    bool flagSpeedChangedRs485 = false;

    if(!request.isEmpty()) {
        uint8_t addr = request.at(1);
        uint8_t command = request.at(2);

        switch(command) {
        case Progress_tmk4UXData::lls_read_lvl_once: {
            if(request.size() == 4) {
                reply.push_back(0x3E);
                reply.push_back(addr);
                reply.push_back(Progress_tmk4UXData::lls_read_lvl_once);
                reply.push_back(temperature);
                reply.push_back((fuel) & 0x00FF);
                reply.push_back(((fuel) & 0xFF00)>>8);
                reply.push_back(frequency & 0x00FF);
                reply.push_back((frequency & 0xFF00)>>8);
                crcCalcResult = crc->crc8_dallas(reply.data(), reply.length());
                reply.push_back(crcCalcResult);
                res = true;
            }
        }
            break;
        case Progress_tmk4UXData::lls_send_data_enable: {
            //        if( rxSize == 4) {
            //            pLlsState->dataSend=HEX;
            //            replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_send_data_default:{
            //        if( rxSize == 5 && pBuff[3] <= 2) {
            //            pSettings->periodicSendType = (PeriodicSendType) pBuff[3];
            //            saveSettingsToFlash();
            //            replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_set_send_time:{
            //        if( rxSize == 5) {
            //            pSettings->periodicSendTime = pBuff[3];
            //            saveSettingsToFlash();
            //            replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_set_serial_number:{
            //        if (rxSize == 16) {
            //            if (*pSerialNumber == 0xFF) {

            //                for (i=0; i<SERIALNUMBER_STRING_SIZE; i++) {
            //                    newSerialNumber[i] = (char) pBuff[3+i];
            //                }

            //                HAL_FLASH_Unlock();
            //                flashWriteBuffer16((uint32_t*) pSerialNumber, (uint32_t*) &newSerialNumber, SERIALNUMBER_STRING_SIZE);
            //                HAL_FLASH_Lock();

            //                replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_serial_number: {
            if(request.length() == 4) {
                int i=0;
                char* pSerialNumber = (char*)serialNumber;
                char* pVersion = version.toUtf8().data();
                char* pCpuId = cpuId.toUtf8().data();
                reply.push_back(0x3E);
                reply.push_back(addr);
                reply.push_back(Progress_tmk4UXData::lls_read_serial_number);
                for (i=0;i<SERIALNUMBER_STRING_SIZE;i++) {
                    reply.push_back(serialNumber[i]);
                }
                for(i=0; i<VERSION_STRING_SIZE; i++) {
                    reply.push_back(pVersion[i]);
                }
                for(i=0; i<CPU_ID_SIZE; i++) {
                    reply.push_back(pCpuId[i]);
                }
                crcCalcResult = crc->crc8_dallas(reply.data(), reply.length());
                reply.push_back(crcCalcResult);
                return true;
            }
        }
            break;
        case Progress_tmk4UXData::lls_set_personal:{
            //        if (rxSize == PERSONAL_DATA_SIZE+4) {
            //            if (*pPersonalData == 0xFF) {
            //                for (i=0;i<PERSONAL_DATA_SIZE;i++) {
            //                    personalDataBuff[i] = (char)pBuff[3+i];
            //                }

            //                HAL_FLASH_Unlock();
            //                flashWriteBuffer16((uint32_t*) pPersonalData, (uint32_t*) &personalDataBuff, PERSONAL_DATA_SIZE);
            //                HAL_FLASH_Lock();
            //                //saveSettingsToFlash();
            //                replaySize=sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_personal:{
            //        if(rxSize == 4) {
            //            replaySize = sendPersonal(addr, (uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_cnt: {
            reply.push_back(0x3E);
            reply.push_back(addr);
            reply.push_back(Progress_tmk4UXData::lls_read_cnt);
            reply.push_back(DUT_TYPE);
            reply.push_back((cnt & 0x000000FF));
            reply.push_back((cnt & 0x0000FF00)>>8);
            reply.push_back((cnt & 0x00FF0000)>>16);
            reply.push_back((cnt & 0xFF000000)>>24);
            reply.push_back((fuel & 0x00FF));
            reply.push_back((fuel & 0xFF00)>>8);
            crcCalcResult = crc->crc8_dallas(reply.data(), reply.length());
            reply.push_back(crcCalcResult);
        }
            break;
        case Progress_tmk4UXData::lls_calibrate_min:{
            //        if (rxSize == 12) {
            //            packetPassHash = calculatePasswordHash(pBuff+3,PASSWORD_SIZE);
            //            if (passwordHash == packetPassHash) {
            //                pSettings->cntEmpty = getCounter();
            //                saveSettingsToFlash();
            //                fuelResetFilters();
            //                replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_PASSWORD;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_calibrate_max: {
            //        if (rxSize == 12) {
            //            packetPassHash = calculatePasswordHash(pBuff+3,PASSWORD_SIZE);
            //            if (passwordHash == packetPassHash) {
            //                pSettings->cntFull = getCounter();
            //                saveSettingsToFlash();
            //                fuelResetFilters();
            //                replaySize = sendReplay(addr, command, 0x00, (uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_PASSWORD;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_cal_table:{
            //        if (rxSize == 4) {
            //            replaySize = sendCalibrationTable(addr, (uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_write_cal_table: {
            //        packetPassHash = calculatePasswordHash(pBuff+3, PASSWORD_SIZE); //TODO: вставить проверку настроечного пароля
            //        if (passwordHash == packetPassHash) {
            //            uint8_t pontCount = pBuff[11];
            //            if (pontCount <= CALIBRATION_TABLE_MAX_SIZE) {
            //                bool flagNotSorted = false;
            //                if ( (((*(pBuff+13+( (pontCount-1) )*4))<<8)+*(pBuff+12+( (pontCount-1) )*4)) > 4095 ) {
            //                    flagNotSorted = true;
            //                }

            //                if (flagNotSorted == false) {
            //                    pCalibrationTable->tableSize = *(pBuff+11);
            //                    for (i=0; i<(pCalibrationTable->tableSize); i++) {
            //                        pCalibrationTable->table[i].x = (uint32_t) ( ((*(pBuff+13+i*4))<<8) + *(pBuff+12+i*4) );
            //                        pCalibrationTable->table[i].y = (uint32_t) ( ((*(pBuff+15+i*4))<<8) + *(pBuff+14+i*4) );
            //                    }
            //                    saveSettingsToFlash();

            //                    replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                    exception = PROTOCOL_NO_EXCEPTION;
            //                } else {
            //                    exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //                }
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_PASSWORD;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_settings: {
            //        if (rxSize == 4) {
            //            replaySize = sendSettings(addr, (uint8_t *) pBuff);
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_write_settings: {
            //        if (rxSize == (4 + 2 + PASSWORD_SIZE + sizeof(Settings))) {
            //            packetPassHash = calculatePasswordHash(pBuff+3,PASSWORD_SIZE);
            //            if (passwordHash == packetPassHash) {
            //                memcpy(&newSettings, (pBuff+13), sizeof(Settings));
            //                //Проверка условий настроек
            //                if ( 	newSettings.periodicSendType < 3 &&
            //                        newSettings.minLevel < 1024 &&
            //                        newSettings.maxLevel < 4096 &&
            //                        newSettings.outputValue < 2 &&
            //                        newSettings.filterType < 4 &&
            //                        newSettings.avarageLength < (AVARAGE_MAX_LENGTH+1) &&
            //                        newSettings.medianLength < (MEDIAN_MAX_LENGTH+1) &&
            //                        newSettings.thermoCompensationType < 8 &&
            //                        newSettings.interpolationType < 1 &&
            //                        newSettings.rs485Speed < 8 &&
            //                        newSettings.waterMode < 2 &&
            //                        newSettings.lowLevelThreshold < 4096 &&
            //                        newSettings.pullUpIsEnabled < 2
            //                        ) {

            //                    if (newSettings.rs485Speed != pSettings->rs485Speed) {
            //                        flagSpeedChangedRs485 = true;
            //                    }
            //                    memcpy(pSettings, &newSettings, sizeof(Settings));
            //                    saveSettingsToFlash();

            //                    //Меняем настройки фильтров
            //                    fuelResetFilters();

            //                    replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                    exception = PROTOCOL_NO_EXCEPTION;
            //                } else {
            //                    exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //                }
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_PASSWORD;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_read_errors:
            //        if( rxSize == 4) {
            //            replaySize = sendErrors(addr, (uint8_t *) pBuff);
            //            clearErrors();
            //            exception = PROTOCOL_NO_EXCEPTION;
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
            break;
        case Progress_tmk4UXData::lls_set_new_password:{
            //        if (rxSize == 20) {
            //            packetPassHash = calculatePasswordHash(pBuff+3, PASSWORD_SIZE);
            //            if (passwordHash == packetPassHash) { //TODO: вставить проверку настроечного пароля
            //                passwordHash = calculatePasswordHash(pBuff+11, PASSWORD_SIZE);
            //                saveSettingsToFlash();
            //                replaySize = sendReplay(addr, command, 0x00 ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_PASSWORD;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_check_address_and_pass:{
            //        if (rxSize == 12) {
            //            packetPassHash = calculatePasswordHash(pBuff+3, PASSWORD_SIZE);
            //            if (passwordHash == packetPassHash) { //TODO: вставить проверку настроечного пароля
            //                replaySize = sendReplay(pSettings->netAddress, command, PROTOCOL_NO_EXCEPTION ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            } else {
            //                replaySize = sendReplay(pSettings->netAddress, command, PROTOCOL_ILLEGAL_PASSWORD ,(uint8_t *) pBuff);
            //                exception = PROTOCOL_NO_EXCEPTION;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        case Progress_tmk4UXData::lls_run_bootloader: {
            //        if(5 == rxSize) {
            //            if(pBuff[3] == 0x19) {
            //                //!!!WatchDogStillEnabled!!!
            //                /* Jump to user application */
            //                //Remap IRQ VECTOR TABLE
            //                //TODO деинит syscfg
            //                //SYSCFG_DeInit();
            //                NVIC->ICER[0] = 0xFFFFFFFF; //запрещаю все прерывания
            //                NVIC_EnableIRQ(SysTick_IRQn); //разрешаем прерывания от систика
            //                ////Disable IRQ
            //                //__disable_irq();
            //                ////Disable SysTick
            //                //SysTick->CTRL = 0;    // Turn off the SysTick timer
            //                //DisableDMA
            //                //TODO проверить нужно ли сейчас
            //                //HAL_RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);
            //                //SetJumpAddress
            //                JumpAddress = *(__IO uint32_t*) (BOOTLOADER_MENU_ADDRESS);
            //                Jump_To_Application = (pFunction) JumpAddress;
            //                /* Initialize user application's Stack Pointer */
            //                __set_MSP(*(__IO uint32_t*) BOOTLOADER_ADDRESS);
            //                /* Jump to application */
            //                Jump_To_Application();
            //            } else {
            //                exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //            }
            //        } else {
            //            exception = PROTOCOL_ILLEGAL_DATA_VALUE;
            //        }
        }
            break;
        default:
            //        exception = PROTOCOL_ILLEGAL_FUNCTION;
            break;
        }
    }
    return res;
}

uint16_t Progress_tmk4UX::getFuel() {
    return fuel;
}

uint16_t Progress_tmk4UX::getFrequency() {
    return freq;
}

int8_t Progress_tmk4UX::getTemperature() {
    return temp;
}
#endif
