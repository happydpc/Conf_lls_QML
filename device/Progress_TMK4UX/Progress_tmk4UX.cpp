#include <QDebug>
#include "Progress_tmk4UX.h"
#include "other/crc.h"

Progress_tmk4UX::Progress_tmk4UX(QString uniqIdentId, QString passwordSession) {
    this->chartData = new QList<int>();
    this->uniqIdentId = uniqIdentId;
    this->state = STATE_DISCONNECTED;
    setDefaultValues();
}

Progress_tmk4UX::~Progress_tmk4UX() {

}

QString Progress_tmk4UX::getDevTypeName() {
    return QString::fromLocal8Bit(Progress_tmk4UX::name, strlen(Progress_tmk4UX::name));
}

QString Progress_tmk4UX::getDevHeader() {
    return "undefined";
}

void Progress_tmk4UX::setDevHeader(QString header) {

}

void Progress_tmk4UX::setDefaultValues() {}

QPair<QStringList,QStringList> Progress_tmk4UX::getPropertyData() {
    return QPair<QStringList,QStringList>();
}

QPair<QStringList,QStringList> Progress_tmk4UX::getCurrentData() {
    return QPair<QStringList,QStringList>();
}

QPair<QStringList,QStringList> Progress_tmk4UX::getErrors() {
    return QPair<QStringList,QStringList>();
}

DeviceAbstract::E_State Progress_tmk4UX::getState() {
    return state;
}

QList<int> Progress_tmk4UX::getChart() {
    return QList<int>();
}

QPair<QStringList,QStringList> Progress_tmk4UX::getSettings() {

}

void Progress_tmk4UX::setState(DeviceAbstract::E_State value) {
    state = value; // если дисконектим или сбрасываем - тогда сбрасываем и данные
    if((state == DeviceAbstract::STATE_DISCONNECTED) || (state == DeviceAbstract::STATE_START_INIT)) {
        setDefaultValues();
    }
}

QString Progress_tmk4UX::getUniqId() {
    return uniqIdentId;
}

bool Progress_tmk4UX::makeDataToCommand(CommandController::sCommandData &commandData) {
    bool res = false;
    return res;
}

bool Progress_tmk4UX::placeDataReplyToCommand(QByteArray &commandArrayReplyData, CommandController::sCommandData commandReqData) {
    bool res = false;
    return res;
}

CommandController::sCommandData Progress_tmk4UX::getCommandToCheckConnected() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_errors;
    return command;
}

CommandController::sCommandData Progress_tmk4UX::getCommandtoCheckPassword() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.devCommand = (int)Progress_tmk4UXData::lls_check_address_and_pass;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandListToInit() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    return listCommand;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandListToUpdate() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    return listCommand;
}

CommandController::sCommandData Progress_tmk4UX::getCommandToGetType() {
    CommandController::sCommandData command;
    command.deviceIdent = getUniqId();
    command.devCommand = (int)Progress_tmk4UXData::lls_read_settings;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandCustom(QString operation) {

}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandListToCurrentData() {
    QList<CommandController::sCommandData> listCommand;
    CommandController::sCommandData command;
    command.commandOptionData.clear();
    command.deviceIdent = getUniqId();
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
