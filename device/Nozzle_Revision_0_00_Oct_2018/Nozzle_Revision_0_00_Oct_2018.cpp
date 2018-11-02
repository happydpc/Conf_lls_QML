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
    this->dev_data.settings.get.isValid = false;
    this->dev_data.temperature.isValid = false;
    this->dev_data.networkPassword.isValid = false;
    this->dev_data.versionFirmware.isValid = false;
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
    res.first.push_back("netAddress");
    res.second.push_back(deviceIdent.id);
    res.first.push_back("header");
    res.second.push_back(deviceIdent.header);
    res.first.push_back("versionFirmare");
    res.second.push_back(dev_data.versionFirmware.isValid ? dev_data.versionFirmware.value : "NA");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getCurrentData() {
    QPair<QStringList,QStringList> res;
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
    res.second.push_back(dev_data.rssi.isValid ? QString::number(dev_data.rssi.value.value_i) : "NA");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getSettings() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("accelConfX");
    res.second.push_back(dev_data.settings.get.isValid == true ? QString::number(dev_data.settings.get.value.accelConfig.thresholdX) : "NA");
    res.first.push_back("accelConfY");
    res.second.push_back(dev_data.settings.get.isValid == true ? QString::number(dev_data.settings.get.value.accelConfig.thresholdY) : "NA");
    res.first.push_back("accelConfZ");
    res.second.push_back(dev_data.settings.get.isValid == true ? QString::number(dev_data.settings.get.value.accelConfig.thresholdZ) : "NA");
    res.first.push_back("accelAngle");
    res.second.push_back(dev_data.settings.get.isValid == true ? QString::number(dev_data.settings.get.value.accelConfig.delta) : "NA");
    res.first.push_back("networkPassword");
    res.second.push_back(dev_data.networkPassword.isValid == true ? dev_data.networkPassword.value : "NA");
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
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword: {
            typedef struct {
                char password[64];
            }sOutBatBuff;
            sOutBatBuff tbuf;
            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
                if(commandData.args.key[keyCount] == "password") {
                    strcpy(tbuf.password, commandData.args.value[keyCount].toUtf8());
                }
            }
            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;

        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig: {
            typedef struct {
                char networkPassword[64];
            }sOutBatBuff;
            sOutBatBuff tbuf;
            for(int keyCount=0; keyCount<commandData.args.key.size(); keyCount++) {
                if(commandData.args.key[keyCount] == "networkPassword") {
                    strcpy(tbuf.networkPassword, commandData.args.value[keyCount].toUtf8());
                }
            }
            memcpy(tCommand.data.data, (uint8_t*)&tbuf, sizeof(tbuf));
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
        qDebug() << "placeDataReplyToCommand=" << commandArray.data();
        commandArrayReplyData += commandArray;
        auto res = prepareReply(commandArrayReplyData);
        for(auto it:res) {
            qDebug() << "parse=" << it.first;
            if(it.first == "logData") {
                emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Connected, getUniqId(),
                                            commandReqData.devCommand, QString("Status connected"), QStringList(), QStringList(), commandReqData);
                emit eventDeviceUpdateState(Type_DeviceEvent_LogMessage, commandReqData.deviceIdent, 0, "LogMessage", QStringList("message"), QStringList(it.second), commandReqData);
            } else if(it.first == "commandData") {
                parseCommandReply(it.second, commandReqData);
            } else {
                qDebug() << "unknown type";
            }
        }
    } else {
        qDebug() << "placeDataReplyToCommand=" << "-no reply";
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqId(),
                                    commandReqData.devCommand, QString("Status disconnected"), QStringList(), QStringList(), commandReqData);
    }
    return res;
}

