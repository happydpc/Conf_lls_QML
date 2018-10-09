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
    this->lls_data.accelX.isValid = false;
    this->lls_data.accelY.isValid = false;
    this->lls_data.accelZ.isValid = false;
    this->lls_data.cardNumber.isValid = false;
    this->lls_data.cardState.isValid = false;
    this->lls_data.networkParentIp.isValid = false;
    this->lls_data.networkState.isValid = false;
    this->lls_data.powerCurrentAccumulate.isValid = false;
    this->lls_data.powerCurrentAccumulateHourse.isValid = false;
    this->lls_data.powerCurrentResouresAvailable.isValid = false;
    this->lls_data.powerCurrentResouresAvailableHourse.isValid = false;
    this->lls_data.powertypeBattery.isValid = false;
    this->lls_data.powerVoltage.isValid = false;
    this->lls_data.settings.get.isValid = false;
    this->lls_data.temperature.isValid = false;
    this->lls_data.networkPassword.isValid = false;
}

QList<int> Nozzle_Revision_0_00_Oct_2018::getChart() {
    return *chartData;
}

ServiceDevicesAbstract* Nozzle_Revision_0_00_Oct_2018::getServiceAbstract() {
    return nullptr;
}

QStringList Nozzle_Revision_0_00_Oct_2018::getPropertyData() {
    QStringList res;
    res << getDevTypeName();
    res << uniqIdentId;
    return res;
}

QStringList Nozzle_Revision_0_00_Oct_2018::getCurrentData() {
    QList<QString> res;
    res.push_back(lls_data.accelX.isValid == true ? QString::number(lls_data.accelX.value.value_f) : "NA");
    res.push_back(lls_data.accelY.isValid == true ? QString::number(lls_data.accelY.value.value_f) : "NA");
    res.push_back(lls_data.accelZ.isValid == true ? QString::number(lls_data.accelZ.value.value_f) : "NA");
    res.push_back(lls_data.cardNumber.isValid == true ? lls_data.cardNumber.value : "NA");
    res.push_back(lls_data.cardState.isValid == true ? QString::number(lls_data.cardState.value.value_i) : "NA");
    res.push_back(lls_data.networkParentIp.isValid == true ? lls_data.networkParentIp.value : "NA");
    res.push_back(lls_data.networkState.isValid == true ? (lls_data.networkState.value.value_i == true ? "Подключено" : "Не подключено") : "NA");
    res.push_back(lls_data.temperature.isValid == true ? QString::number(lls_data.temperature.value.value_f) : "NA");
    res.push_back(lls_data.powerVoltage.isValid == true ? QString::number(lls_data.powerVoltage.value.value_f) : "NA");
    res.push_back(lls_data.powertypeBattery.isValid == true ? lls_data.powertypeBattery.value : "NA");
    res.push_back(lls_data.powerCurrentAccumulate.isValid == true ? QString::number(lls_data.powerCurrentAccumulate.value.value_f) : "NA");
    res.push_back(lls_data.powerCurrentAccumulateHourse.isValid == true ? QString::number(lls_data.powerCurrentAccumulateHourse.value.value_f) : "NA");
    res.push_back(lls_data.powerCurrentResouresAvailable.isValid == true ? QString::number(lls_data.powerCurrentResouresAvailable.value.value_f) : "NA");
    res.push_back(lls_data.powerCurrentResouresAvailableHourse.isValid == true ? QString::number(lls_data.powerCurrentResouresAvailableHourse.value.value_f) : "NA");
    res.push_back(lls_data.networkPassword.isValid == true ? lls_data.networkPassword.value : "NA");
    return res;
}

QPair<QStringList,QStringList> Nozzle_Revision_0_00_Oct_2018::getSettings() {
    QPair<QStringList,QStringList> res;
    if(lls_data.settings.get.isValid) {
        res.first.push_back("device_value");
        res.second.push_back(getDevTypeName());
        res.first.push_back("k1_value");
    }
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
    tCommand.argCount = 0;
    tCommand.magic_word = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_MAGIC_WORD;
    tCommand.devieIcdent = Nozzle_Revision_0_00_Oct_2018_Data::CONSOLE_DEVICE_IDENT;
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
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryProperty: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardProperty: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;
        case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
            commandData.commandOptionData.insert(0, (char*)&tCommand, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleBufData));
            res = true;
        }
            break;

            //            Nozzle_Revision_0_00_Oct_2018_Data::T_settings tSettings;
            //            if(lls_data.settings.get.isValid) {
            //                memcpy(&tSettings, &lls_data.settings.get.value, sizeof(tSettings));
            //                for(int i=0; i<commandData.args.key.size(); i++) {
            //                    if(commandData.args.key.at(i) == "k1_value") {
            //                        //                            tSettings.k1 = commandData.args.value.at(i);
            //                    } else {
            //                        qDebug() << "settings udnefined type parcing";
            //                    }
            //                }
            //                commandData.commandOptionData.insert(13, (char*)&tSettings, sizeof(Nozzle_Revision_0_00_Oct_2018_Data::T_settings));
            //            }
            //            res = true;
            //        }
            //            break;
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

                    emit eventDeviceMessage(commandReqData.deviceIdent, QStringList(tlog));
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
            }
        }
    }
    return res;
}

