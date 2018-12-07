#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Nozzle_Revision_0_00_Oct_2018.h"
#include "other/crc.h"
#include <qmath.h>

Nozzle_Revision_0_00_Oct_2018::Nozzle_Revision_0_00_Oct_2018(std::list<std::string> keys, std::list<std::string> values) {
    auto propIter = values.begin();
    for(auto itemKey: keys) {
        if(itemKey == "id") {
            this->deviceIdent.id = *propIter;
        }
        if(itemKey == "header") {
            this->deviceIdent.header = *propIter;
        }
        propIter++;
    }
    this->state = STATE_DISCONNECTED;
    setDefaultValues();

    if(deviceIdent.id.empty() || deviceIdent.header.empty()) {
        throw std::string("if does not include all properties");
    }

    this->state = STATE_DISCONNECTED;
    setDefaultValues();
}

Nozzle_Revision_0_00_Oct_2018::~Nozzle_Revision_0_00_Oct_2018() {

}

std::string Nozzle_Revision_0_00_Oct_2018::getDevTypeName() {
    return std::string(Nozzle_Revision_0_00_Oct_2018::name);
}

std::string Nozzle_Revision_0_00_Oct_2018::getDevHeader() {
    return deviceIdent.header;
}

void Nozzle_Revision_0_00_Oct_2018::setDevHeader(std::string header) {
    deviceIdent.header = header;
}

void Nozzle_Revision_0_00_Oct_2018::setDefaultValues() {
    this->dev_data.accelX.isValid = false;
    this->dev_data.accelY.isValid = false;
    this->dev_data.accelZ.isValid = false;
    this->dev_data.cardNumber.isValid = false;
    this->dev_data.cardState.isValid = false;
    this->dev_data.networkCurrentIp.isValid = false;
    this->dev_data.networkState.isValid = false;
    this->dev_data.powerCurrent.isValid = false;
    this->dev_data.powerVoltage.isValid = false;
    this->dev_data.powertypeBattery.isValid = false;
    this->dev_data.powerCurrentAccumulate_uAh.isValid = false;
    this->dev_data.powerCurrentResouresAvailable_mA.isValid = false;
    this->dev_data.temperature.isValid = false;
    this->dev_data.versionFirmware.isValid = false;
    this->dev_data.rssi.isValid = false;
    this->dev_data.networkConfig.isValid = false;
}

ServiceDevicesAbstract* Nozzle_Revision_0_00_Oct_2018::getServiceAbstract() {
    return nullptr;
}

std::list<int> Nozzle_Revision_0_00_Oct_2018::getChart() {
    return std::list<int>();
}

std::pair<std::list<std::string>,std::list<std::string>> Nozzle_Revision_0_00_Oct_2018::getPropertyData() {
    std::pair<std::list<std::string>,std::list<std::string>> res;
    res.first.push_back("devTypeName");
    res.second.push_back(getDevTypeName());
    res.first.push_back("serialNum");
    res.second.push_back(serialNumber.empty() ? std::string("Не присвоен") : serialNumber);
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("header");
    res.second.push_back(deviceIdent.header);
    res.first.push_back("versionFirmare");
    res.second.push_back(dev_data.versionFirmware.isValid ? dev_data.versionFirmware.value : "NA");
    return res;
}

