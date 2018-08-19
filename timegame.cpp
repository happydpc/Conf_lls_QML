#include "timegame.h"

TimeGame::TimeGame(QObject *parent) : QObject(parent) {
    this->secondTimer = new QTimer();
    this->secondTimer->setInterval(1000);
    connect(this->secondTimer, SIGNAL(timeout()), this, SLOT(updateSecondTimer()));
    this->secondTimer->start();
}

void TimeGame::updateSecondTimer() {
    QDateTime dateTime(QDateTime::currentDateTime());
    emit updateTime(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
}
