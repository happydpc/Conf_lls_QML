#include <QDebug>
#include "tests/testDevReply.h"
#include "device/deviceAbstract.h"
#include "device/subDevices/Progress_tmk24.h"
#include "device/subDevices/Progress_tmk13.h"

TestDevReply::TestDevReply(QObject *parent) : QObject(parent) {
    this->replyByteArrayBuff.clear();
}

//bool TestDevReply::writeDevRequestData(DeviceAbstract::E_DeviceType type, QByteArray &data) {
//    bool res = false;
//#ifdef USE_TEST_DEV_REPLY
//    if(type == DeviceAbstract::Type_Progress_Tmk24) {
//        Progress_tmk24 *tmk24 = new Progress_tmk24();
//        res = tmk24->makeDataRequestReply(data, replyByteArrayBuff);
//        delete tmk24;
//    } else if(type == DeviceAbstract::Type_Progress_Tmk13) {
//        Progress_tmk13 *tmk13 = new Progress_tmk13();
//        res = tmk13->makeDataRequestReply(data, replyByteArrayBuff);
//        delete tmk13;
//    } else {
//        qDebug() << "undefined deviceTy[e [writeDevRequestData]";
//    }
//#endif
//    return res;
//}

//bool TestDevReply::readDevReplyData(QByteArray &data) {
//    data = replyByteArrayBuff;
//    return !data.isEmpty();
//}
