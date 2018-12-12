#include <QDebug>
#include "Progress_tmk24.h"
#include "other/crc.h"

Progress_tmk24::Progress_tmk24(std::vector<std::string> keyValue, std::vector<std::string> value) {
    auto propIter = value.begin();
    for(auto itemKey: keyValue) {
        if(itemKey == "id") {
            this->deviceIdent.id = *propIter;
        }
        if(itemKey == "header") {
            this->deviceIdent.header = *propIter;
        }
        if(itemKey == "password") {
            this->lls_data.password.session.value = *propIter;
            this->lls_data.password.session.isValid = true;
        }
        propIter++;
    }
    this->state = STATE_DISCONNECTED;
    this->service = std::make_shared<ServiceDevicesAbstract>();
    setDefaultValues();

    if(deviceIdent.id.empty() || deviceIdent.header.empty()) {
        throw std::string("if does not include all properties");
    }
}

Progress_tmk24::~Progress_tmk24() {

}

std::string Progress_tmk24::getDevTypeName() {
    return std::string(Progress_tmk24::name);
}

std::string Progress_tmk24::getDevHeader() {
    return deviceIdent.header;
}

void Progress_tmk24::setDevHeader(std::string header) {
    deviceIdent.header = header;
}

void Progress_tmk24::setDefaultValues() {
    this->settings.k1 = 0;
    this->settings.k2 = 0;
    this->settings.netAddress = std::stoi(deviceIdent.id);
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
    return service.get();
}

std::pair<std::vector<std::string>,std::vector<std::string>> Progress_tmk24::getPropertyData() {
    std::pair<std::vector<std::string>,std::vector<std::string>> res;
    res.first.push_back("devTypeName");
    res.second.push_back(getDevTypeName());
    res.first.push_back("serialNum");
    res.second.push_back((lls_data.serialNum.value.empty() || lls_data.serialNum.value.at(0) > 0x255) ? std::string("Не присвоен") : lls_data.serialNum.value);
    res.first.push_back("netAddress");
    res.second.push_back(std::to_string(settings.netAddress));
    res.first.push_back("versionFirmare");
    res.second.push_back(lls_data.firmware.isValid ? lls_data.firmware.value : "NA");
    res.first.push_back("authIsNormal");
    res.second.push_back(std::to_string(lls_data.password.get.authIsNormal));
    res.first.push_back("password");
    res.second.push_back(lls_data.password.get.value.value);
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("header");
    res.second.push_back(deviceIdent.header);
    return res;
}

std::pair<std::vector<std::string>,std::vector<std::string>> Progress_tmk24::getCurrentData() {
    std::pair<std::vector<std::string>,std::vector<std::string>> res;
    res = getPropertyData();
    res.first.push_back("fuelLevel");
    res.second.push_back(lls_data.fuelLevel.isValid == true ? std::to_string(lls_data.fuelLevel.value.value_u32) : std::to_string(0));
    res.first.push_back("fuelProcent");
    res.second.push_back(lls_data.fuelProcent.isValid ? std::to_string(lls_data.fuelProcent.value.value_u16) : std::to_string(0));
    res.first.push_back("cnt");
    res.second.push_back(lls_data.cnt.isValid ? std::to_string(lls_data.cnt.value.value_u32) : std::to_string(0));
    res.first.push_back("freq");
    res.second.push_back(lls_data.freq.isValid ? std::to_string(lls_data.freq.value.value_u16) : std::to_string(0));
    res.first.push_back("temp");
    res.second.push_back(lls_data.temp.isValid ? std::to_string(lls_data.temp.value.value_i) : std::to_string(0));
    res.first.push_back("noiseDetected");
    res.second.push_back(std::to_string(lls_data.noiseDetected));
    res.first.push_back("chartValue");
    res.second.push_back(lls_data.freq.isValid == true ? std::to_string(lls_data.freq.value.value_u32) : std::to_string(0));
    return res;
}