std::pair<std::list<std::string>,std::list<std::string>> Nozzle_Revision_0_00_Oct_2018::getCurrentData() {
    std::pair<std::list<std::string>,std::list<std::string>> res;
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("accelX");
    res.second.push_back(dev_data.accelX.isValid == true ? std::to_string(dev_data.accelX.value.value_i) : "NA");
    res.first.push_back("accelY");
    res.second.push_back(dev_data.accelY.isValid == true ? std::to_string(dev_data.accelY.value.value_i) : "NA");
    res.first.push_back("accelZ");
    res.second.push_back(dev_data.accelZ.isValid == true ? std::to_string(dev_data.accelZ.value.value_i) : "NA");
    res.first.push_back("cardNumber");
    res.second.push_back(dev_data.cardNumber.isValid == true ? dev_data.cardNumber.value : "NA");
    res.first.push_back("cardState");
    res.second.push_back(dev_data.cardState.isValid == true ? std::to_string(dev_data.cardState.value.value_i) : "NA");
    res.first.push_back("networkCurrentIp");
    res.second.push_back(dev_data.networkCurrentIp.isValid == true ? dev_data.networkCurrentIp.value : "NA");
    res.first.push_back("networkState");
    res.second.push_back(dev_data.networkState.isValid == true ? (dev_data.networkState.value.value_i == true ? "Подключено" : "Не подключено") : "NA");
    res.first.push_back("temperature");
    res.second.push_back(dev_data.temperature.isValid == true ? std::to_string(dev_data.temperature.value.value_f) : "NA");
    res.first.push_back("powerVoltage");
    res.second.push_back(dev_data.powerVoltage.isValid == true ? std::to_string(dev_data.powerVoltage.value.value_f) : "NA");
    res.first.push_back("powertypeBattery");
    res.second.push_back(dev_data.powertypeBattery.isValid == true ? dev_data.powertypeBattery.value : "NA");
    res.first.push_back("powerCurrentAccumulate");
    res.second.push_back(dev_data.powerCurrentAccumulate_uAh.isValid == true ? std::to_string(dev_data.powerCurrentAccumulate_uAh.value.value_f) : "NA");
    res.first.push_back("powerCurrentResouresAvailable");
    res.second.push_back(dev_data.powerCurrentResouresAvailable_mA.isValid == true ? std::to_string(dev_data.powerCurrentResouresAvailable_mA.value.value_f) : "NA");
    res.first.push_back("powerCurrent");
    res.second.push_back(dev_data.powerCurrent.isValid == true ? std::to_string(dev_data.powerCurrent.value.value_f) : "NA");
    res.first.push_back("versionFirmare");
    res.second.push_back(dev_data.versionFirmware.isValid ? dev_data.versionFirmware.value : "NA");
    res.first.push_back("rssiValue");
    res.second.push_back(dev_data.rssi.isValid ? std::to_string(dev_data.rssi.value.value_i) : "0");
    return res;
}

std::pair<std::list<std::string>,std::list<std::string>> Nozzle_Revision_0_00_Oct_2018::getSettings() {
    std::pair<std::list<std::string>,std::list<std::string>> res;
    std::stringstream sstream;
    res.first.push_back("accelConfX");
    // accel
    res.second.push_back(dev_data.accelThresholdX.isValid == true ? std::to_string(dev_data.accelThresholdX.value.value_i) : "NA");
    res.first.push_back("accelConfY");
    res.second.push_back(dev_data.accelThresholdY.isValid == true ? std::to_string(dev_data.accelThresholdY.value.value_i) : "NA");
    res.first.push_back("accelConfZ");
    res.second.push_back(dev_data.accelThresholdZ.isValid == true ? std::to_string(dev_data.accelThresholdZ.value.value_i) : "NA");
    res.first.push_back("accelAngle");
    res.second.push_back(dev_data.accelDelta.isValid == true ? std::to_string(dev_data.accelDelta.value.value_i) : "NA");
    // security
    res.first.push_back("securityPasswordIsUsed");
    res.second.push_back(dev_data.security.passwordIsUsed.isValid == true ? std::to_string(dev_data.security.passwordIsUsed.value.value_i) : "NA");
    res.first.push_back("securityPassword");
    res.second.push_back(dev_data.networkConfig.isValid ? dev_data.security.password.value : "NA");
    // network
    res.first.push_back("networkClientToken");
    res.second.push_back(dev_data.networkConfig.isValid ? dev_data.networkConfig.clientToken : "NA");
    res.first.push_back("networkClientName");
    res.second.push_back(dev_data.networkConfig.isValid ? dev_data.networkConfig.clientUserName : "NA");
    res.first.push_back("networkServerIp");
    res.second.push_back(dev_data.networkConfig.isValid ? dev_data.networkConfig.serverIp : "NA");
    res.first.push_back("networkServerPort");
    res.second.push_back(dev_data.networkConfig.isValid ? std::to_string(dev_data.networkConfig.serverPort) : "NA");
    res.first.push_back("networkPanid");
    sstream << std::hex << std::to_string(dev_data.networkConfig.panid);
    res.second.push_back(dev_data.networkConfig.isValid ?  sstream.str() : "NA");
    return res;
}

