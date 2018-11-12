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
    delete chartData;
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

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandToCheckConnected() {
    QList<CommandController::sCommandData> command;
    CommandController::sCommandData simpleCommand;
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.devCommand = (int)Progress_tmk4UXData::lls_read_errors;
    command.push_back(simpleCommand);
    return command;
}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandtoCheckPassword() {
    CommandController::sCommandData simpleCommand;
    QList<CommandController::sCommandData> command;
    simpleCommand.deviceIdent = getUniqId();
    simpleCommand.devCommand = (int)Progress_tmk4UXData::lls_check_address_and_pass;
    command.push_back(simpleCommand);
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

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandToGetType() {}

QList<CommandController::sCommandData> Progress_tmk4UX::getCommandCustom(QString operation, QPair<QStringList, QStringList> data) {
    QList <CommandController::sCommandData> command;
    return command;
}

QStringList Progress_tmk4UX::execCommand(QString operation, QPair<QStringList,QStringList> data) {}

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