std::pair<std::vector<std::string>,std::vector<std::string>> Progress_tmk24::getSettings() {
    std::pair<std::vector<std::string>,std::vector<std::string>> res;
    if(lls_data.settings.get.isValid) {
        res.first.push_back("device_value");
        res.second.push_back(getDevTypeName());
        res.first.push_back("versionFirmare");
        res.second.push_back(lls_data.firmware.isValid ? lls_data.firmware.value : "NA");
        res.first.push_back("k1_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.k1));
        res.first.push_back("k2_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.k2));
        res.first.push_back("typeTempCompensation_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.thermoCompensationType));
        res.first.push_back("periodicSendType_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.periodicSendType));
        res.first.push_back("periodicSendTime_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.periodicSendTime));
        res.first.push_back("typeOutMessage_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.outputValue));
        res.first.push_back("typeInterpolation_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.interpolationType));
        res.first.push_back("typeFiltration_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.filterType));
        res.first.push_back("filterLenghtMediana_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.medianLength));
        res.first.push_back("filterAvarageValueSec_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.avarageLength));
        res.first.push_back("filterValueQ_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.q));
        res.first.push_back("filterValueR_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.r));
        res.first.push_back("minLevelValue_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.minLevel));
        res.first.push_back("maxLevelValue_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.maxLevel));
        res.first.push_back("masterSlaveModes_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.masterMode));
        res.first.push_back("baudrateRs232Values_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.rs232Speed));
        res.first.push_back("baudrateRs485Values_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.rs485Speed));
        res.first.push_back("masterSlaveFullCountes_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.slaveCount));
        res.first.push_back("masterSlaveSlaveId_1_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.slaveAddr[0]));
        res.first.push_back("masterSlaveSlaveId_2_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.slaveAddr[1]));
        res.first.push_back("masterSlaveSlaveId_3_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.slaveAddr[2]));
        res.first.push_back("masterSlaveSlaveId_4_value");
        res.second.push_back(std::to_string(lls_data.settings.get.value.slaveAddr[3]));
        res.first.push_back("typeFuel");
        res.second.push_back(std::to_string(lls_data.settings.get.value.waterMode));
    }
    return res;
}

std::pair<std::vector<std::string>,std::vector<std::string>> Progress_tmk24::getErrors() {
    std::pair<std::vector<std::string>,std::vector<std::string>> ret;
    if(lls_data.errors.isValid) {
        ret.first.push_back("GenFreq0");
        ret.second.push_back(std::to_string(lls_data.errors.errors.GenFreq0));
        ret.first.push_back("MaxFreqOut");
        ret.second.push_back(std::to_string(lls_data.errors.errors.MaxFreqOut));
        ret.first.push_back("MinFreqOut");
        ret.second.push_back(std::to_string(lls_data.errors.errors.MinFreqOut));
        ret.first.push_back("NotCalibrated");
        ret.second.push_back(std::to_string(lls_data.errors.errors.NotCalibrated));
        ret.first.push_back("QeueManagerError");
        ret.second.push_back(std::to_string(lls_data.errors.errors.QeueManagerError));
        ret.first.push_back("ReplayNotComeRs232");
        ret.second.push_back(std::to_string(lls_data.errors.errors.ReplayNotComeRs232));
        ret.first.push_back("ReplayNotComeRs485");
        ret.second.push_back(std::to_string(lls_data.errors.errors.ReplayNotComeRs485));
        ret.first.push_back("Rs232Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Rs232Error));
        ret.first.push_back("Rs485Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Rs485Error));
        ret.first.push_back("Slave1Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Slave1Error));
        ret.first.push_back("Slave2Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Slave2Error));
        ret.first.push_back("Slave3Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Slave3Error));
        ret.first.push_back("Slave4Error");
        ret.second.push_back(std::to_string(lls_data.errors.errors.Slave4Error));
    }
    return ret;
}

std::vector<int> Progress_tmk24::getChart() {
    return chartData;
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

std::string Progress_tmk24::getUniqId() {
    return deviceIdent.id;
}

//bool Progress_tmk24::makeDataToCommand(CommandController::sCommandData &commandData) {
//    bool res = false;
//    if(!commandData.deviceIdent.isEmpty()) {
//        try {
//            commandData.commandOptionData.clear();
//            commandData.commandOptionData.push_back(0x31);
//            commandData.delay_send_ms = 100;
//            // id addr
//            commandData.commandOptionData.push_back(commandData.deviceIdent.toInt());
//            // command byte
//            commandData.commandOptionData.push_back(commandData.devCommand);
//            switch(commandData.devCommand) {
//            case Progress_tmk24Data::lls_read_lvl_once: break;
//            case Progress_tmk24Data::lls_send_data_enable: break;
//            case Progress_tmk24Data::lls_set_send_time: break;
//            case Progress_tmk24Data::lls_send_data_default: break;
//            case Progress_tmk24Data::lls_read_cnt: break;
//            case Progress_tmk24Data::lls_read_lvl_all: break;
//            case Progress_tmk24Data::lls_read_settings: break;

//            case Progress_tmk24Data::lls_write_settings: {
//                // сперва заносим текущий пароль для разрешения доступа
//                QByteArray passArray;
//                if(lls_data.password.session.isValid) {
//                    if(!lls_data.password.session.value.isEmpty()) {
//                        int passLen = lls_data.password.session.value.length();
//                        for(int passCounter=0; passCounter<passLen; passCounter++) {
//                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
//                        }
//                    }
//                }
//                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
//                    passArray.push_back((char)0);
//                }
//                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
//                commandData.commandOptionData.push_back(0xFF);
//                commandData.commandOptionData.push_back(0xFF);

//                Progress_tmk24Data::T_settings tSettings;
//                if(lls_data.settings.get.isValid) {
//                    memcpy(&tSettings, &lls_data.settings.get.value, sizeof(tSettings));
//                    for(int i=0; i<commandData.args.key.size(); i++) {
//                        if(commandData.args.key.at(i) == "k1_value") {
//                            tSettings.k1 = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "k2_value") {
//                            tSettings.k2 = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "typeTempCompensation_value") {
//                            tSettings.thermoCompensationType = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "netAddress_value") {
//                            tSettings.netAddress = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "periodicSendType_value") {
//                            tSettings.periodicSendType = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "periodicSendTime_value") {
//                            tSettings.periodicSendTime = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "typeOutMessage_value") {
//                            tSettings.outputValue = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "typeInterpolation_value") {
//                            tSettings.interpolationType = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "typeFiltration_value") {
//                            tSettings.filterType = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "filterLenghtMediana_value") {
//                            tSettings.medianLength = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "filterAvarageValueSec_value") {
//                            tSettings.avarageLength = commandData.args.value.at(i).toInt(); //
//                        } else if(commandData.args.key.at(i) == "filterValueQ_value") {
//                            tSettings.q = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "filterValueR_value") {
//                            tSettings.r = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "minLevelValue_value") {
//                            tSettings.minLevel = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "maxLevelValue_value") {
//                            tSettings.maxLevel = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveModes_value") {
//                            tSettings.masterMode = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "baudrateRs232Values_value") {
//                            tSettings.rs232Speed = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "baudrateRs485Values_value") {
//                            tSettings.rs485Speed = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "typeFuel") {
//                            tSettings.waterMode = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveFullCountes_value") {
//                            tSettings.slaveCount = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_1_value") {
//                            tSettings.slaveAddr[0] = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_2_value") {
//                            tSettings.slaveAddr[1] = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_3_value") {
//                            tSettings.slaveAddr[2] = commandData.args.value.at(i).toInt();
//                        } else if(commandData.args.key.at(i) == "masterSlaveSlaveId_4_value") {
//                            tSettings.slaveAddr[3] = commandData.args.value.at(i).toInt();
//                        } else {
//                            qDebug() << "settings udnefined type parcing";
//                        }
//                    }
//                    commandData.delay_send_ms = 150;
//                    commandData.commandOptionData.insert(13, (char*)&tSettings, sizeof(Progress_tmk24Data::T_settings));
//                    while(commandData.commandOptionData.size() != 62) {
//                        commandData.commandOptionData.push_back(0xFF);
//                    }
//                }
//            }
//                break;

//            case Progress_tmk24Data::lls_read_cal_table:
//                commandData.delay_send_ms = 150;
//                break;

//            case Progress_tmk24Data::lls_write_cal_table: {
//                // сперва заносим текущий пароль для разрешения доступа
//                QByteArray passArray;
//                if(lls_data.password.session.isValid) {
//                    if(!lls_data.password.session.value.isEmpty()) {
//                        int passLen = lls_data.password.session.value.length();
//                        for(int passCounter=0; passCounter<passLen; passCounter++) {
//                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
//                        }
//                    }
//                }
//                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
//                    passArray.push_back((char)0);
//                }
//                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
//                commandData.delay_send_ms = 150;
//                commandData.commandOptionData.push_back((uint8_t)commandData.args.value.size());
//                for(uint8_t i=0; i<(Progress_tmk24Data::TAR_TABLE_SIZE); i++) {
//                    if(i < commandData.args.value.size()) {
//                        commandData.commandOptionData.push_back((uint32_t)commandData.args.value.at(i).toUInt() & 0xFF);
//                        commandData.commandOptionData.push_back(((uint32_t)commandData.args.value.at(i).toUInt() & 0xFF00) >> 8);
//                        commandData.commandOptionData.push_back((uint32_t)commandData.args.key.at(i).toUInt() & 0xFF);
//                        commandData.commandOptionData.push_back(((uint32_t)commandData.args.key.at(i).toUInt() & 0xFF00) >> 8);
//                    } else {
//                        commandData.commandOptionData.push_back((char)0);
//                        commandData.commandOptionData.push_back((char)0);
//                        commandData.commandOptionData.push_back((char)0);
//                        commandData.commandOptionData.push_back((char)0);
//                    }
//                }
//            }
//                break;
//            case Progress_tmk24Data::lls_calibrate_min:
//            case Progress_tmk24Data::lls_calibrate_max: {
//                // заносим текущий пароль для разрешения доступа
//                // значение заносится в самоме датчике
//                QByteArray passArray;
//                if(lls_data.password.session.isValid) {
//                    if(!lls_data.password.session.value.isEmpty()) {
//                        int passLen = lls_data.password.session.value.length();
//                        for(int passCounter=0; passCounter<passLen; passCounter++) {
//                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
//                        }
//                    }
//                }
//                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
//                    passArray.push_back((char)0);
//                }
//                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
//            }
//                break;
//            case Progress_tmk24Data::lls_read_errors: break;
//            case Progress_tmk24Data::lls_set_serial_number: break;
//            case Progress_tmk24Data::lls_read_serial_number: break;
//            case Progress_tmk24Data::lls_set_personal: break;
//            case Progress_tmk24Data::lls_read_personal: break;
//            case Progress_tmk24Data::lls_set_new_password: {
//                if(!commandData.commandOptionData.isEmpty()) {
//                }
//            }
//                break;

//            case Progress_tmk24Data::lls_check_address_and_pass: {
//                // заносим текущий пароль для разрешения доступа
//                // значение заносится в самоме датчике
//                QByteArray passArray;
//                if(lls_data.password.session.isValid) {
//                    if(!lls_data.password.session.value.isEmpty()) {
//                        int passLen = lls_data.password.session.value.length();
//                        for(int passCounter=0; passCounter<passLen; passCounter++) {
//                            passArray.push_back(lls_data.password.session.value.at(passCounter).toLatin1());
//                        }
//                    }
//                }
//                while(passArray.size() < Progress_tmk24Data::PASSWORD_SIZE) {
//                    passArray.push_back((char)0);
//                }
//                commandData.commandOptionData.insert(commandData.commandOptionData.size(), passArray);
//            }
//                break;
//            case Progress_tmk24Data::lls_run_bootloader: break;
//            default : break;
//            }
//            Crc crcCalc;
//            uint8_t crcResult = 0;
//            crcResult = crcCalc.crc8_dallas(commandData.commandOptionData.data(), commandData.commandOptionData.length());
//            commandData.commandOptionData.push_back(crcResult);
//            res = true;
//        } catch(...) {
//            qDebug("Device: makeDataToCommand -catch!");
//        }
//    } else {
//        qDebug() << "Device: makeDataToCommand paramIsNull!";
//    }
//    return res;
//}

//bool Progress_tmk24::placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) {
//    std::pair<std::vector<std::string>, std::vector<std::string>> res;
//    bool replyIsValid = false;
//    Crc crc;
//    uint8_t crcRes = 0;
//    uint16_t frequency = 0;
//    uint16_t value = 0;
//    if(!commandArrayReplyData.isEmpty()) {
//        if(getState() == STATE_DISCONNECTED) { // если что-то есть в ответе - меняем статус на Connected
//            emit eventDeviceUpdateState(Type_DeviceEvent_Connected, commandReqData.deviceIdent, res.first, res.second, commandReqData);
//            setState(DeviceAbstract::STATE_GET_TYPE);
//        }
//        crcRes = crc.crc8_dallas(commandArrayReplyData.data(), commandArrayReplyData.length()-1);
//        if(crcRes != (0xff & commandArrayReplyData.at(commandArrayReplyData.length()-1))) {
//            emit eventDeviceUpdateState(Type_DeviceEvent_Disconnected, commandReqData.deviceIdent, res.first, res.second, commandReqData);
//            setState(DeviceAbstract::STATE_DISCONNECTED);
//            return false;
//        } else {
//            replyIsValid = true;
//        }
//    } else {
//        state = STATE_DISCONNECTED;
//            emit eventDeviceUpdateState(Type_DeviceEvent_Disconnected, commandReqData.deviceIdent, res.first, res.second, commandReqData);
//    }

//    // мы же знаем какую команду отправили, ее и ожидаем
//    // внутри смотрим что она совпадает в пакете
//    // ответ должен быть на отправленную команду
//    switch(commandReqData.devCommand) {
//    case Progress_tmk24Data::lls_read_lvl_once: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_lvl_once";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                lls_data.temp.value.value_i = (int8_t)(0xFF & commandArrayReplyData.at(3));
//                lls_data.temp.isValid = true;
//                value = 0;
//                value = 0xFF & commandArrayReplyData.at(5);
//                value = value << 8;
//                value |= 0xFF & commandArrayReplyData.at(4);
//                frequency = 0xFF & commandArrayReplyData.at(7);
//                frequency = frequency << 8;
//                frequency |= 0xFF & commandArrayReplyData.at(6);
//                lls_data.fuelLevel.value.value_u32 = value;
//                if(lls_data.settings.get.isValid) {
//                    lls_data.fuelProcent.value.value_u32 = ((float)((float)value/lls_data.settings.get.value.maxLevel)*100);
//                    lls_data.fuelProcent.isValid = true;
//                } else {
//                    lls_data.fuelProcent.value.value_u32 = 0;
//                }
//                lls_data.fuelLevel.isValid = true;
//                lls_data.freq.value.value_u32 = frequency;
//                lls_data.freq.isValid = true;

//                chartData.push_back(lls_data.fuelLevel.value.value_u32 + (rand()%1));
//                while(chartData.size() > 50) {
//                    chartData.pop_front();
//                }
//                replyIsValid = true;
//            }
//        } else {
//            // здесь не нужно ничего
//            // т.к. если нет данных
//            // оно само станет Disconnected
//            // обработка требуется для выполнения команд по записи/чтения настроек и пр.
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getCurrentData().first;
//        res.second << getCurrentData().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;
//        // TOOD:
//    case Progress_tmk24Data::lls_send_data_enable: break;
//    case Progress_tmk24Data::lls_set_send_time: break;
//    case Progress_tmk24Data::lls_send_data_default: break;
//    case Progress_tmk24Data::lls_read_lvl_all: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_lvl_all";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                lls_data.llssValues.values.slave_count = (0xFF & commandArrayReplyData.at(3));
//                lls_data.llssValues.values.summed_volume = (0xFF & commandArrayReplyData.at(5));
//                lls_data.llssValues.values.summed_volume = lls_data.llssValues.values.summed_volume << 8;
//                lls_data.llssValues.values.summed_volume |= (0xFF & commandArrayReplyData.at(4));
//                //
//                lls_data.llssValues.values.send_value = 0xFF & commandArrayReplyData.at(8);
//                lls_data.llssValues.values.send_value = lls_data.llssValues.values.send_value << 8;
//                lls_data.llssValues.values.send_value |= (0xFF & commandArrayReplyData.at(7));
//                //
//                int offset_counter = 11;
//                for(uint8_t i=0; i<4; i++) {
//                    lls_data.llssValues.values.Temperature[i] = (int8_t)(0xFF & commandArrayReplyData.at(offset_counter));
//                    offset_counter++;
//                    //--
//                    lls_data.llssValues.values.Level[i] = 0xFF & commandArrayReplyData.at(offset_counter);
//                    offset_counter++;
//                    //--
//                    lls_data.llssValues.values.Level[i] |= (0xFF & commandArrayReplyData.at(offset_counter)) << 8;
//                    offset_counter++;
//                    //--
//                    lls_data.llssValues.values.Frequency[i] = 0xFF & commandArrayReplyData.at(offset_counter);
//                    lls_data.llssValues.values.Frequency[i] = lls_data.llssValues.values.Frequency[i] << 8;
//                    offset_counter++;
//                    lls_data.llssValues.values.Frequency[i] |= (0xFF & commandArrayReplyData.at(offset_counter));
//                    lls_data.llssValues.values.Frequency[i] = lls_data.llssValues.values.Frequency[i] << 8;
//                    offset_counter++;
//                }
//                lls_data.llssValues.isValid = true;
//                replyIsValid;
//            }
//        } else {
//            // здесь не нужно ничего
//            // т.к. если нет данных
//            // оно само станет Disconnected
//            // обработка требуется для выполнения команд по записи/чтения настроек и пр.
//        }

//        if(replyIsValid) {
//            if(lls_data.fuelLevel.isValid && lls_data.fuelProcent.isValid && lls_data.cnt.isValid
//                    && lls_data.freq.isValid && lls_data.temp.isValid && lls_data.fuelLevel.isValid) {
//                res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//            }
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getCurrentData().first;
//        res.second << getCurrentData().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_read_settings: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_settings";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 22) {
//                    char *pbuf = (commandArrayReplyData.data() + 4);
//                    lls_data.serialNum.value = std::string::fromUtf8(pbuf, Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
//                    lls_data.serialNum.isValid = true;
//                    pbuf = (commandArrayReplyData.data() + 4 + Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
//                    lls_data.firmware.value = std::string::fromUtf8(pbuf,  Progress_tmk24Data::FIRMWARE_VERSION_STRING_SIZE);
//                    lls_data.firmware.isValid = true;

//                    // проверка типа
//                    if(commandArrayReplyData.at(3) == Progress_tmk24Data::type_lls_tmk24) {
//                        Progress_tmk24Data::T_settings *pSettings = (Progress_tmk24Data::T_settings*)(commandArrayReplyData.data() + 34);
//                        if(pSettings->netAddress == commandArrayReplyData.at(Progress_tmk24Data::param_id_address)) {
//                            lls_data.settings.get.value = *pSettings;
//                            lls_data.settings.get.isValid = true;
//                            replyIsValid = true;
//                            if(getState() == STATE_GET_TYPE) {
//                                setState(DeviceAbstract::STATE_CHECK_PASSWORD);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ReadyReadProperties, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_write_settings:
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_write_settings";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 4) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        replyIsValid = true;
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;

//    case Progress_tmk24Data::lls_read_cal_table: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_cal_table";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 45) {
//                    std::vector<std::string> keys;
//                    std::vector<std::string> values;
//                    memset(&lls_data.calibrateTable.get.table, 0, sizeof(Progress_tmk24Data::T_calibrationTable));
//                    lls_data.calibrateTable.get.table.TableSize = commandArrayReplyData.at(3);
//                    int index = 0;
//                    for(int i=0; i<lls_data.calibrateTable.get.table.TableSize; i++) {
//                        lls_data.calibrateTable.get.table.y[i] = (0xFF & commandArrayReplyData.at(index+4));
//                        index++;
//                        lls_data.calibrateTable.get.table.y[i] |= ((0xFF & commandArrayReplyData.at(index+4)) << 8);
//                        index++;
//                        lls_data.calibrateTable.get.table.x[i] = (0xFF & commandArrayReplyData.at(index+4));
//                        index++;
//                        lls_data.calibrateTable.get.table.x[i] |= ((0xFF & commandArrayReplyData.at(index+4)) << 8);
//                        index++;
//                        keys.push_back("y");
//                        values.push_back(std::to_string(lls_data.calibrateTable.get.table.y[i]));
//                        keys.push_back("x");
//                        values.push_back(std::to_string(lls_data.calibrateTable.get.table.x[i]));
//                    }
//                    lls_data.calibrateTable.get.isValid = true;
//                    replyIsValid = true;
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_write_cal_table: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_write_cal_table";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 4) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        if(commandReqData.isNeedAckMessage) {
//                            replyIsValid = true;
//                        }
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;
//    case Progress_tmk24Data::lls_calibrate_min: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_calibrate_min";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 3) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        replyIsValid = true;
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_calibrate_max: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_calibrate_max";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 3) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        replyIsValid = true;
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_read_errors: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_errors";
//        // если ожидаемая команда совпадает с пакетом
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 5) { // TODO: 10?
//                    Progress_tmk24Data::T_errors t_erros;
//                    memcpy(&t_erros, (commandArrayReplyData.data() + 3), sizeof(t_erros));
//                    memcpy(&lls_data.errors, &t_erros, sizeof(t_erros));
//                    lls_data.errors.isValid = true;
//                    replyIsValid = true;
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;
//    case Progress_tmk24Data::lls_set_serial_number: break;
//    case Progress_tmk24Data::lls_read_serial_number: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_serial_number";
//        // если ожидаемая команда совпадает с пакетом
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 22) {
//                    lls_data.serialNum.value = std::string::fromUtf8((commandArrayReplyData.data() + 3),
//                                                                 Progress_tmk24Data::SERIALNUMBER_STRING_SIZE);
//                    lls_data.serialNum.isValid = true;
//                }
//                replyIsValid = true;
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_set_personal: break;
//    case Progress_tmk24Data::lls_read_personal: break;
//    case Progress_tmk24Data::lls_set_new_password:
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_set_new_password";
//        // если ожидаемая команда совпадает с пакетом
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() >= 4) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        replyIsValid = true;
//                    }
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;

//    case Progress_tmk24Data::lls_check_address_and_pass: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_check_address_and_pass";
//        // если ожидаемая команда совпадает с пакетом
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                if(commandArrayReplyData.size() > 4) {
//                    if(commandArrayReplyData.at(3) == 0) {
//                        lls_data.password.get.value.isValid = true; // TOOD: обработка ошибок
//                        lls_data.password.get.authIsNormal = true;
//                    } else {
//                        lls_data.password.get.value.isValid = true;
//                        lls_data.password.get.authIsNormal = false;
//                    }
//                    replyIsValid = true;
//                    setState(STATE_START_INIT);
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getSettings().first;
//        res.second << getSettings().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;

//    case Progress_tmk24Data::lls_run_bootloader: // TODO:
//        break;
//    case Progress_tmk24Data::lls_read_cnt: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "lls_read_cnt";
//        if(!commandArrayReplyData.isEmpty()) { // TODO: проверка только на пустоту
//            // возможно обращение к несуществующему элементу
//            // если ожидаемая команда совпадает с пакетом
//            if(commandReqData.devCommand == (uint8_t)commandArrayReplyData.at(2)) {
//                uint32_t cnt = 0;
//                if(commandArrayReplyData.size() >= 8) {
//                    cnt = 0xFF & commandArrayReplyData.at(7);
//                    cnt = cnt << 8;
//                    cnt |= 0xFF & commandArrayReplyData.at(6);
//                    cnt = cnt << 8;
//                    cnt |= 0xFF & commandArrayReplyData.at(5);
//                    cnt = cnt << 8;
//                    cnt |= 0xFF & commandArrayReplyData.at(4);

//                    uint32_t maxProcentTollerance = lls_data.cnt.value.value_u32 / 100 * 5;
//                    if(lls_data.cnt.isValid) {
//                        lls_data.cnt.value.value_u32 = cnt;
//                        lls_data.cnt.history.push_back(lls_data.cnt.value.value_u32);
//                        if(lls_data.cnt.history.size() > Progress_tmk24Data::MAX_SIZE_HISTORY_CNT_vector) {
//                            lls_data.cnt.history.pop_front();
//                        }
//                    }
//                    if(lls_data.cnt.value.value_u32 != 0) {
//                        if(!lls_data.cnt.history.empty()) {
//                            lls_data.noiseDetected = false;
//                            for(auto i : lls_data.cnt.history) {
//                                if(cnt >= (i - maxProcentTollerance)
//                                        && cnt <= (i + maxProcentTollerance)) {
//                                } else {
//                                    lls_data.noiseDetected = true;
//                                }
//                            }
//                        }
//                    }
//                    lls_data.cnt.value.value_u32 = cnt;
//                    lls_data.cnt.isValid = true;
//                    replyIsValid = true;
//                }
//            }
//        }
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        res.first << getCurrentData().first;
//        res.second << getCurrentData().second;
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;
//    default : break;
//    }

//    if(getState() == STATE_START_INIT) {
//        if((lls_data.settings.get.isValid) && (lls_data.errors.isValid)
//                && (lls_data.password.get.value.isValid) && (lls_data.calibrateTable.get.isValid)
//                && (lls_data.llssValues.isValid)) {
//            setState(DeviceAbstract::STATE_NORMAL_READY);
//            emit eventDeviceUpdateState(Type_DeviceEvent_Inited, commandReqData.deviceIdent, res.first, res.second, commandReqData);
//        }
//    }
//    return replyIsValid;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandToCheckConnected() {
//    Qvector<CommandController::sCommandData> commandvector;
//    CommandController::sCommandData unitCommand;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    unitCommand.deviceIdent = getUniqId();
//    unitCommand.isNeedAckMessage = false;
//    unitCommand.operationHeader = "check dev is connected";
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_errors;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    return commandvector;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandtoCheckPassword() {
//    Qvector<CommandController::sCommandData> commandvector;
//    CommandController::sCommandData unitCommand;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    unitCommand.deviceIdent = getUniqId();
//    unitCommand.isNeedAckMessage = false;
//    unitCommand.operationHeader = "check dev password";
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    return commandvector;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandvectorToInit() {
//    Qvector<CommandController::sCommandData> commandvector;
//    CommandController::sCommandData unitCommand;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    unitCommand.deviceIdent = getUniqId();
//    unitCommand.operationHeader = "init dev after connecting";
//    unitCommand.isNeedAckMessage = false;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_errors;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    return commandvector;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandvectorToUpdate() {
//    Qvector<CommandController::sCommandData> vectorCommand;
//    CommandController::sCommandData unitCommand;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    unitCommand.deviceIdent = getUniqId();
//    unitCommand.operationHeader = "update device";
//    unitCommand.isNeedAckMessage = false;
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(unitCommand);
//    vectorCommand.push_back(unitCommand);
//    return vectorCommand;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandToGetType() {
//    Qvector<CommandController::sCommandData> commandvector;
//    CommandController::sCommandData unitCommand;
//    unitCommand.deviceIdent = getUniqId();
//    unitCommand.isNeedAckMessage = false;
//    unitCommand.operationHeader = "get dev type";
//    unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//    unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(unitCommand);
//    commandvector.push_back(unitCommand);
//    return commandvector;
//}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandCustom(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>> data) {
//    Qvector <CommandController::sCommandData> commandvector;
//    CommandController::sCommandData unitCommand;
//    unitCommand.operationHeader = operation;
//    if(operation == "update device") {
//        commandvector = getCommandvectorToUpdate();
//    }
//    if(operation == "setTableFromFrontEnd") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
//        pService->placeTableFromFrontEnd(getUniqId(), data.first, data.second);
//    }
//    if(operation == "sendReqWriteTarrirAllDev") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
//        for(auto i:pService->requestWriteTableToAllDevice()) {
//            // извлекаем данные из таблциц
//            // отправляем всем dev из списка команду на запись таблиц
//            std::pair<std::vector<std::string>,std::vector<std::string>> table;
//            data = pService->getTableAtDeviceToPair(i);
//            unitCommand.deviceIdent = getUniqId();
//            unitCommand.isNeedAckMessage = true;
//            unitCommand.devCommand = (int)Progress_tmk24Data::lls_write_cal_table;
//            unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//            // key, value
//            unitCommand.args.key << data.first;
//            unitCommand.args.value << data.second;
//            makeDataToCommand(unitCommand);
//            commandvector.push_back(unitCommand);
//        }
//    }
//    if(operation == "set current level value as min") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_calibrate_min;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "check device is connected") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.commandType = CommandController::E_CommandType_command_without_request;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_check_address_and_pass;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "set current level value as max") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_calibrate_max;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "get current dev settings") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "get get available dev tarrir id") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "get current dev settings without ack dialog") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = false;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "set current dev settings") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_write_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        // key, value
//        unitCommand.args.key << data.first;
//        unitCommand.args.value << data.second;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "read current dev errors") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_errors;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "read current dev tar table") {
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.isNeedAckMessage = true;
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
//    if(operation == "change current dev id") {
//        // first read settings
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        unitCommand.isNeedAckMessage = false;
//        unitCommand.args.key.clear();
//        unitCommand.args.value.clear();
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//        // потоm запись id
//        unitCommand.deviceIdent = getUniqId();
//        unitCommand.devCommand = (int)Progress_tmk24Data::lls_write_settings;
//        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
//        unitCommand.isNeedAckMessage = true;
//        // key, value
//        unitCommand.args.key << data.first;
//        unitCommand.args.value << data.second;
//        makeDataToCommand(unitCommand);
//        commandvector.push_back(unitCommand);
//    }
////    // TODO:
////    if(operation == "getTarMaxCountStep") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    }

////    // TODO:
////    if(operation == "getTarMaxCountStep") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    }

////    // TODO:
////    if(operation == "sendReqExportTarrirAllDevToCsv") { // pathFile
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        std::vector<std::string> exportvector;
////        std::string str;
////        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////            int devAll = pService->getDeviceCount();
////            // id[devType], объем, уровень топлива
////            for(int devCounter=0; devCounter<devAll; devCounter++) {
////                std::vector<std::string> litersvector;
////                std::vector<std::string> fuelLevelvector;
////                // получаем стоблец с liters и fuelLevel
////                std::pair<std::vector<std::string>,std::vector<std::string>> tableData;
////                tableData = pService->getTableAtDeviceToPair(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(devCounter));
////                for(int tableCounter=0; tableCounter<tableData.first.size(); tableCounter++) {
////                    // lites
////                    litersvector << tableData.first.at(tableCounter);
////                    // fuelLevel
////                    fuelLevelvector << tableData.second.at(tableCounter);
////                }
////                str.clear();
////                str.push_back("\"" + std::string("ID/Тип") + "\"" + ",");
////                str.push_back("\"" + std::string("Объем") + "\"" + ",");
////                str.push_back("\"" + std::string("Уровень") + "\"");
////                exportvector.push_back(str);
////                for(int makeCounter=0; makeCounter<litersvector.size(); makeCounter++) {
////                    str.clear();
////                    str.push_back("\"" + std::string("ID%1[%2]").arg(pService->getDeviceProperty(devCounter).at(1)).arg(pService->getDeviceProperty(devCounter).at(0)) + "\"" + ",");
////                    str.push_back("\"" + ((litersvector.size() >= makeCounter) ? (litersvector.at(makeCounter) + "\"" + ",") : std::string("Нет данных")));
////                    str.push_back("\"" + ((fuelLevelvector.size() >= makeCounter) ? (fuelLevelvector.at(makeCounter) + "\"") : std::string("Нет данных")));
////                    exportvector.push_back(str);
////                }
////            }
////            if(!exportvector.empty()) {
////                if(pathFile.size() > 0) {
////                    if(!pathFile.contains(".csv")) {
////                        pathFile.push_back(".csv");
////                    }
////                    if(pathFile.count(':') > 1) { // windows
////                        pathFile.remove("file:///");
////                    } else {
////                        pathFile.remove("file://"); // unix
////                    }
////                    QFile file(pathFile);
////                    if (file.open(QFile::WriteOnly | QFile::Text)) {
////                        QTextStream s(&file);
////                        for (int counterExport=0; counterExport<exportvector.size(); ++counterExport) {
////                            s << exportvector.at(counterExport) << '\n';
////                        }
////                    }
////                    file.close();
////                }
////            }
////        }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevType") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();

////        //    std::vector<std::string> resvector;
////        //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////        //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
////        //        for(int i=0; i<devCount; i++) {
////        //            resvector << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(i);
////        //        }
////        //    }
////        //    return resvector;
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevId") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();

////        std::vector<std::string> ViewController::getAvailableDevTarrirAdd_DevId() {
////            //    std::vector<std::string> resvector;
////            //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////            //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
////            //        for(int i=0; i<devCount; i++) {
////            //            resvector << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(i);
////            //        }
////            //    }
////            //    return resvector;
////        }
////    }


////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();

////        std::vector<std::string> ViewController::getAvailableDevTarrirAdd_DevSerialNumber() {
////            //    std::vector<std::string> resvector;
////            //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////            //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
////            //        for(int i=0; i<devCount; i++) {
////            //            std::vector<std::string> keyvector = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).first;
////            //            for(int i2 =0; i2<keyvector.size(); i2++) {
////            //                if(keyvector.at(i2) == std::string("serialNum")) {                                                                                 // TOOD:!!!!!
////            //                    resvector << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).second.at(0);
////            //                }
////            //            }
////            //        }
////            //    }
////            //    return resvector;
////        }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    std::vector<std::string> ViewController::getTarCurrentDeviceData(int index) {
////        //    std::vector<std::string> res;
////        //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////        //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //            if(pService != nullptr) {
////        //                res = pService->getCurrentDataDevice(index);
////        //            }
////        //        }
////        //    }
////        //    return res;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    Qvector<int> ViewController::getTarCurrentDeviceChartData(int index) {
////        //    Qvector<int> res;
////        //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////        //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //            if(pService != nullptr) {
////        //                res = pService->getCurrentChartDataDevice(index);
////        //            }
////        //        }
////        //    }
////        //    return res;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    int ViewController::getStayedDevTarrirCount() {
////        //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////        //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //            if(pService != nullptr) {
////        //                return pService->getDeviceCount();
////        //            }
////        //        }
////        //    }
////        //    return 0;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    std::vector<std::string> ViewController::getStayedDevTarrir_DevProperty(std::string propertyName) {
////        //    std::vector<std::string> res;
////        //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
////        //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //            if(pService != nullptr) {
////        //                for(int i=0; i<pService->getDeviceCount(); i++) {
////        //                    if(propertyName.toLower() == "type") {
////        //                        res << pService->getDeviceProperty(i).at(0); // type
////        //                    }
////        //                    if(propertyName.toLower() == "id") {
////        //                        res << pService->getDeviceProperty(i).at(1); // id
////        //                    }
////        //                    if(propertyName.toLower() == "sn") {
////        //                        res << pService->getDeviceProperty(i).at(2); // serialNum
////        //                    }
////        //                }
////        //            }
////        //        }
////        //    }
////        //    return res;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    bool ViewController::addTarrirDev(std::string devTypeName, std::string devId) {
////        //    bool res = false;
////        //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        res = pService->addDevice(devTypeName, devId,"-----");
////        //    }
////        //    return res;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    void ViewController::removeTarrirDev(std::string devTypeName, std::string devId) {
////        //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        if(pService != nullptr) {
////        //            pService->removeDevice(devTypeName, devId);
////        //        }
////        //    }
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    void ViewController::setLastRealTimeValuesToStep(int indexStep) {
////        //#if USE_DB_VIEWCONTROLLER == 1
////        //    qDebug() << "ViewController: - setLastRealTimeValuesToStep";
////        //#endif
////        ////    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        //  Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        //  pService->setLastRealTimeValuesToStep(indexStep);
////        ////    }
////        //#if USE_DB_VIEWCONTROLLER == 1
////        //    qDebug() << "ViewController: - setLastRealTimeValuesToStep -OK";
////        //#endif
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    //1) считать таблицу с добавленных устройств
////    // отправляем в контроллер список dev с id
////    // указываем что считать таблицу
////    // ожидаем ответа по очереди
////    // когда последний опрошен, отсылаем результат в qml
////    // если ответа небыло, значение выделить красным и вывести message
////    void ViewController::sendReqGetTarrirAllDev() {
////        //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        if(pService != nullptr) {
////        //            for(auto i:pService->requestGetTableFromAllDevice()) {      // TODO: плохо, можно взять пустой список и ждать ответа
////        //                if(i.length() > 0) {
////        //                    // отправляем всем dev из списка команду на чтение таблицы
////        //                    DevicesFactory *pdeviceFactory = nullptr;
////        //                    pdeviceFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
////        //                    if(pdeviceFactory != nullptr) {
////        //                        int devIndex = pdeviceFactory->findDeviceIndex(i);
////        //                        if(devIndex >= 0) {
////        //                            pdeviceFactory->deviceCollector->sendCustomCommadToDev(devIndex, "read current dev tar table");
////        //                        } else {
////        //                            qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR find device";
////        //                        }
////        //                    } else {
////        //                        qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR nullprt deviceFactory";
////        //                    }
////        //                }
////        //            }
////        //        }
////        //    }
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    std::vector<std::string> ViewController::getTableAtDevice(int index) {
////        //    std::vector<std::string> res;
////        //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        if(pService != nullptr) {
////        //            res = pService->getTableAtDevice(index);
////        //        }
////        //    }
////        //    return res;
////    }
////    }

////    // TODO:
////    if(operation == "getAvailableDevTarrirAdd_DevSerialNumber") {
////        unitCommand.deviceIdent = getUniqId();
////        unitCommand.isNeedAckMessage = true;
////        unitCommand.devCommand = (int)Progress_tmk24Data::lls_read_cal_table;
////        unitCommand.commandType = CommandController::E_CommandType_send_typical_request;
////        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getServiceAbstract());
////        pService->getMaxCountStep();
////    int ViewController::getTableCountReady() {
////        //    int res = 0;
////        //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
////        //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
////        //        if(pService != nullptr) {
////        //            res = pService->requestGetTableFromAllDevice().size();
////        //        }
////        //    }
////        //    return res;
////    }
////    }

//    return commandvector;
//}

std::vector<std::string> Progress_tmk24::execCommand(std::string operation, std::pair<std::vector<std::string>, std::vector<std::string>>) {}

//Qvector<CommandController::sCommandData> Progress_tmk24::getCommandvectorToCurrentData() {
//    Qvector<CommandController::sCommandData> commandvector;
//    CommandController::sCommandData command;
//    command.commandOptionData.clear();
//    command.deviceIdent = getUniqId();
//    command.operationHeader = "typical command get current data";
//    command.isNeedAckMessage = false;
//    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_once;
//    command.commandType = CommandController::E_CommandType_send_typical_request;
//    commandvector.push_back(command);
//    command.devCommand = (int)Progress_tmk24Data::lls_read_cnt;
//    commandvector.push_back(command);
//    command.devCommand = (int)Progress_tmk24Data::lls_read_lvl_all;
//    commandvector.push_back(command);
//    return commandvector;
//}
