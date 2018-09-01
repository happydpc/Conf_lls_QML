#include "commandController.h"

CommandController::CommandController(QObject *parent) : QObject(parent) {

}

bool CommandController::addCommandToStack(sCommandData devCommandData) {
    commandQueue.enqueue(devCommandData);
    return !commandQueue.empty();
}

bool CommandController::getCommandFirstCommandFromStack(sCommandData &devCommandData) {
    bool res = false;
    if(!commandQueue.empty()) {
        devCommandData = commandQueue.dequeue();
        res = true;
    }
    return res;
}

bool CommandController::commandsIsEmpty() {
    return commandQueue.empty();
}