void Nozzle_Revision_0_00_Oct_2018::parseCommandReply(Nozzle_Revision_0_00_Oct_2018_Data::sConsoleReplyBuff command,CommandController::sCommandData commandReqData) {
    switch(command.commandType) {
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryProperty: {
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
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data;
        lls_data.powerVoltage.value.value_f = tbuf->powerVoltage;
        lls_data.powertypeBattery.value = QString::fromUtf8(tbuf->powertypeBattery);
        lls_data.powerCurrentAccumulate.value.value_f = tbuf->powerCurrentAccumulate;
        lls_data.powerCurrentAccumulateHourse.value.value_f = tbuf->powerCurrentAccumulateHourse;
        lls_data.powerCurrentResouresAvailable.value.value_f = tbuf->powerCurrentResouresAvailable;
        lls_data.powerCurrentResouresAvailableHourse.value.value_f = tbuf->powerCurrentResouresAvailableHourse;
        //
        lls_data.powerVoltage.isValid = true;
        lls_data.powertypeBattery.isValid = true;
        lls_data.powerCurrentAccumulate.isValid = true;
        lls_data.powerCurrentAccumulateHourse.isValid = true;
        lls_data.powerCurrentResouresAvailable.isValid = true;
        lls_data.powerCurrentResouresAvailableHourse.isValid = true;
        emit eventDeviceUpdateState(Type_DeviceEvent_ExectCustomCommand, commandReqData.deviceIdent, command.commandType, "Normal", QStringList(""), commandReqData);
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig: {
        typedef struct {
            int thresholdX;
            int thresholdY;
            int thresholdZ;
            int delta;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data;
        lls_data.accelConfX.value.value_i = tbuf->thresholdX;
        lls_data.accelConfY.value.value_i = tbuf->thresholdY;
        lls_data.accelConfZ.value.value_i = tbuf->thresholdZ;
        lls_data.accelConfDelta.value.value_i = tbuf->delta;
        lls_data.accelConfX.isValid = true;
        lls_data.accelConfY.isValid = true;
        lls_data.accelConfZ.isValid = true;
        lls_data.accelConfDelta.isValid = true;
    }
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData: {
        lls_data.accelX.value.value_f = 0;
        lls_data.accelY.value.value_f = 0;
        lls_data.accelZ.value.value_f = 0;
        lls_data.accelX.isValid = true;
        lls_data.accelY.isValid = true;
        lls_data.accelZ.isValid = true;
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardProperty: {
        typedef struct {
            int status;
            char cardNumber[64];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data;
        lls_data.cardNumber.value = QString::fromUtf8(tbuf->cardNumber);
        lls_data.cardState.value.value_i = tbuf->status;
        lls_data.cardNumber.isValid = true;
        lls_data.cardState.isValid = true;
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData: {
        typedef struct {
            char networkParentIp[64];
            bool status;
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data;
        lls_data.networkParentIp.value = QString::fromUtf8(tbuf->networkParentIp);
        lls_data.networkParentIp.isValid = true;
        lls_data.networkState.value.value_i = tbuf->status;
        lls_data.networkState.isValid = true;
    }
        break;
    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig: {
        typedef struct {
            char networkPassword[64];
        }sOutBatBuff;
        sOutBatBuff *tbuf = (sOutBatBuff*)command.data;
        lls_data.networkPassword.value = QString::fromUtf8(tbuf->networkPassword);
        lls_data.networkPassword.isValid = true;
    }
        break;

    case Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand: {
        lls_data.temperature.value.value_i = 32;
        lls_data.temperature.isValid = true;
    }
    default : break;
    }
    if(getState() == STATE_DISCONNECTED) {
        setState(DeviceAbstract::STATE_START_INIT);
    }
    if(lls_data.networkPassword.isValid && lls_data.accelConfX.isValid
            && lls_data.accelConfY.isValid && lls_data.accelConfZ.isValid) {
        setState(DeviceAbstract::STATE_NORMAL_READY);
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
    if(operation == "set current level value as min") {

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
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryProperty;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData;
    listCommand.push_back(command);
    command.devCommand = (int)Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardProperty;
    listCommand.push_back(command);
    return listCommand;
}
