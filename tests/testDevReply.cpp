#include <QDebug>
#include "tests/testDevReply.h"
#include "device/deviceAbstract.h"
#include "device/subDevices/Progress_tmk24.h"
#include "device/subDevices/Progress_tmk4UX.h"

TestDevReply::TestDevReply(QObject *parent) : QObject(parent) {
    this->replyByteArrayBuff.clear();
}
