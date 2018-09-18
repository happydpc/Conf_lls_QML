#include "calibrate.h"

Calibrate::Calibrate(QObject *parent) : QObject(parent)
{

}

void Calibrate::reset() {

}
bool Calibrate::addDevice(QString caption, QString uniqNameId) {

}
void Calibrate::removeDevice(int index) {

}

bool Calibrate::addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs) {

}
bool Calibrate::changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs) {

}
void Calibrate::removeStep(int index) {

}

QString Calibrate::getLastError() {

}
