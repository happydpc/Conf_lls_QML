#include "command.h"

Command::Command(QObject *parent) : QObject(parent) {

}

void Command::setCommand(QString command) {

}

void Command::setArgs(QStringList keys, QStringList values) {

}

void Command::setDelayRequstMs(int delay_ms) {

}

QString Command::getCommand() {

}

QPair<QStringList,QStringList> Command::getArgs() {

}
int Command::getDelayRequstMs() {

}
