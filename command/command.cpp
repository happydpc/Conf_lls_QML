#include "command.h"

Command::Command(QObject *parent) :
    QObject(parent),
    isExecuted(false) {
}

Command::Command(const Command & command) {
    this->isExecuted = command.isExecuted;
    this->command = command.command;
    this->args = command.args;
    this->result = command.result;
    this->delay_request_ms = command.delay_request_ms;
}

void Command::setCommand(std::string command) {
    this->command = command;
}

std::string Command::getCommand() {
    return command;
}

void Command::setArgs(std::vector<std::string> keys, std::vector<std::string> values) {
    args.key = keys;
    args.value = values;
}

std::pair<std::vector<std::string>,std::vector<std::string>> Command::getArgs() {
    return std::pair<std::vector<std::string>,std::vector<std::string>>(args.key, args.value);
}

void Command::setResult(std::vector<std::string> keys, std::vector<std::string> values) {
    result.key = keys;
    result.value = values;
}

std::pair<std::vector<std::string>,std::vector<std::string>> Command::getResult() {
    return std::pair<std::vector<std::string>,std::vector<std::string>>(result.key, result.value);
}

void Command::setIsExecuted() {
    isExecuted = true;
}

bool Command::getIsExecuted() {
    return isExecuted;
}

void Command::setDelayRequstMs(int delay_ms) {

}

int Command::getDelayRequstMs() {

}
