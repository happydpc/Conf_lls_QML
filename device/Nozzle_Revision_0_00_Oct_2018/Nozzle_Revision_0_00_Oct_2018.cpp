#include <QDebug>
#include "Nozzle_Revision_0_00_Oct_2018.h"
#include "other/crc.h"
#include <QList>

Nozzle_Revision_0_00_Oct_2018::Nozzle_Revision_0_00_Oct_2018(QString devName) {
    this->chartData = new QList<int>();
    this->uniqIdentId = devName;
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

void Nozzle_Revision_0_00_Oct_2018::setDefaultValues() {
    this->dev_data.accelX.isValid = false;
    this->dev_data.accelY.isValid = false;
    this->dev_data.accelZ.isValid = false;
    this->dev_data.cardNumber.isValid = false;
    this->dev_data.cardState.isValid = false;
    this->dev_data.networkParentIp.isValid = false;
    this->dev_data.networkState.isValid = false;
    this->dev_data.powerCurrentAccumulate.isValid = false;
    this->dev_data.powerCurrentAccumulateHourse.isValid = false;
    this->dev_data.powerCurrentResouresAvailable.isValid = false;
    this->dev_data.powerCurrentResouresAvailableHourse.isValid = false;
    this->dev_data.powertypeBattery.isValid = false;
    this->dev_data.powerVoltage.isValid = false;
    this->dev_data.settings.get.isValid = false;
    this->dev_data.temperature.isValid = false;
    this->dev_data.networkPassword.isValid = false;
}

QList<int> Nozzle_Revision_0_00_Oct_2018::getChart() {
    return *chartData;
}

ServiceDevicesAbstract* Nozzle_Revision_0_00_Oct_2018::getServiceAbstract() {
    return nullptr;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getPropertyData() {
    QPair<QStringList,QStringList> res;
    res.first.push_back("devTypeName");
    res.second.push_back(getDevTypeName());
    res.first.push_back("serialNum");
    res.second.push_back(serialNumber.isEmpty() ? QString("Не присвоен") : serialNumber);
    res.first.push_back("netAddress");
    res.second.push_back(uniqIdentId);
    res.first.push_back("firmware");
    res.second.push_back(versionFirmware.isEmpty() ? QString("NA") : versionFirmware);
    res.first.push_back("uniqIdentId");
    res.second.push_back(uniqIdentId);
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
    res.first.push_back("networkParentIp");
    res.second.push_back(dev_data.networkParentIp.isValid == true ? dev_data.networkParentIp.value : "NA");
    res.first.push_back("networkState");
    res.second.push_back(dev_data.networkState.isValid == true ? (dev_data.networkState.value.value_i == true ? "Подключено" : "Не подключено") : "NA");
    res.first.push_back("temperature");
    res.second.push_back(dev_data.temperature.isValid == true ? QString::number(dev_data.temperature.value.value_f) : "NA");
    res.first.push_back("powerVoltage");
    res.second.push_back(dev_data.powerVoltage.isValid == true ? QString::number(dev_data.powerVoltage.value.value_f) : "NA");
    res.first.push_back("powertypeBattery");
    res.second.push_back(dev_data.powertypeBattery.isValid == true ? dev_data.powertypeBattery.value : "NA");
    res.first.push_back("powerCurrentAccumulate");
    res.second.push_back(dev_data.powerCurrentAccumulate.isValid == true ? QString::number(dev_data.powerCurrentAccumulate.value.value_f) : "NA");
    res.first.push_back("powerCurrentAccumulateHourse");
    res.second.push_back(dev_data.powerCurrentAccumulateHourse.isValid == true ? QString::number(dev_data.powerCurrentAccumulateHourse.value.value_f) : "NA");
    res.first.push_back("powerCurrentResouresAvailable");
    res.second.push_back(dev_data.powerCurrentResouresAvailable.isValid == true ? QString::number(dev_data.powerCurrentResouresAvailable.value.value_f) : "NA");
    res.first.push_back("powerCurrentResouresAvailableHourse");
    res.second.push_back(dev_data.powerCurrentResouresAvailableHourse.isValid == true ? QString::number(dev_data.powerCurrentResouresAvailableHourse.value.value_f) : "NA");
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
    res.first.push_back("accelConfDelta");
    res.second.push_back(dev_data.settings.get.isValid == true ? QString::number(dev_data.settings.get.value.accelConfig.delta) : "NA");
    res.first.push_back("networkPassword");
    res.second.push_back(dev_data.networkPassword.isValid == true ? dev_data.networkPassword.value : "NA");
    return res;
}

QStringList Nozzle_Revision_0_00_Oct_2018::getErrors() {
    QStringList ret;
    return ret;
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

QString Nozzle_Revision_0_00_Oct_2018::getUniqIdent() {
    return uniqIdentId;
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
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig:
//            accelConfX
//            accelConfDelta
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig:
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
            break;
        default : break;
        }
    } catch(...) {
        qDebug("Device: makeDataToCommand -catch!");
    }
    return res;
}

bool Nozzle_Revision_0_00_Oct_2018::placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) {
    bool res = false;
    int indexStartLog = 0;
    int indexEndLog = 0;
    Crc crc;
    if(!commandArrayReplyData.isEmpty()) {
        qDebug() << "placeDataReplyToCommand inputBuf =" << commandArrayReplyData.data();

        // logs
        std::string log(commandArrayReplyData.data());
        while(1) {
            indexStartLog = log.find(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind);
            indexEndLog = log.find(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd);
            if((indexStartLog != log.npos) && (indexEndLog != log.npos)) {
                char tlog[128] = {0};
                log.copy(tlog, indexEndLog - indexStartLog - strlen(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind), indexStartLog + strlen(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderBegind));
                log.erase(log.begin(), log.begin() + indexEndLog + strlen(Nozzle_Revision_0_00_Oct_2018_Data::logHeaderEnd));
                if(strlen(tlog)>0) {
                    qDebug() << "placeDataReplyToCommand - logMessage = " << QString(tlog);
                    emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Connected, getUniqIdent(),
                                                commandReqData.devCommand, QString("Status connected"), QStringList(), commandReqData);
                    emit eventDeviceUpdateState(Type_DeviceEvent_LogMessage, commandReqData.deviceIdent, 0, "LogMessage", QStringList(tlog), commandReqData);
                }
            } else {
                break;
            }
        }
        // commands
        indexEndLog = 0;
        indexStartLog = 0;
        for(int it=0; it<commandArrayReplyData.size(); it++) {
            if(commandArrayReplyData.at(it) == Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind[0]) {
                if(it+1 < commandArrayReplyData.size()) {
                    if(commandArrayReplyData.at(it+1) == Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind[1]) {
                        indexStartLog = it;
                    }
                }
            }
            if(commandArrayReplyData.at(it) == Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd[0]) {
                if(it+1 < commandArrayReplyData.size()) {
                    if(commandArrayReplyData.at(it+1) == Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd[1]) {
                        indexEndLog = it;
                    }
                }
            }
        }
        if((indexStartLog < commandArrayReplyData.size()) && (indexEndLog != 0)) {
            Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff *tReplyCommand;
            int size = indexEndLog - indexStartLog - strlen(Nozzle_Revision_0_00_Oct_2018_Data::logCommandEnd);
            QByteArray logArray = commandArrayReplyData.mid(indexStartLog + strlen(Nozzle_Revision_0_00_Oct_2018_Data::logCommandBegind), size);
            tReplyCommand = (Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff*)(logArray.data());
            qDebug() << "placeDataReplyToCommand - logCommand = "
                     << QString((tReplyCommand->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
                                 && tReplyCommand->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
                                 && tReplyCommand->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) ? "NORMAL REPLY" : "REPLY ERROR");
            if(tReplyCommand->deviceIdent == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT
                    && tReplyCommand->versionProtocol == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_VERSION_PROTOCOL
                    && tReplyCommand->magic_word == Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD) {

                parseCommandReply(*tReplyCommand, commandReqData);

                if(getState() == STATE_DISCONNECTED) {
                    setState(DeviceAbstract::STATE_START_INIT);
                }
                if(dev_data.networkPassword.isValid && dev_data.settings.get.isValid) {
                    setState(DeviceAbstract::STATE_NORMAL_READY);
                }
            }
        }
    } else {
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_Disconnected, getUniqIdent(),
                                    commandReqData.devCommand, QString("Status disconnected"), QStringList(), commandReqData);
    }
    return res;
}

