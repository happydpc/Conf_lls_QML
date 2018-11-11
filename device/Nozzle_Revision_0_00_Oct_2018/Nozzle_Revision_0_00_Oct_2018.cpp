#include <QDebug>
#include "Nozzle_Revision_0_00_Oct_2018.h"
#include "other/crc.h"
#include <QList>
#include <qmath.h>

Nozzle_Revision_0_00_Oct_2018::Nozzle_Revision_0_00_Oct_2018(QString devId, QString header) {
    this->deviceIdent.header = header;
    this->deviceIdent.id = devId;
    this->state = STATE_DISCONNECTED;
    qDebug() << QString("Console size eTypeData = %1\n").arg(sizeof(uint8_t));
    qDebug() << QString("Console size sConsoleBufData = %1\n").arg(sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
    qDebug() << QString("Console size sConsoleReplyBuff = %1\n").arg(sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff));
    qDebug() << QString("Console size sConsole = %1\n").arg(sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsole));
    setDefaultValues();
}

Nozzle_Revision_0_00_Oct_2018::~Nozzle_Revision_0_00_Oct_2018() {

}

QString Nozzle_Revision_0_00_Oct_2018::getDevTypeName() {
    return QString::fromLocal8Bit(Nozzle_Revision_0_00_Oct_2018::name, strlen(Nozzle_Revision_0_00_Oct_2018::name));
}

QString Nozzle_Revision_0_00_Oct_2018::getDevHeader() {
    return deviceIdent.header;
}

void Nozzle_Revision_0_00_Oct_2018::setDevHeader(QString header) {
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
    this->dev_data.powerCurrentAccumulate_mA.isValid = false;
    this->dev_data.powerCurrentResouresAvailable_mA.isValid = false;
    this->dev_data.temperature.isValid = false;
    this->dev_data.versionFirmware.isValid = false;
    this->dev_data.rssi.isValid = false;
    this->dev_data.networkConfig.isValid = false;
}

ServiceDevicesAbstract* Nozzle_Revision_0_00_Oct_2018::getServiceAbstract() {
    return nullptr;
}

