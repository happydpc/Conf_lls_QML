#include <QDebug>
#include "Progress_tmk24.h"
#include "other/crc.h"
#include <QList>

Progress_tmk24::Progress_tmk24(QString devId, QString header,
                               QPair<QStringList,QStringList>param, ServiceDevicesAbstract *pServiceAbstract) {
    this->deviceIdent.id = devId;
    this->deviceIdent.header = header;
    this->state = STATE_DISCONNECTED;
    int paramCounter = 0;
    for(auto paramIter:param.first) {
        if(paramIter == "password") {
            this->lls_data.password.session.value = param.second[paramCounter];
            this->lls_data.password.session.isValid = true;
        }
        paramCounter++;
    }
    this->serviceAbstact = pServiceAbstract;
    setDefaultValues();
}

Progress_tmk24::~Progress_tmk24() {

}

QString Progress_tmk24::getDevTypeName() {
    return QString::fromLocal8Bit(Progress_tmk24::name, strlen(Progress_tmk24::name));
}

QString Progress_tmk24::getDevHeader() {
    return deviceIdent.header;
}

void Progress_tmk24::setDevHeader(QString header) {
    deviceIdent.header = header;
}

void Progress_tmk24::setDefaultValues() {
    this->settings.k1 = 0;
    this->settings.k2 = 0;
    this->settings.netAddress = (uint8_t)deviceIdent.id.toInt();
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
    this->lls_data.fuelLevel.isValid = false;
    this->lls_data.freq.isValid = false;
    this->lls_data.temp.isValid = false;
    this->lls_data.cnt.isValid = false;
    this->lls_data.firmware.isValid = false;
}

ServiceDevicesAbstract* Progress_tmk24::getServiceAbstract() {
    return serviceAbstact;
}

QPair<QStringList,QStringList> Progress_tmk24::getPropertyData() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("devTypeName");
    res.second.push_back(getDevTypeName());
    res.first.push_back("serialNum");
    res.second.push_back((lls_data.serialNum.value.isEmpty() || lls_data.serialNum.value.at(0) > 0x255) ? QString("Не присвоен") : lls_data.serialNum.value);
    res.first.push_back("netAddress");
    res.second.push_back(QString::number(settings.netAddress));
    res.first.push_back("versionFirmare");
    res.second.push_back(lls_data.firmware.isValid ? lls_data.firmware.value : "NA");
    res.first.push_back("authIsNormal");
    res.second.push_back(QString::number(lls_data.password.get.authIsNormal));
    res.first.push_back("password");
    res.second.push_back(lls_data.password.get.value.value);
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("header");
    res.second.push_back(deviceIdent.header);
    return res;
}

QPair<QStringList,QStringList> Progress_tmk24::getCurrentData() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("fuelLevel");
    res.second.push_back(lls_data.fuelLevel.isValid == true ? QString::number(lls_data.fuelLevel.value.value_u32) : QString::number(0));
    res.first.push_back("fuelProcent");
    res.second.push_back(lls_data.fuelProcent.isValid ? QString::number(lls_data.fuelProcent.value.value_u16) : QString::number(0));
    res.first.push_back("cnt");
    res.second.push_back(lls_data.cnt.isValid ? QString::number(lls_data.cnt.value.value_u32) : QString::number(0));
    res.first.push_back("freq");
    res.second.push_back(lls_data.freq.isValid ? QString::number(lls_data.freq.value.value_u16) : QString::number(0));
    res.first.push_back("temp");
    res.second.push_back(lls_data.temp.isValid ? QString::number(lls_data.temp.value.value_i) : QString::number(0));
    res.first.push_back("noiseDetected");
    res.second.push_back(QString::number(lls_data.noiseDetected));
    res.first.push_back("chartValue");
    res.second.push_back(lls_data.fuelLevel.isValid == true ? QString::number(lls_data.fuelLevel.value.value_u32) : QString::number(0));
    return res;
}

