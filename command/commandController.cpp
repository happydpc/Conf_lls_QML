#include "commandController.h"

CommandController::CommandController(QObject *parent) : QObject(parent) {

}

bool CommandController::addCommandToStack(sCommandData devCommandData) {
    commandQueue.enqueue(devCommandData);
    return !commandQueue.isEmpty();
}

QPair<bool, CommandController::sCommandData> CommandController::getCommandFirstCommand() {
    bool res = false;
    CommandController::sCommandData tcommand;
    if(!commandQueue.empty()) {
        tcommand = commandQueue.first();
        res = true;
    }
    return QPair<bool,CommandController::sCommandData>(res, tcommand);
}

void CommandController::removeFirstCommand() {
    if(!commandQueue.empty()) {
        commandQueue.pop_front();
    }
}

bool CommandController::commandsIsEmpty() {
    return commandQueue.empty();
}