QList<int> Nozzle_Revision_0_00_Oct_2018::getChart() {
    return QList<int>();
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getPropertyData() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("devTypeName");
    res.second.push_back(getDevTypeName());
    res.first.push_back("serialNum");
    res.second.push_back(serialNumber.isEmpty() ? QString("Не присвоен") : serialNumber);
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("header");
    res.second.push_back(deviceIdent.header);
    res.first.push_back("versionFirmare");
    res.second.push_back(dev_data.versionFirmware.isValid ? dev_data.versionFirmware.value : "NA");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getCurrentData() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("id");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("accelX");
    res.second.push_back(dev_data.accelX.isValid == true ? QString::number(dev_data.accelX.value.value_i) : "NA");
    res.first.push_back("accelY");
    res.second.push_back(dev_data.accelY.isValid == true ? QString::number(dev_data.accelY.value.value_i) : "NA");
    res.first.push_back("accelZ");
    res.second.push_back(dev_data.accelZ.isValid == true ? QString::number(dev_data.accelZ.value.value_i) : "NA");
    res.first.push_back("cardNumber");
    res.second.push_back(dev_data.cardNumber.isValid == true ? dev_data.cardNumber.value : "NA");
    res.first.push_back("cardState");
    res.second.push_back(dev_data.cardState.isValid == true ? QString::number(dev_data.cardState.value.value_i) : "NA");
    res.first.push_back("networkCurrentIp");
    res.second.push_back(dev_data.networkCurrentIp.isValid == true ? dev_data.networkCurrentIp.value : "NA");
    res.first.push_back("networkState");
    res.second.push_back(dev_data.networkState.isValid == true ? (dev_data.networkState.value.value_i == true ? "Подключено" : "Не подключено") : "NA");
    res.first.push_back("temperature");
    res.second.push_back(dev_data.temperature.isValid == true ? QString::number(dev_data.temperature.value.value_f) : "NA");
    res.first.push_back("powerVoltage");
    res.second.push_back(dev_data.powerVoltage.isValid == true ? QString::number(dev_data.powerVoltage.value.value_f) : "NA");
    res.first.push_back("powertypeBattery");
    res.second.push_back(dev_data.powertypeBattery.isValid == true ? dev_data.powertypeBattery.value : "NA");
    res.first.push_back("powerCurrentAccumulate");
    res.second.push_back(dev_data.powerCurrentAccumulate_mA.isValid == true ? QString::number(dev_data.powerCurrentAccumulate_mA.value.value_f) : "NA");
    res.first.push_back("powerCurrentResouresAvailable");
    res.second.push_back(dev_data.powerCurrentResouresAvailable_mA.isValid == true ? QString::number(dev_data.powerCurrentResouresAvailable_mA.value.value_f) : "NA");
    res.first.push_back("powerCurrent");
    res.second.push_back(dev_data.powerCurrent.isValid == true ? QString::number(dev_data.powerCurrent.value.value_f) : "NA");
    res.first.push_back("versionFirmare");
    res.second.push_back(dev_data.versionFirmware.isValid ? dev_data.versionFirmware.value : "NA");
    res.first.push_back("rssiValue");
    res.second.push_back(dev_data.rssi.isValid ? QString::number(dev_data.rssi.value.value_i) : "0");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getSettings() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("accelConfX");
    // accel
    res.second.push_back(dev_data.accelThresholdX.isValid == true ? QString::number(dev_data.accelThresholdX.value.value_i) : "NA");
    res.first.push_back("accelConfY");
    res.second.push_back(dev_data.accelThresholdY.isValid == true ? QString::number(dev_data.accelThresholdY.value.value_i) : "NA");
    res.first.push_back("accelConfZ");
    res.second.push_back(dev_data.accelThresholdZ.isValid == true ? QString::number(dev_data.accelThresholdZ.value.value_i) : "NA");
    res.first.push_back("accelAngle");
    res.second.push_back(dev_data.accelDelta.isValid == true ? QString::number(dev_data.accelDelta.value.value_i) : "NA");
    // security
    res.first.push_back("securityPasswordIsUsed");
    res.second.push_back(dev_data.security.passwordIsUsed.isValid == true ? QString::number(dev_data.security.passwordIsUsed.value.value_i) : "NA");
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
    res.second.push_back(dev_data.networkConfig.isValid ? QString::number(dev_data.networkConfig.serverPort) : "NA");
    res.first.push_back("networkPanid");
    res.second.push_back(dev_data.networkConfig.isValid ? QString::number(dev_data.networkConfig.panid, 16) : "NA");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getErrors() {
    return QPair<QStringList,QStringList>();
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

QString Nozzle_Revision_0_00_Oct_2018::getUniqId() {
    return deviceIdent.id;
}

bool Nozzle_Revision_0_00_Oct_2018::makeDataToCommand(CommandController::sCommandData &commandData) {
    bool res = false;
    Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData tCommand;
    memset(&tCommand, 0, sizeof(tCommand));
    commandData.commandOptionData.clear();
    tCommand.commandType = (Nozzle_Revision_0_00_Oct_2018_Data::eConsoleCommandType)commandData.devCommand;
    tCommand.magic_word = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD;
    tCommand.deviceIdent = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT;
    tCommand.versionProtocol = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL;
    try {
        switch(commandData.devCommand) {
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig: {
            typedef struct {
                int x;
                int y;
                int z;
                int angle;
                int deltaPower2;
            }sOutBatBuff;

            sOutBatBuff tbuf;
            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
                if(commandData.args.key[keyCount] == "accelConfX") {
                    tbuf.x = (int)commandData.args.value[keyCount].toInt();
                }
                if(commandData.args.key[keyCount] == "accelConfY") {
                    tbuf.y = (int)commandData.args.value[keyCount].toInt();
                }
                if(commandData.args.key[keyCount] == "accelConfZ") {
                    tbuf.z = (int)commandData.args.value[keyCount].toInt();
                }
                if(commandData.args.key[keyCount] == "accelAngle") {
                    tbuf.angle  = (int)commandData.args.value[keyCount].toInt();
                }
                const int mG = 9810;
                tbuf.deltaPower2 = qPow((2*mG*sin((tbuf.angle*M_PI/180)/2)), 2);
            }
            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData: {
            typedef struct {
                bool passwordIsUsed;
                char password[64];
            }sOutBatBuff;
            sOutBatBuff tbuf; // if password len != 0 when is used
            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
                if(commandData.args.key[keyCount] == "password") {
                    if(!commandData.args.value[keyCount].isEmpty()) {
                        strcpy(tbuf.password, commandData.args.value[keyCount].toUtf8());
                        tbuf.passwordIsUsed = true;
                    } else {
                        tbuf.passwordIsUsed = false;
                    }
                }
            }
            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;

        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig: {
            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig t_data;
            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
                if(commandData.args.key[keyCount] == "networkClientToken") {
                    strcpy(t_data.clientToken, commandData.args.value[keyCount].toUtf8());
                }
                if(commandData.args.key[keyCount] == "networkClientName") {
                    strcpy(t_data.clientUserName, commandData.args.value[keyCount].toUtf8());
                }
                if(commandData.args.key[keyCount] == "networkServerIp") {
                    strcpy(t_data.serverIp, commandData.args.value[keyCount].toUtf8());
                }
                if(commandData.args.key[keyCount] == "networkServerPort") {
                    t_data.serverPort = commandData.args.value[keyCount].toInt();
                }
                if(commandData.args.key[keyCount] == "networkPanid") {
                    t_data.panid = commandData.args.value[keyCount].toInt(nullptr, 16);
                }
            }
            memcpy(tCommand.data.data, (uint8_t*)&t_data, sizeof(t_data));
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum: {
            typedef struct {
                bool normal;
            }sOutBatBuff;
            sOutBatBuff tbuf;
            tbuf.normal = true;
            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        default : break;
        }
    } catch(...) {
        qDebug("Device: makeDataToCommand -catch!");
    }
    return res;
}

// found dead frames and delete it
QList<QPair<QString,QByteArray>> Nozzle_Revision_0_00_Oct_2018::prepareReply(QByteArray &data) {
    QList<QPair<QString,QByteArray>> res;
    int startIndexBuf = 0;
    int endIndexBuf = 0;
    // 1 find first tag
    // 2 it will make clear type data
    for(int i=0; i<data.size(); i++) {
        //  find type log
        auto value = findTag(QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind),
                             QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd), data);
        if(value.first) {
            startIndexBuf = value.second.first + QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind).length();
            endIndexBuf = value.second.second;
            res.push_back(QPair<QString,QByteArray>("logData", QByteArray(data.mid(startIndexBuf, endIndexBuf - startIndexBuf))));
            data.remove(0, endIndexBuf + QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd).length());
        } else { //  find type data
            value = findTag(QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind),
                            QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd), data);
            if(value.first) {
                startIndexBuf = value.second.first + QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind).length();
                endIndexBuf = value.second.second;
                res.push_back(QPair<QString,QByteArray>("commandData", QByteArray(data.mid(startIndexBuf, endIndexBuf - startIndexBuf))));
                data.remove(0, endIndexBuf + QString::fromUtf8(Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd).length());
            }
        }
    }
    return res;
}

