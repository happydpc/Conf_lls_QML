#include "tests/testDevReply.h"

#include "device/subDevices/Progress_tmk324.h"

TestDevReply::TestDevReply(QObject *parent) : QObject(parent) {
    this->replyByteArrayBuff.clear();
}

bool TestDevReply::writeDevRequestData(QByteArray &data) {
    bool res = false;
    Progress_tmk324 *tmk24 = new Progress_tmk324();
    res = tmk24->makeDataRequestReply(data, replyByteArrayBuff);
    delete tmk24;
    return res;
}

bool TestDevReply::readDevReplyData(QByteArray &data) {
    data = replyByteArrayBuff;
    return !data.isEmpty();
}
