#ifndef TESTDEVREPLY_H
#define TESTDEVREPLY_H

#include <QObject>
#include "device/deviceAbstract.h"

class TestDevReply : public QObject
{
    Q_OBJECT
public:
    explicit TestDevReply(QObject *parent = nullptr);

//    bool writeDevRequestData(DeviceAbstract::E_DeviceType type, QByteArray &data);
//    bool readDevReplyData(QByteArray &data);

private:
    QByteArray replyByteArrayBuff;

};

#endif // TESTDEVREPLY_H