void Nozzle_Revision_0_00_Oct_2018::parseCommandReply(QByteArray data, CommandController::sCommandData commandReqData) {    
    Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff *t_reply =
            (Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff*)(data.data());
    qDebug() << "placeDataReplyToCommand - logCommand = "
             << QString((t_reply->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
                         && t_reply->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
                         && t_reply->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) ? "NORMAL REPLY" : "REPLY ERROR");
    if(t_reply->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
            && t_reply->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
            && t_reply->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) {

        if(getState() == STATE_DISCONNECTED) {
            setState(DeviceAbstract::STATE_START_INIT);
        }
        if(dev_data.networkPassword.isValid && dev_data.settings.get.isValid) {
            setState(DeviceAbstract::STATE_NORMAL_READY);
        }
    }

    switch(t_reply->commandType) {
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
        typedef struct {
            float powerVoltage;
            float powerCurrent;
            // тока потребленно
            float powerCurrentAccumulate_mA;
            // ресурс осталось
            float  powerCurrentResouresAvailable_mA;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.powerVoltage.value.value_f = tbuf->powerVoltage;
        dev_data.powerCurrent.value.value_f = tbuf->powerCurrent;
        dev_data.powerCurrentAccumulate_mA.value.value_f = tbuf->powerCurrentAccumulate_mA;
        dev_data.powerCurrentResouresAvailable_mA.value.value_f = tbuf->powerCurrentResouresAvailable_mA;
        dev_data.powerVoltage.isValid = true;
        dev_data.powertypeBattery.isValid = true;
        dev_data.powerCurrent.isValid = true;
        dev_data.powerCurrentAccumulate_mA.isValid = true;
        dev_data.powerCurrentResouresAvailable_mA.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    t_reply->commandType, "Update current data", QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
        typedef struct {
            int thresholdX;
            int thresholdY;
            int thresholdZ;
            int delta;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.settings.get.value.accelConfig.thresholdX = tbuf->thresholdX;
        dev_data.settings.get.value.accelConfig.thresholdY = tbuf->thresholdY;
        dev_data.settings.get.value.accelConfig.thresholdZ = tbuf->thresholdZ;
        dev_data.settings.get.value.accelConfig.delta = tbuf->delta;
        dev_data.settings.get.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
        typedef struct {
            int x;
            int y;
            int z;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.accelX.value.value_i = tbuf->x;
        dev_data.accelY.value.value_i = tbuf->y;
        dev_data.accelZ.value.value_i = tbuf->z;
        dev_data.accelX.isValid = true;
        dev_data.accelY.isValid = true;
        dev_data.accelZ.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    t_reply->commandType, "Update current data", QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData: {
        typedef struct {
            char version[32];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.versionFirmware.value = QString::fromUtf8(tbuf->version);
        dev_data.versionFirmware.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    t_reply->commandType, "Update current data", QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
        typedef struct {
            int status;
            char cardNumber[64];
            uint16_t len;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.cardNumber.value = QString::fromUtf8(tbuf->cardNumber, tbuf->len);
        dev_data.cardState.value.value_i = tbuf->status;
        dev_data.cardNumber.isValid = true;
        dev_data.cardState.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    t_reply->commandType, "Update current data", QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
        typedef struct {
            char networkCurrentIp[64];
            bool status;
            int rssi;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.networkCurrentIp.value = QString::fromUtf8(tbuf->networkCurrentIp);
        dev_data.networkCurrentIp.isValid = true;
        dev_data.rssi.value.value_i = tbuf->rssi;
        dev_data.rssi.history.push_back(tbuf->rssi);
        dev_data.rssi.isValid = true;
        dev_data.networkState.value.value_i = tbuf->status;
        dev_data.networkState.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    t_reply->commandType, "Update current data", QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
        typedef struct {
            char networkPassword[64];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)t_reply->data.data;
        dev_data.networkPassword.value = QString::fromUtf8(tbuf->networkPassword);
        dev_data.networkPassword.isValid = true;
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ReadyReadProperties, getUniqId(),
                                    commandReqData.devCommand, QString("Status ready read properties"), QStringList(), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    t_reply->commandType, "Normal", QStringList(), QStringList(), commandReqData);
        break;
    default : break;
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

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.isNeedAckMessage = false;
    command.operationHeader = "check dev is connected";
    command.deviceIdent = getUniqId();
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    return command;
}

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.isNeedAckMessage = false;
    command.operationHeader = "check dev password";
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.operationHeader = "init dev after connecting";
    command.isNeedAckMessage = false;
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
    listCommand.push_back(command);
    return listCommand;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToUpdate() {
    return getCommandListToInit();
}

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.isNeedAckMessage = false;
    command.operationHeader = "get dev type";
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_EmptyCommand;
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandCustom(QString operation) {
    return getCommandCustom(operation, QPair<QStringList,QStringList>());
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
    CommandController::sCommandData tcommand;
    tcommand.operationHeader = operation;
    tcommand.isNeedIncreasedDelay = false;
    if(operation == "set current accel value as null pointe") { // TODO:!!!
    } else if(operation == "get current dev settings witout dialog") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = false; // что не нужен ответ на форме
        tcommand.isNeedIncreasedDelay = true;
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        command.push_back(tcommand);
    } else if(operation == "get current dev settings") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        command.push_back(tcommand);
    } else if(operation == "set current dev settings accel config") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig;
        tcommand.isNeedIncreasedDelay = true;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else if(operation == "set current dev password") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword;
        tcommand.isNeedIncreasedDelay = true;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else if(operation == "set current dev settings net config") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig;
        tcommand.isNeedIncreasedDelay = true;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i);
        }
        command.push_back(tcommand);
    } else if(operation == "set new battery") {
        tcommand.deviceIdent = getUniqId();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum;
        tcommand.isNeedIncreasedDelay = true;
        command.push_back(tcommand);
    } else {
        qDebug() << "getCommandCustom -type unknown!";
    }
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.operationHeader = "typical command get current data";
    command.isNeedAckMessage = false;
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData;
    listCommand.push_back(command);
    return listCommand;
}