std::pair<std::list<std::string>,std::list<std::string>> Nozzle_Revision_0_00_Oct_2018::getErrors() {
    return std::pair<std::list<std::string>,std::list<std::string>>();
}

DeviceAbstract::E_State Nozzle_Revision_0_00_Oct_2018::getState() {
    return state;
}

void Nozzle_Revision_0_00_Oct_2018::setState(DeviceAbstract::E_State value) {
    state = value; // если дисконектим или сбрасываем - тогда сбрасываем и данные
    if((state == DeviceAbstract::STATE_DISCONNECTED) || (state == DeviceAbstract::STATE_START_INIT)) {
        setDefaultValues();
    }
}

std::string Nozzle_Revision_0_00_Oct_2018::getUniqId() {
    return deviceIdent.id;
}

//bool Nozzle_Revision_0_00_Oct_2018::makeDataToCommand(CommandController::sCommandData &commandData) {
//    bool res = false;
//    Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData tCommand;
//    memset(&tCommand, 0, sizeof(tCommand));
//    commandData.commandOptionData.clear();
//    tCommand.commandType = (Nozzle_Revision_0_00_Oct_2018_Data::eConsoleCommandType)commandData.devCommand;
//    tCommand.magic_word = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD;
//    tCommand.deviceIdent = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT;
//    tCommand.versionProtocol = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL;