bool Nozzle_Revision_0_00_Oct_2018::placeDataReplyToCommand(QByteArray &commandArray, CommandController::sCommandData commandReqData) {
    bool res = false;
    if(!commandArray.isEmpty()) {
        commandArrayReplyData += commandArray;
        auto res = prepareReply(commandArrayReplyData);
        for(auto it:res) {
            if(!it.first.isEmpty()) {
                if(state == DeviceAbstract::STATE_DISCONNECTED) {
                    emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Connected, commandReqData.deviceIdent,
                                                QStringList("Status"), QStringList("Connected"), commandReqData);
                }
                if(it.first == "logData") {
                    emit eventDeviceUpdateState(Type_DeviceEvent_LogMessage, commandReqData.deviceIdent, QStringList("LogMessage"), QStringList(it.second), commandReqData);
                } else if (it.first  == "commandData") {
                    parseCommandReply(it.second, commandReqData);
                } else {
                    qDebug() << "unknown type";
                }
            }
        }
    } else {
        qDebug() << "placeDataReplyToCommand=" << "-no reply";
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, commandReqData.deviceIdent,
                                    QStringList("Status"), QStringList("disconnected"), commandReqData);
    }
    return res;
}

void Nozzle_Revision_0_00_Oct_2018::parseCommandReply(QByteArray data, CommandController::sCommandData commandReqData) {    
    QPair<QStringList, QStringList> res;
    bool replyIsValid = false;
    Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff *t_reply =
            (Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff*)(data.data());
    if(t_reply->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
            && t_reply->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
            && t_reply->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) {
        replyIsValid = true;
    }

    switch(t_reply->commandType) {
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getBatteryData";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sBatteryData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sBatteryData*)t_reply->data.data;
            dev_data.powerVoltage.value.value_f = tbuf->powerVoltage;
            dev_data.powerCurrent.value.value_f = tbuf->powerCurrent;
            dev_data.powerCurrentAccumulate_mA.value.value_f = tbuf->powerCurrentAccumulate_mA;
            dev_data.powerCurrentResouresAvailable_mA.value.value_f = tbuf->powerCurrentResouresAvailable_mA - abs(tbuf->powerCurrentAccumulate_mA);
            dev_data.powerVoltage.isValid = true;
            dev_data.powertypeBattery.isValid = true;
            dev_data.powerCurrent.isValid = true;
            dev_data.powerCurrentAccumulate_mA.isValid = true;
            dev_data.powerCurrentResouresAvailable_mA.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getCurrentData().first;
        res.second << getCurrentData().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getAccelConfig";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sAccelConfig *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sAccelConfig*)t_reply->data.data;
            dev_data.accelThresholdX.value.value_i = tbuf->thresholdX;
            dev_data.accelThresholdY.value.value_i = tbuf->thresholdY;
            dev_data.accelThresholdZ.value.value_i = tbuf->thresholdZ;
            dev_data.accelDelta.value.value_i = tbuf->delta;
            dev_data.accelThresholdX.isValid = true;
            dev_data.accelThresholdY.isValid = true;
            dev_data.accelThresholdZ.isValid = true;
            dev_data.accelDelta.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getSettings().first;
        res.second << getSettings().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getAccelData";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sAccelData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sAccelData*)t_reply->data.data;
            dev_data.accelX.value.value_i = tbuf->x;
            dev_data.accelY.value.value_i = tbuf->y;
            dev_data.accelZ.value.value_i = tbuf->z;
            dev_data.accelX.isValid = true;
            dev_data.accelY.isValid = true;
            dev_data.accelZ.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getCurrentData().first;
        res.second << getCurrentData().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getOtherData";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sOtherData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sOtherData*)t_reply->data.data;
            dev_data.versionFirmware.value = QString::fromUtf8(tbuf->version);
            dev_data.versionFirmware.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getCurrentData().first;
        res.second << getCurrentData().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData:
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getCardData";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sCardData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sCardData*)t_reply->data.data;
            dev_data.cardNumber.value = QString::fromUtf8(tbuf->cardNumber, tbuf->len);
            dev_data.cardState.value.value_i = tbuf->status;
            dev_data.cardNumber.isValid = true;
            dev_data.cardState.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getCurrentData().first;
        res.second << getCurrentData().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getNetworkData";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkData *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sNetworkData*)t_reply->data.data;
            dev_data.networkCurrentIp.value = QString::fromUtf8(tbuf->networkCurrentIp);
            dev_data.networkCurrentIp.isValid = true;
            dev_data.rssi.value.value_i = tbuf->rssi;
            dev_data.rssi.history.push_back(tbuf->rssi);
            dev_data.rssi.isValid = true;
            dev_data.networkState.value.value_i = tbuf->status;
            dev_data.networkState.isValid = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getCurrentData().first;
        res.second << getCurrentData().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        res.second << "getNetworkConfig";
        if(replyIsValid) {
            Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig *tbuf = (Nozzle_Revision_0_00_Oct_2018_Data::sNetworkConfig*)t_reply->data.data;
            dev_data.networkConfig.clientToken = QString::fromUtf8(tbuf->clientToken);
            dev_data.networkConfig.clientUserName = QString::fromUtf8(tbuf->clientUserName);
            dev_data.networkConfig.serverIp = QString::fromUtf8(tbuf->serverIp);
            dev_data.networkConfig.serverPort = tbuf->serverPort;
            dev_data.networkConfig.panid = tbuf->panid;
            dev_data.networkConfig.isValid  = true;
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        res.first << getSettings().first;
        res.second << getSettings().second;
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        if(replyIsValid) {
            res.second << "getIsReadyCommand" << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "getIsReadyCommand" << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig:
        res.second << "setAccelConfig";
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        if(replyIsValid) {
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig:
        res.second << "setNetworkConfig";
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        if(replyIsValid) {
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData:
        res.second << "setSecurityData";
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        if(replyIsValid) {
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum:
        res.second << "setBatteryNewAccum";
        res.first << "typeCommand" << "resultCommand" << "isNeedAckMessage";
        if(replyIsValid) {
            res.second << "normal" << QString::number(commandReqData.isNeedAckMessage);
        } else {
            res.second << "error" << QString::number(commandReqData.isNeedAckMessage);
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    res.first, res.second, commandReqData);
        break;
    default : break;
    }

    if(replyIsValid) {
        if(getState() == STATE_DISCONNECTED) {
            setState(DeviceAbstract::STATE_START_INIT);
        }
        if(dev_data.networkConfig.isValid && dev_data.security.passwordIsUsed.isValid) {
            setState(DeviceAbstract::STATE_NORMAL_READY);
        }
    }
}

QPair<bool, QPair<int,int>> Nozzle_Revision_0_00_Oct_2018::findTag(QString regExpValueBegin, QString regExpValueEnd, QByteArray data) {
    QPair<bool, QPair<int,int>> res;
    int indexBegin = 0, indexEnd = 0;
    res.first = false;
    indexBegin = data.indexOf(regExpValueBegin);
    if(indexBegin >=0){
        res.second.first = indexBegin;
        indexEnd = data.indexOf(regExpValueEnd);
        if(indexEnd >= 0) {
            res.second.second = indexEnd;
            res.first = true;
        }
    }
    return res;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandToCheckConnected() {
    QList<CommandController::sCommandData> command;
    CommandController::sCommandData simpleCommand;
    simpleCommand.isNeedAckMessage = false;
    simpleCommand.delay_send_ms = 150;
    simpleCommand.operationHeader = "check dev is connected";
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
    makeDataToCommand(simpleCommand);
    command.push_back(simpleCommand);
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandtoCheckPassword() {
    QList<CommandController::sCommandData> command;
    CommandController::sCommandData simpleCommand;
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.delay_send_ms = 150;
    simpleCommand.isNeedAckMessage = false;
    simpleCommand.operationHeader = "check dev password";
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
    makeDataToCommand(simpleCommand);
    command.push_back(simpleCommand);
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData simpleCommand;
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.delay_send_ms = 150;
    simpleCommand.operationHeader = "init dev after connecting";
    simpleCommand.isNeedAckMessage = false;
    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    makeDataToCommand(simpleCommand);
    listCommand.push_back(simpleCommand);
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
    makeDataToCommand(simpleCommand);
    listCommand.push_back(simpleCommand);
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
    makeDataToCommand(simpleCommand);
    listCommand.push_back(simpleCommand);
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
    makeDataToCommand(simpleCommand);
    listCommand.push_back(simpleCommand);
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
    makeDataToCommand(simpleCommand);
    listCommand.push_back(simpleCommand);
    return listCommand;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToUpdate() {
    return getCommandListToInit();
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandToGetType() {
    QList<CommandController::sCommandData> command;
    CommandController::sCommandData simpleCommand;
    simpleCommand.commandType = CommandController::E_CommandType_send_typical_request;
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.delay_send_ms = 150;
    simpleCommand.isNeedAckMessage = false;
    simpleCommand.operationHeader = "get dev type";
    simpleCommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_EmptyCommand;
    makeDataToCommand(simpleCommand);
    command.push_back(simpleCommand);
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.delay_send_ms = 150;
    command.deviceIdent = getUniqId();
    command.operationHeader = "typical command get current data";
    command.isNeedAckMessage = false;
    command.commandType = CommandController::E_CommandType_send_typical_request;
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData;
    makeDataToCommand(command);
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData;
    makeDataToCommand(command);
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData;
    makeDataToCommand(command);
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData;
    makeDataToCommand(command);
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
    makeDataToCommand(command);
    listCommand.push_back(command);
    return listCommand;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
    CommandController::sCommandData tcommand;
    tcommand.operationHeader = operation;
    tcommand.delay_send_ms = 150;
    tcommand.commandType = CommandController::E_CommandType_send_typical_request;
    if(operation == "update device") {
        command = getCommandListToUpdate();
    }
    if(operation == "set current accel value as null pointe") { // TODO:!!!
    } else if(operation == "get current dev settings witout dialog") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = false; // что не нужен ответ на форме
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
        makeDataToCommand(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        command.push_back(tcommand);
    } else if(operation == "get current dev settings") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getSecurityData;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
    } else if(operation == "set current dev settings accel config") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
    } else if(operation == "set current dev password") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setSecurityData;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
    } else if(operation == "set current dev settings net config") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
    } else if(operation == "set new battery") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum;
        makeDataToCommand(tcommand);
        command.push_back(tcommand);
    } else {
        qDebug() << "getCommandCustom -type unknown!";
    }
    return command;
}

QStringList Nozzle_Revision_0_00_Oct_2018::execCommand(QString operation, QPair<QStringList, QStringList>) {

}