QPair<QStringList,QStringList> Progress_tmk24::getSettings() {
    QPair<QStringList,QStringList> res;
    if(lls_data.settings.get.isValid) {
        res.first.push_back("device_value");
        res.second.push_back(getDevTypeName());
        res.first.push_back("versionFirmare");
        res.second.push_back(lls_data.firmware.isValid ? lls_data.firmware.value : "NA");
        res.first.push_back("k1_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.k1, 'f'));
        res.first.push_back("k2_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.k2, 'f'));
        res.first.push_back("typeTempCompensation_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.thermoCompensationType));
        res.first.push_back("periodicSendType_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.periodicSendType));
        res.first.push_back("periodicSendTime_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.periodicSendTime));
        res.first.push_back("typeOutMessage_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.outputValue));
        res.first.push_back("typeInterpolation_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.interpolationType));
        res.first.push_back("typeFiltration_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.filterType));
        res.first.push_back("filterLenghtMediana_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.medianLength));
        res.first.push_back("filterAvarageValueSec_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.avarageLength));
        res.first.push_back("filterValueQ_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.q, 'f'));
        res.first.push_back("filterValueR_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.r, 'f'));
        res.first.push_back("minLevelValue_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.minLevel));
        res.first.push_back("maxLevelValue_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.maxLevel));
        res.first.push_back("masterSlaveModes_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.masterMode));
        res.first.push_back("baudrateRs232Values_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.rs232Speed));
        res.first.push_back("baudrateRs485Values_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.rs485Speed));
        res.first.push_back("masterSlaveFullCountes_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.slaveCount));
        res.first.push_back("masterSlaveSlaveId_1_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.slaveAddr[0]));
        res.first.push_back("masterSlaveSlaveId_2_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.slaveAddr[1]));
        res.first.push_back("masterSlaveSlaveId_3_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.slaveAddr[2]));
        res.first.push_back("masterSlaveSlaveId_4_value");
        res.second.push_back(QString::number(lls_data.settings.get.value.slaveAddr[3]));
    }
    return res;
}

QPair<QStringList,QStringList> Progress_tmk24::getErrors() {
    QPair<QStringList,QStringList> ret;
    if(lls_data.errors.isValid) {
        ret.first.push_back("GenFreq0");
        ret.second.push_back(QString::number(lls_data.errors.errors.GenFreq0));
        ret.first.push_back("MaxFreqOut");
        ret.second.push_back(QString::number(lls_data.errors.errors.MaxFreqOut));
        ret.first.push_back("MinFreqOut");
        ret.second.push_back(QString::number(lls_data.errors.errors.MinFreqOut));
        ret.first.push_back("NotCalibrated");
        ret.second.push_back(QString::number(lls_data.errors.errors.NotCalibrated));
        ret.first.push_back("QeueManagerError");
        ret.second.push_back(QString::number(lls_data.errors.errors.QeueManagerError));
        ret.first.push_back("ReplayNotComeRs232");
        ret.second.push_back(QString::number(lls_data.errors.errors.ReplayNotComeRs232));
        ret.first.push_back("ReplayNotComeRs485");
        ret.second.push_back(QString::number(lls_data.errors.errors.ReplayNotComeRs485));
        ret.first.push_back("Rs232Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Rs232Error));
        ret.first.push_back("Rs485Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Rs485Error));
        ret.first.push_back("Slave1Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Slave1Error));
        ret.first.push_back("Slave2Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Slave2Error));
        ret.first.push_back("Slave3Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Slave3Error));
        ret.first.push_back("Slave4Error");
        ret.second.push_back(QString::number(lls_data.errors.errors.Slave4Error));
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

QString Progress_tmk24::getUniqId() {
    return deviceIdent.id;
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
                QByteArray passArray;
                if(lls_data.password.session.isValid) {
                    if(!lls_data.password.session.value.isEmpty()) {
                        int passLen = lls_data.password.session.value.length();
                        for(int passCounter=0; passCounter<passLen; passCounter++) {
                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
                        }
                    }
                }
                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
                    passArray.push_back((char)0);
                }
                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
                commandData.commandOptionData.push_back(0xFF);
                commandData.commandOptionData.push_back(0xFF);

                Progress_tmk24Data::T_settings tSettings;
                if(lls_data.settings.get.isValid) {
                    memcpy(&tSettings, &lls_data.settings.get.value, sizeof(tSettings));
                    for(int i=0; i<commandData.args.key.size(); i++) {
                        if(commandData.args.key.at(i) == "k1_value") {
                            tSettings.k1 = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "k2_value") {
                            tSettings.k2 = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "typeTempCompensation_value") {
                            tSettings.thermoCompensationType = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "netAddress_value") {
                            tSettings.netAddress = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "periodicSendType_value") {
                            tSettings.periodicSendType = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "periodicSendTime_value") {
                            tSettings.periodicSendTime = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "typeOutMessage_value") {
                            tSettings.outputValue = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "typeInterpolation_value") {
                            tSettings.interpolationType = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "typeFiltration_value") {
                            tSettings.filterType = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "filterLenghtMediana_value") {
                            tSettings.medianLength = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "filterAvarageValueSec_value") {
                            tSettings.avarageLength = commandData.args.value.at(i).toInt(); //
                        } else if(commandData.args.key.at(i) == "filterValueQ_value") {
                            tSettings.q = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "filterValueR_value") {
                            tSettings.r = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "minLevelValue_value") {
                            tSettings.minLevel = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "maxLevelValue_value") {
                            tSettings.maxLevel = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveModes_value") {
                            tSettings.masterMode = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "baudrateRs232Values_value") {
                            tSettings.rs232Speed = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "baudrateRs485Values_value") {
                            tSettings.rs485Speed = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveFullCountes_value") {
                            tSettings.slaveCount = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_1_value") {
                            tSettings.slaveAddr[0] = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_2_value") {
                            tSettings.slaveAddr[1] = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_3_value") {
                            tSettings.slaveAddr[2] = commandData.args.value.at(i).toInt();
                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_4_value") {
                            tSettings.slaveAddr[3] = commandData.args.value.at(i).toInt();
                        } else {
                            qDebug() << "settings udnefined type parcing";
                        }
                    }

                    commandData.commandOptionData.insert(13, (char*)&tSettings, sizeof(Progress_tmk24Data::T_settings));
                    while(commandData.commandOptionData.size() != 62) {
                        commandData.commandOptionData.push_back(0xFF);
                    }
                }
            }
                break;

            case Progress_tmk24Data::lls_read_cal_table:
                break;

            case Progress_tmk24Data::lls_write_cal_table: {
                // сперва заносим текущий пароль для разрешения доступа
                QByteArray passArray;
                if(lls_data.password.session.isValid) {
                    if(!lls_data.password.session.value.isEmpty()) {
                        int passLen = lls_data.password.session.value.length();
                        for(int passCounter=0; passCounter<passLen; passCounter++) {
                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
                        }
                    }
                }
                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
                    passArray.push_back((char)0);
                }
                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
                commandData.commandOptionData.push_back((uint8_t)commandData.args.value.size());
                for(uint8_t i=0; i<(Progress_tmk24Data::TAR_TABLE_SIZE); i++) {
                    if(i < commandData.args.value.size()) {
                        commandData.commandOptionData.push_back((uint32_t)commandData.args.key.at(i).toUInt() & 0xFF);
                        commandData.commandOptionData.push_back(((uint32_t)commandData.args.key.at(i).toUInt() & 0xFF00) >> 8);
                        commandData.commandOptionData.push_back((uint32_t)commandData.args.value.at(i).toUInt() & 0xFF);
                        commandData.commandOptionData.push_back(((uint32_t)commandData.args.value.at(i).toUInt() & 0xFF00) >> 8);
                    } else {
                        commandData.commandOptionData.push_back((char)0);
                        commandData.commandOptionData.push_back((char)0);
                        commandData.commandOptionData.push_back((char)0);
                        commandData.commandOptionData.push_back((char)0);
                    }
                }
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
                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
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
                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
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

bool Progress_tmk24::placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) {
    bool res = false;
    Crc crc;
    uint8_t crcRes = 0;
    uint16_t frequency = 0;
    uint16_t value = 0;

    // мы же знаем какую команду отправили, ее и ожидаем
    // внутри смотрим что она совпадает в пакете
    // ответ должен быть на отправленную команду
    switch(commandReqData.devCommand) {
    case Progress_tmk24Data::lls_read_lvl_once: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                lls_data.temp.value.value_i = (int8_t)(0xFF & commandArrayReplyData.at(3));
                lls_data.temp.isValid = true;
                value = 0;
                value = 0xFF & commandArrayReplyData.at(5);
                value = value << 8;
                value |= 0xFF & commandArrayReplyData.at(4);
                frequency = 0xFF & commandArrayReplyData.at(7);
                frequency = frequency << 8;
                frequency |= 0xFF & commandArrayReplyData.at(6);
                lls_data.fuelLevel.value.value_u32 = value;
                if(lls_data.settings.get.isValid) {
                    lls_data.fuelProcent.value.value_u32 = ((float)((float)value/lls_data.settings.get.value.maxLevel)*100);
                    lls_data.fuelProcent.isValid = true;
                } else {
                    lls_data.fuelProcent.value.value_u32 = 0;
                }
                lls_data.fuelLevel.isValid = true;
                lls_data.freq.value.value_u32  = frequency;
                lls_data.freq.isValid = true;
                emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_CurrentDataUpdated, getUniqId(),
                                            commandReqData.devCommand, QString("Ready current data"),
                                            QStringList(), QStringList(), commandReqData);
                res = true;
            }
        } else {
            // здесь не нужно ничего
            // т.к. если нет данных
            // оно само станет Disconnected
            // обработка требуется для выполнения команд по записи/чтения настроек и пр.
        }
    }
        break;
        // TOOD:
    case Progress_tmk24Data::lls_send_data_enable: break;
    case Progress_tmk24Data::lls_set_send_time: break;
    case Progress_tmk24Data::lls_send_data_default: break;
    case Progress_tmk24Data::lls_read_lvl_all: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
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
                emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                            commandReqData.commandType, "Update current data",
                                            QStringList(),QStringList(), commandReqData);
                emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                            commandReqData.commandType, "Normal",
                                            QStringList(), QStringList(), commandReqData);
                lls_data.llssValues.isValid = true;
                res = true;
            }
        } else {
            // здесь не нужно ничего
            // т.к. если нет данных
            // оно само станет Disconnected
            // обработка требуется для выполнения команд по записи/чтения настроек и пр.
        }
    }
        break;

    case Progress_tmk24Data::lls_read_settings: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 22) {
                    char *pbuf = (commandArrayReplyData.data() + 4);
                    lls_data.serialNum.value = QString::fromUtf8(pbuf, Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
                    lls_data.serialNum.isValid = true;
                    pbuf = (commandArrayReplyData.data() + 4 + Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
                    lls_data.firmware.value = QString::fromUtf8(pbuf,  Progress_tmk24Data::FIRMWARE_VERSION_STRING_SIZE);
                    lls_data.firmware.isValid = true;

                    // проверка типа
                    if(commandArrayReplyData.at(3) == Progress_tmk24Data::type_lls_tmk24) {
                        Progress_tmk24Data::T_settings *pSettings = (Progress_tmk24Data::T_settings*)(commandArrayReplyData.data() + 34);
                        if(pSettings->netAddress == commandArrayReplyData.at(Progress_tmk24Data::param_id_address)) {
                            lls_data.settings.get.value = *pSettings;
                            lls_data.settings.get.isValid = true;
                        }
                        if(getState() == STATE_GET_TYPE) {
                            setState(DeviceAbstract::STATE_CHECK_PASSWORD);
                        }
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"),
                                                    QStringList(), QStringList(), commandReqData);
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ReadyReadProperties, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"),
                                                    QStringList(), QStringList(), commandReqData);

                    } else {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_TypeError, getUniqId(),
                                                    commandReqData.devCommand, QString("Type Error!"),
                                                    QStringList(), QStringList(), commandReqData);
                    }
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"),
                                        QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_write_settings:
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                        res = true;
                    }
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
        break;

    case Progress_tmk24Data::lls_read_cal_table: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 45) {
                    QStringList keys;
                    QStringList values;
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
                        keys.push_back("y");
                        values.push_back(QString::number(lls_data.calibrateTable.get.table.y[i]));
                        keys.push_back("x");
                        values.push_back(QString::number(lls_data.calibrateTable.get.table.x[i]));
                    }
                    lls_data.calibrateTable.get.isValid = true;
                    if(commandReqData.isNeedAckMessage) {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"), keys, values, commandReqData);
                    }
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_write_cal_table: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 4) {
                    res = true;
                    if(commandArrayReplyData.at(3) == 0) {
                        if(commandReqData.isNeedAckMessage) {
                            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                        commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                        }
                    } else {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Data no valid"), QStringList(), QStringList(), commandReqData);
                    }
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;
    case Progress_tmk24Data::lls_calibrate_min: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 3) {
                    if(commandArrayReplyData.at(3) == 0) {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                    }
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_calibrate_max: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 3) {
                    if(commandArrayReplyData.at(3) == 0) {
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                    commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                        res = true;
                    }
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_read_errors: {
        // если ожидаемая команда совпадает с пакетом
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 5) { // TODO: 10?
                    Progress_tmk24Data::T_errors t_erros;
                    memcpy(&t_erros, (commandArrayReplyData.data() + 3), sizeof(t_erros));
                    memcpy(&lls_data.errors, &t_erros, sizeof(lls_data.errors));
                    emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                    lls_data.errors.isValid = true;
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;
    case Progress_tmk24Data::lls_set_serial_number: break;
    case Progress_tmk24Data::lls_read_serial_number: {
        // если ожидаемая команда совпадает с пакетом
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 22) {
                    lls_data.serialNum.value = QString::fromUtf8((commandArrayReplyData.data() + 3),
                                                                 Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
                    lls_data.serialNum.isValid = true;
                }
                res = true;
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_set_personal: break;
    case Progress_tmk24Data::lls_read_personal: break;
    case Progress_tmk24Data::lls_set_new_password:
        // если ожидаемая команда совпадает с пакетом
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() >= 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        res = true;
                    }
                }
            }
        }
        break;

    case Progress_tmk24Data::lls_check_address_and_pass: {
        // если ожидаемая команда совпадает с пакетом
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                if(commandArrayReplyData.size() > 4) {
                    if(commandArrayReplyData.at(3) == 0) {
                        lls_data.password.get.value.isValid = true; // TOOD: обработка ошибок
                        lls_data.password.get.authIsNormal = true;
                    } else {
                        lls_data.password.get.value.isValid = true;
                        lls_data.password.get.authIsNormal = false;
                        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_PasswordError, getUniqId(),
                                                    commandReqData.devCommand, QString("Password error"), QStringList(), QStringList(), commandReqData);
                    }
                    if(getState() == STATE_CHECK_PASSWORD) {
                        setState(STATE_START_INIT);
                    }
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;

    case Progress_tmk24Data::lls_run_bootloader: // TODO:
        break;
    case Progress_tmk24Data::lls_read_cnt: {
        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
            // возможно обращение к несуществующему элементу
            // если ожидаемая команда совпадает с пакетом
            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
                uint32_t cnt = 0;
                if(commandArrayReplyData.size() >= 8) {
                    cnt = 0xFF & commandArrayReplyData.at(7);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(6);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(5);
                    cnt = cnt << 8;
                    cnt |= 0xFF & commandArrayReplyData.at(4);

                    uint32_t maxProcentTollerance = lls_data.cnt.value.value_u32 / 100 * 5;
                    if(lls_data.cnt.isValid) {
                        lls_data.cnt.value.value_u32 = cnt;
                        lls_data.cnt.history.push_back(lls_data.cnt.value.value_u32);
                        if(lls_data.cnt.history.size() > Progress_tmk24Data::MAX_SIZE_HISTORY_CNT_LIST) {
                            lls_data.cnt.history.pop_front();
                        }
                    }
                    if(lls_data.cnt.value.value_u32 != 0) {
                        if(!lls_data.cnt.history.empty()) {
                            lls_data.noiseDetected = false;
                            for(auto i : lls_data.cnt.history) {
                                if(cnt >= (i - maxProcentTollerance)
                                        && cnt <= (i + maxProcentTollerance)) {
                                } else {
                                    lls_data.noiseDetected = true;
                                }
                            }
                        }
                    }
                    lls_data.cnt.value.value_u32 = cnt;
                    lls_data.cnt.isValid = true;
                    emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                                commandReqData.devCommand, QString("Normal"), QStringList(), QStringList(), commandReqData);
                    res = true;
                }
            }
        }
        if(!res) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ExectCustomCommand, getUniqId(),
                                        commandReqData.devCommand, QString("Error"), QStringList(), QStringList(), commandReqData);
        }
    }
        break;
    default : break;
    }

    if(!commandArrayReplyData.isEmpty() && res == true) {
        if(getState() == STATE_DISCONNECTED) { // если что-то есть в ответе - меняем статус на Connected
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Connected, getUniqId(),
                                        commandReqData.devCommand, QString("Connected"), QStringList(), QStringList(), commandReqData);
            setState(DeviceAbstract::STATE_GET_TYPE);
        }

        crcRes = crc.crc8_dallas(commandArrayReplyData.data(), commandArrayReplyData.length()-1);
        if(crcRes != (0xff & commandArrayReplyData.at(commandArrayReplyData.length()-1))) {
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqId(),
                                        commandReqData.devCommand, QString("Disconnected"), QStringList(), QStringList(), commandReqData);
            setState(DeviceAbstract::STATE_DISCONNECTED);
            return false;
        }
    } else {
        state = STATE_DISCONNECTED;
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqId(),
                                    commandReqData.devCommand, QString("Status disconnected"), QStringList(), QStringList(), commandReqData);
    }

    if(getState() == STATE_START_INIT) {
        if((lls_data.settings.get.isValid) && (lls_data.errors.isValid)
                && (lls_data.password.get.value.isValid) && (lls_data.calibrateTable.get.isValid)
                && (lls_data.llssValues.isValid)) {
            setState(DeviceAbstract::STATE_NORMAL_READY);
            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Inited, getUniqId(),
                                        commandReqData.devCommand, QString("Inited"), QStringList(), QStringList(), commandReqData);
        }
    }
    return res;
}

CommandController::sCommandData Progress_tmk24::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.isNeedAckMessage = false;
    command.operationHeader = "check dev is connected";
    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    return command;
}

CommandController::sCommandData Progress_tmk24::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.isNeedAckMessage = false;
    command.operationHeader = "check dev password";
    command.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk24::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.operationHeader = "init dev after connecting";
    command.isNeedAckMessage = false;
    command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_errors;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
    listCommand.push_back(command);
    return listCommand;
}

CommandController::sCommandData Progress_tmk24::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.isNeedAckMessage = false;
    command.operationHeader = "get dev type";
    command.devCommand = (int)Progress_tmk24Data::lls_read_settings;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk24::getCommandCustom(QString operation) {
    return getCommandCustom(operation, QPair<QStringList,QStringList>());
}

QList<CommandController::sCommandData> Progress_tmk24::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
    CommandController::sCommandData tcommand;
    tcommand.operationHeader = operation;
    if(operation == "set current level value as min") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Progress_tmk24Data::lls_calibrate_min;
        command.push_back(tcommand);
    } else if(operation == "check device is connected") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.commandType = CommandController::E_CommandType_command_without_request;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
        command.push_back(tcommand);
    } else if(operation == "set current level value as max") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_calibrate_max;
        command.push_back(tcommand);
    } else if(operation == "get current dev settings") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
        command.push_back(tcommand);
    } else if(operation == "get get available dev tarrir id") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
        command.push_back(tcommand);
    } else if(operation == "get current dev settings without ack dialog") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = false;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
        command.push_back(tcommand);
    } else if(operation == "set current dev settings") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_write_settings;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else if(operation == "read current dev errors") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_errors;
        command.push_back(tcommand);
    } else if(operation == "set current dev tar table") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_write_cal_table;
        // key
        for(auto i:data.first) { // string index
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) { // qstringList values
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else if(operation == "read current dev tar table") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true;
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
        command.push_back(tcommand);
    } else if(operation == "change current dev id") {
        // first read settings
        tcommand.deviceIdent = getUniqId();
        tcommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
        tcommand.isNeedAckMessage = false;
        tcommand.args.key.clear();
        tcommand.args.value.clear();
        tcommand.commandOptionData.clear();
        command.push_back(tcommand);
        // потоm запись id
        tcommand.deviceIdent = getUniqId();
        tcommand.devCommand = (int)Progress_tmk24Data::lls_write_settings;
        tcommand.isNeedAckMessage = true;
        // key
        for(auto i:data.first) { // string index
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) { // qstringList values
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else {
        qDebug() << "getCommandCustom -type unknown!";
    }
    return command;
}

QList<CommandController::sCommandData> Progress_tmk24::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.commandOptionData.clear();
    command.deviceIdent = getUniqId();
    command.operationHeader = "typical command get current data";
    command.isNeedAckMessage = false;
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_cnt;
    listCommand.push_back(command);
    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
    listCommand.push_back(command);
    return listCommand;
}