//    try {
//        switch(commandData.devCommand) {
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig: {
//            typedef struct {
//                int x;
//                int y;
//                int z;
//                int angle;
//                int deltaPower2;
//            }sOutBatBuff;

//            sOutBatBuff tbuf;
//            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
//                if(commandData.args.key[keyCount] == "accelConfX") {
//                    tbuf.x = (int)commandData.args.value[keyCount].toInt();
//                }
//                if(commandData.args.key[keyCount] == "accelConfY") {
//                    tbuf.y = (int)commandData.args.value[keyCount].toInt();
//                }
//                if(commandData.args.key[keyCount] == "accelConfZ") {
//                    tbuf.z = (int)commandData.args.value[keyCount].toInt();
//                }
//                if(commandData.args.key[keyCount] == "accelAngle") {
//                    tbuf.angle  = (int)commandData.args.value[keyCount].toInt();
//                }
//                const int mG = 9810;
//                tbuf.deltaPower2 = qPow((2*mG*sin((tbuf.angle*M_PI/180)/2)), 2);
//            }
//            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData: {
//            typedef struct {
//                bool passwordIsUsed;
//                char password[64];
//            }sOutBatBuff;
//            sOutBatBuff tbuf; // if password len != 0 when is used
//            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
//                if(commandData.args.key[keyCount] == "password") {
//                    if(!commandData.args.value[keyCount].isEmpty()) {
//                        strcpy(tbuf.password, commandData.args.value[keyCount].toUtf8());
//                        tbuf.passwordIsUsed = true;
//                    } else {
//                        tbuf.passwordIsUsed = false;
//                    }
//                }
//            }
//            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;

//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig: {
//            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig t_data;
//            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
//                if(!commandData.args.key.empty()) {
//                    if(commandData.args.key[keyCount] == "networkClientToken") {
//                        strcpy(t_data.clientToken, commandData.args.value[keyCount].toUtf8());
//                    }
//                    if(commandData.args.key[keyCount] == "networkClientName") {
//                        strcpy(t_data.clientUserName, commandData.args.value[keyCount].toUtf8());
//                    }
//                    if(commandData.args.key[keyCount] == "networkServerIp") {
//                        strcpy(t_data.serverIp, commandData.args.value[keyCount].toUtf8());
//                    }
//                    if(commandData.args.key[keyCount] == "networkServerPort") {
//                        t_data.serverPort = commandData.args.value[keyCount].toInt();
//                    }
//                    if(commandData.args.key[keyCount] == "networkPanid") {
//                        t_data.panid = commandData.args.value[keyCount].toInt(nullptr, 16);
//                    }
//                }
//                memcpy(tCommand.data.data, (uint8_t*)&t_data, sizeof(t_data));
//            }
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum: {
//            typedef struct {
//                bool normal;
//            }sOutBatBuff;
//            sOutBatBuff tbuf;
//            tbuf.normal = true;
//            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
//            commandData.commandOptionData.append((char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
//            res = true;
//        }
//            break;
//        default : break;
//        }
//        commandData.commandOptionData = packData(&commandData.commandOptionData);

//    } catch(...) {
//        qDebug("Device: makeDataToCommand -catch!");
//    }
//    return res;
//}

QByteArray Nozzle_Revision_0_00_Oct_2018::packData(QByteArray *pCommandData){
    QByteArray outData;
    outData.clear();
    outData.append(COMMAND_START_BYTE);
    for (int i=0; i<pCommandData->size(); i++) {
        switch (pCommandData->constData()[i]) {
            case COMMAND_ESC_BYTE:
                outData.append(COMMAND_ESC_BYTE);
                outData.append(COMMAND_ESC_ESC_BYTE);
                break;
            case COMMAND_START_BYTE:
                outData.append(COMMAND_ESC_BYTE);
                outData.append(COMMAND_START_BYTE);
                break;
            case COMMAND_STOP_BYTE:
                outData.append(COMMAND_ESC_BYTE);
                outData.append(COMMAND_STOP_BYTE);
                break;
            default:
                outData.append(pCommandData->constData()[i]);
                break;
        }
    }
    outData.append(COMMAND_STOP_BYTE);

    return outData;
}

// found dead frames and delete it
QList<std::pair<std::string,QByteArray>> Nozzle_Revision_0_00_Oct_2018::prepareReply(QByteArray &data) {
    QList<std::pair<std::string,QByteArray>> res;
    int startIndexBuf = 0;
    int endIndexBuf = 0;
    // 1 find first tag
    // 2 it will make clear type data
    for(int i=0; i<data.size(); i++) {
        //  find type log
        auto value = findTag(std::string(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind),
                             std::string(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd), data);
        if(value.first) {
            startIndexBuf = value.second.first + std::string(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind).length();
            endIndexBuf = value.second.second;
            res.push_back(std::pair<std::string,QByteArray>("logData", QByteArray(data.mid(startIndexBuf, endIndexBuf - startIndexBuf))));
            data.remove(0, endIndexBuf + std::string(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd).length());
        } else { //  find type data
            value = findTag(std::string(Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind),
                            std::string(Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd), data);
            if(value.first) {
                startIndexBuf = value.second.first + std::string(Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind).length();
                endIndexBuf = value.second.second;
                res.push_back(std::pair<std::string,QByteArray>("commandData", QByteArray(data.mid(startIndexBuf, endIndexBuf - startIndexBuf))));
                data.remove(0, endIndexBuf + std::string(Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd).length());
            }
        }
    }
    return res;
}

//bool Nozzle_Revision_0_00_Oct_2018::placeDataReplyToCommand(QByteArray &commandArray, CommandController::sCommandData commandReqData) {
//    bool res = false;
//    static int disconnect_counter = 0;
//    if(!commandArray.isEmpty()) {
//        commandArrayReplyData += commandArray;
//        auto res = prepareReply(commandArrayReplyData);
//        for(auto it:res) {
//            disconnect_counter = 0;
//            if(!it.first.isEmpty()) {
//                if(state == DeviceAbstract::STATE_DISCONNECTED) {
//                    emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Connected, commandReqData.deviceIdent,
//                                                std::list<std::string>("Status"), std::list<std::string>("Connected"), commandReqData);
//                }
//                if(it.first == "logData") {
//                    emit eventDeviceUpdateState(Type_DeviceEvent_LogMessage, commandReqData.deviceIdent, std::list<std::string>("LogMessage"), std::list<std::string>(it.second), commandReqData);
//                } else if (it.first  == "commandData") {
//                    parseCommandReply(it.second, commandReqData);
//                } else {
//                    std::cout  << "unknown type";
//                }
//            }
//        }
//    } else {
//        if(disconnect_counter > 10) {
//            disconnect_counter = 0;
//            setState(DeviceAbstract::STATE_DISCONNECTED);
//            emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, commandReqData.deviceIdent,
//                                    std::list<std::string>("Status"), std::list<std::string>("disconnected"), commandReqData);
//        } else {
//            disconnect_counter++;
//        }
//    }
//    return res;
//}

//void Nozzle_Revision_0_00_Oct_2018::parseCommandReply(QByteArray data, CommandController::sCommandData commandReqData) {
//    std::pair<std::list<std::string>, std::list<std::string>> res;
//    bool replyIsValid = false;
//    Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff *t_reply =
//            (Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff*)(data.data());
//    if(t_reply->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
//            && t_reply->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
//            && t_reply->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) {
//        replyIsValid = true;
//    }

//    switch(t_reply->commandType) {
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getBatteryData";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sBatteryData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sBatteryData*)t_reply->data.data;
//            dev_data.powerVoltage.value.value_f = tbuf->powerVoltage;
//            dev_data.powerCurrent.value.value_f = tbuf->powerCurrent;
//            dev_data.powerCurrentAccumulate_uAh.value.value_f = tbuf->powerCurrentAccumulate_uAh;
//            dev_data.powerCurrentResouresAvailable_mA.value.value_f = tbuf->powerCurrentResouresAvailable_mA - abs(tbuf->powerCurrentAccumulate_uAh / 1000);
//            dev_data.powerVoltage.isValid = true;
//            dev_data.powertypeBattery.isValid = true;
//            dev_data.powerCurrent.isValid = true;
//            dev_data.powerCurrentAccumulate_uAh.isValid = true;
//            dev_data.powerCurrentResouresAvailable_mA.isValid = true;
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
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getAccelConfig";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sAccelConfig *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sAccelConfig*)t_reply->data.data;
//            dev_data.accelThresholdX.value.value_i = tbuf->thresholdX;
//            dev_data.accelThresholdY.value.value_i = tbuf->thresholdY;
//            dev_data.accelThresholdZ.value.value_i = tbuf->thresholdZ;
//            dev_data.accelDelta.value.value_i = tbuf->delta;
//            dev_data.accelThresholdX.isValid = true;
//            dev_data.accelThresholdY.isValid = true;
//            dev_data.accelThresholdZ.isValid = true;
//            dev_data.accelDelta.isValid = true;
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
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getAccelData";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sAccelData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sAccelData*)t_reply->data.data;
//            dev_data.accelX.value.value_i = tbuf->x;
//            dev_data.accelY.value.value_i = tbuf->y;
//            dev_data.accelZ.value.value_i = tbuf->z;
//            dev_data.accelX.isValid = true;
//            dev_data.accelY.isValid = true;
//            dev_data.accelZ.isValid = true;
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
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getOtherData";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sOtherData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sOtherData*)t_reply->data.data;
//            dev_data.versionFirmware.value = std::string::fromUtf8(tbuf->version);
//            dev_data.versionFirmware.isValid = true;
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

//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData:
//        break;

//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getCardData";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sCardData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sCardData*)t_reply->data.data;
//            dev_data.cardNumber.value = std::string::fromUtf8(tbuf->cardNumber, tbuf->len);
//            dev_data.cardState.value.value_i = tbuf->status;
//            dev_data.cardNumber.isValid = true;
//            dev_data.cardState.isValid = true;
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
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getNetworkData";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sNetworkData*)t_reply->data.data;
//            dev_data.networkCurrentIp.value = std::string::fromUtf8(tbuf->networkCurrentIp);
//            dev_data.networkCurrentIp.isValid = true;
//            dev_data.rssi.value.value_i = tbuf->rssi;
//            dev_data.rssi.history.push_back(tbuf->rssi);
//            dev_data.rssi.isValid = true;
//            dev_data.networkState.value.value_i = tbuf->status;
//            dev_data.networkState.isValid = true;
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
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        res.second << "getNetworkConfig";
//        if(replyIsValid) {
//            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig*)t_reply->data.data;
//            dev_data.networkConfig.clientToken = std::string::fromUtf8(tbuf->clientToken);
//            dev_data.networkConfig.clientUserName = std::string::fromUtf8(tbuf->clientUserName);
//            dev_data.networkConfig.serverIp = std::string::fromUtf8(tbuf->serverIp);
//            dev_data.networkConfig.serverPort = tbuf->serverPort;
//            dev_data.networkConfig.panid = tbuf->panid;
//            dev_data.networkConfig.isValid  = true;
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

//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        if(replyIsValid) {
//            res.second << "getIsReadyCommand" << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "getIsReadyCommand" << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//    }
//        break;
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig:
//        res.second << "setAccelConfig";
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig:
//        res.second << "setNetworkConfig";
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData:
//        res.second << "setSecurityData";
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;
//    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum:
//        res.second << "setBatteryNewAccum";
//        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
//        if(replyIsValid) {
//            res.second << "normal" << std::to_string(commandReqData.isNeedAckMessage);
//        } else {
//            res.second << "error" << std::to_string(commandReqData.isNeedAckMessage);
//        }
//        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
//                                    res.first, res.second, commandReqData);
//        break;
//    default : break;
//    }

//    if(replyIsValid) {
//        if(getState() == STATE_DISCONNECTED) {
//            setState(DeviceAbstract::STATE_START_INIT);
//        }
//        if(dev_data.networkConfig.isValid && dev_data.security.passwordIsUsed.isValid) {
//            setState(DeviceAbstract::STATE_NORMAL_READY);
//        }
//    }
//}

std::pair<bool, std::pair<int,int>> Nozzle_Revision_0_00_Oct_2018::findTag(std::string regExpValueBegin, std::string regExpValueEnd, QByteArray data) {
    std::pair<bool, std::pair<int,int>> res;
    int indexBegin = 0, indexEnd = 0;
    res.first = false;
    indexBegin = data.indexOf(QString(regExpValueBegin.c_str()));
    if(indexBegin >=0){
        res.second.first = indexBegin;
        indexEnd = data.indexOf(QString(regExpValueEnd.c_str()));
        if(indexEnd >= 0) {
            res.second.second = indexEnd;
            res.first = true;
        }
    }
    return res;
}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandToCheckConnected() {
//    QList<CommandController::sCommandData> command;
//    CommandController::sCommandData simpleCommand;
//    simpleCommand.isNeedAckMessage = false;
//    simpleCommand.delay_send_ms = 150;
//    simpleCommand.operationHeader = "check dev is connected";
//    simpleCommand.deviceIdent = getUniqId();
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
//    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(simpleCommand);
//    command.push_back(simpleCommand);
//    return command;
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandtoCheckPassword() {
//    QList<CommandController::sCommandData> command;
//    CommandController::sCommandData simpleCommand;
//    simpleCommand.deviceIdent = getUniqId();
//    simpleCommand.delay_send_ms = 150;
//    simpleCommand.isNeedAckMessage = false;
//    simpleCommand.operationHeader = "check dev password";
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
//    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    makeDataToCommand(simpleCommand);
//    command.push_back(simpleCommand);
//    return command;
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToInit() {
//    QList<CommandController::sCommandData> listCommand;
//    CommandController::sCommandData simpleCommand;
//    simpleCommand.deviceIdent = getUniqId();
//    simpleCommand.delay_send_ms = 150;
//    simpleCommand.operationHeader = "init dev after connecting";
//    simpleCommand.isNeedAckMessage = false;
//    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
//    makeDataToCommand(simpleCommand);
//    listCommand.push_back(simpleCommand);
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
//    makeDataToCommand(simpleCommand);
//    listCommand.push_back(simpleCommand);
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
//    makeDataToCommand(simpleCommand);
//    listCommand.push_back(simpleCommand);
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
//    makeDataToCommand(simpleCommand);
//    listCommand.push_back(simpleCommand);
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
//    makeDataToCommand(simpleCommand);
//    listCommand.push_back(simpleCommand);
//    return listCommand;
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToUpdate() {
//    return getCommandListToInit();
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandToGetType() {
//    QList<CommandController::sCommandData> command;
//    CommandController::sCommandData simpleCommand;
//    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
//    simpleCommand.deviceIdent = getUniqId();
//    simpleCommand.delay_send_ms = 150;
//    simpleCommand.isNeedAckMessage = false;
//    simpleCommand.operationHeader = "get dev type";
//    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_EmptyCommand;
//    makeDataToCommand(simpleCommand);
//    command.push_back(simpleCommand);
//    return command;
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToCurrentData() {
//    QList<CommandController::sCommandData> listCommand;
//    CommandController::sCommandData command;
//    command.delay_send_ms = 150;
//    command.deviceIdent = getUniqId();
//    command.operationHeader = "typical command get current data";
//    command.isNeedAckMessage = false;
//    command.commandType = CommandController::E_CommandType_send_typical_request;
//    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData;
//    makeDataToCommand(command);
//    listCommand.push_back(command);
//    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData;
//    makeDataToCommand(command);
//    listCommand.push_back(command);
//    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData;
//    makeDataToCommand(command);
//    listCommand.push_back(command);
//    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData;
//    makeDataToCommand(command);
//    listCommand.push_back(command);
//    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
//    makeDataToCommand(command);
//    listCommand.push_back(command);
//    return listCommand;
//}

//QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandCustom(std::string operation, std::pair<std::list<std::string>, std::list<std::string>> data) {
//    QList <CommandController::sCommandData> command;
//    CommandController::sCommandData tcommand;
//    tcommand.operationHeader = operation;
//    tcommand.delay_send_ms = 170;
//    tcommand.commandType = CommandController::E_CommandType_send_typical_request;
//    if(operation == "update device") {
//        command = getCommandListToUpdate();
//    }
//    if(operation == "set current accel value as null pointe") { // TODO:!!!
//    } else if(operation == "get current dev settings witout dialog") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = false; // что не нужен ответ на форме
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//        makeDataToCommand(tcommand);
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
//        command.push_back(tcommand);
//    } else if(operation == "get current dev settings") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//    } else if(operation == "set current dev settings accel config") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig;
//        // key, value
//        tcommand.args.key << data.first;
//        tcommand.args.value << data.second;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//    } else if(operation == "set current dev password") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData;
//        // key, value
//        tcommand.args.key << data.first;
//        tcommand.args.value << data.second;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//    } else if(operation == "set current dev settings net config") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig;
//        // key, value
//        tcommand.args.key << data.first;
//        tcommand.args.value << data.second;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//    } else if(operation == "set new battery") {
//        tcommand.deviceIdent = getUniqId();
//        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
//        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum;
//        makeDataToCommand(tcommand);
//        command.push_back(tcommand);
//    } else {
//        std::cout  << "getCommandCustom -type unknown!";
//    }
//    return command;
//}

std::list<std::string> Nozzle_Revision_0_00_Oct_2018::execCommand(std::string operation, std::pair<std::list<std::string>, std::list<std::string>>) {

}
