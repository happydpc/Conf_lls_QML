#include "command.h"

Command::Command(QObject *parent) : QObject(parent) {

}

void Command::setCommand(std::string command) {

}

void Command::setArgs(std::list<std::string> keys, std::list<std::string> values) {

}

void Command::setDelayRequstMs(int delay_ms) {

}

std::string Command::getCommand() {

}

std::pair<std::vector<std::string>,std::vector<std::string>> Command::getArgs() {

}
int Command::getDelayRequstMs() {

}