void Nozzle_Revision_0_00_Oct_2018::parseCommandReply(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff command,CommandController::sCommandData commandReqData) {
    switch(command.commandType) {
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData: {
        typedef struct {
            float powerVoltage;
            char powertypeBattery[32];
            // тока потребленно
            float powerCurrentAccumulate;
            // тока потребленно (часов)
            float  powerCurrentAccumulateHourse;
            // ресурс осталось (часов)
            float  powerCurrentResouresAvailable;
            float  powerCurrentResouresAvailableHourse;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.powerVoltage.value.value_f = tbuf->powerVoltage;
        dev_data.powertypeBattery.value = QString::fromUtf8(tbuf->powertypeBattery);
        dev_data.powerCurrentAccumulate.value.value_f = tbuf->powerCurrentAccumulate;
        dev_data.powerCurrentAccumulateHourse.value.value_f = tbuf->powerCurrentAccumulateHourse;
        dev_data.powerCurrentResouresAvailable.value.value_f = tbuf->powerCurrentResouresAvailable;
        dev_data.powerCurrentResouresAvailableHourse.value.value_f = tbuf->powerCurrentResouresAvailableHourse;
        //
        dev_data.powerVoltage.isValid = true;
        dev_data.powertypeBattery.isValid = true;
        dev_data.powerCurrentAccumulate.isValid = true;
        dev_data.powerCurrentAccumulateHourse.isValid = true;
        dev_data.powerCurrentResouresAvailable.isValid = true;
        dev_data.powerCurrentResouresAvailableHourse.isValid = true;

        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    command.commandType, "Update current data", QStringList(""), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
        typedef struct {
            int thresholdX;
            int thresholdY;
            int thresholdZ;
            int delta;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.settings.get.value.accelConfig.thresholdX = tbuf->thresholdX;
        dev_data.settings.get.value.accelConfig.thresholdY = tbuf->thresholdY;
        dev_data.settings.get.value.accelConfig.thresholdZ = tbuf->thresholdZ;
        dev_data.settings.get.value.accelConfig.delta = tbuf->delta;
        dev_data.settings.get.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
        typedef struct {
            int x;
            int y;
            int z;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.accelX.value.value_i = tbuf->x;
        dev_data.accelY.value.value_i = tbuf->y;
        dev_data.accelZ.value.value_i = tbuf->z;
        dev_data.accelX.isValid = true;
        dev_data.accelY.isValid = true;
        dev_data.accelZ.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    command.commandType, "Update current data", QStringList(""), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData: {
        typedef struct {
            int status;
            char cardNumber[64];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.cardNumber.value = QString::fromUtf8(tbuf->cardNumber);
        dev_data.cardState.value.value_i = tbuf->status;
        dev_data.cardNumber.isValid = true;
        dev_data.cardState.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    command.commandType, "Update current data", QStringList(""), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
        typedef struct {
            char networkParentIp[64];
            bool status;
            int rssi;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.networkParentIp.value = QString::fromUtf8(tbuf->networkParentIp);
        dev_data.networkParentIp.isValid = true;
        dev_data.rssi.value.value_i = tbuf->rssi;
        dev_data.rssi.history.push_back(tbuf->rssi);
        dev_data.rssi.isValid = true;
        dev_data.networkState.value.value_i = tbuf->status;
        dev_data.networkState.isValid = true;

        chartData->push_back(dev_data.rssi.value.value_i + (rand()%1));
        while(chartData->size() > 50) {
            chartData->pop_front();
        }
        emit eventDeviceUpdateState(Type_DeviceEvent_CurrentDataUpdated, commandReqData.deviceIdent,
                                    command.commandType, "Update current data", QStringList(""), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
        typedef struct {
            char networkPassword[64];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data.data;
        dev_data.networkPassword.value = QString::fromUtf8(tbuf->networkPassword);
        dev_data.networkPassword.isValid = true;
        emit eventDeviceUpdateState(DeviceAbstract::Type_DeviceEvent_ReadyReadProperties, getUniqIdent(),
                                    commandReqData.devCommand, QString("Status ready read properties"), QStringList(), commandReqData);
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig:
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent,
                                    command.commandType, "Normal", QStringList(""), commandReqData);
        break;
    default : break;
    }
}

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    return command;
}

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
    listCommand.push_back(command);
    return listCommand;
}

CommandController::sCommandData Nozzle_Revision_0_00_Oct_2018::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
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
    if(operation == "set current accel value as null pointe") { // TODO:!!!
    } else if(operation == "get current dev settings witout dialog") {
        tcommand.deviceIdent = getUniqIdent();
        tcommand.isNeedAckMessage = false; // что не нужен ответ на форме
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        command.push_back(tcommand);
    } else if(operation == "get current dev settings") {
        tcommand.deviceIdent = getUniqIdent();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig;
        command.push_back(tcommand);
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig;
        command.push_back(tcommand);
    } else if(operation == "set current dev settings accel config") {
        tcommand.deviceIdent = getUniqIdent();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i.toDouble());
        }
        command.push_back(tcommand);
    } else if(operation == "set current dev settings net config") {
        tcommand.deviceIdent = getUniqIdent();
        tcommand.isNeedAckMessage = true; // что нужен ответ на форме (сообщение ок)
        tcommand.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig;
        // key
        for(auto i:data.first) {
            tcommand.args.key.push_back(i);
        }
        // value
        for(auto i:data.second) {
            tcommand.args.value.push_back(i.toDouble());
        }
        command.push_back(tcommand);
    } else {
        qDebug() << "getCommandCustom -type unknown!";
    }
    return command;
}

QList<CommandController::sCommandData> Nozzle_Revision_0_00_Oct_2018::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.deviceIdent = getUniqIdent();
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData;
    listCommand.push_back(command);
    return listCommand;
}
