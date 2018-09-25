#include <QDebug>
#include "tests/testDevReply.h"
#include "device/deviceAbstract.h"

TestDevReply::TestDevReply(QObject *parent) : QObject(parent) {
    this->replyByteArrayBuff.clear();
}
