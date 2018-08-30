#include "commandController.h"

CommandController::CommandController(QObject *parent) : QObject(parent) {

}

bool CommandController::addCommandToStack(QStringList devParamIdent, int command, QByteArray commandData) {
    sCommandElement scommand;
    scommand.commandReqData = commandData;
    scommand.typeComamnd = command;
    QPair<QStringList, QPair<QByteArray,int>> tqueue;
    commandQueue.enqueue(tqueue);
    return !commandQueue.empty();
}

bool CommandController::getCommandFirstCommandFromStack(QStringList &devParamItend, int &command, QByteArray &commandData) {
    bool res = false;
    if(!commandQueue.empty()) {
        auto qcommand = commandQueue.dequeue();
        command = qcommand.second.second;
        devParamItend = qcommand.first;
        commandData = qcommand.second.first;
        res = true;
    }
    return res;
}

bool CommandController::isEmpty() {
    return commandQueue.empty();
}
