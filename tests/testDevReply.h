#ifndef TESTDEVREPLY_H
#define TESTDEVREPLY_H

#include <QObject>

class TestDevReply : public QObject
{
    Q_OBJECT
public:
    explicit TestDevReply(QObject *parent = nullptr);

    bool writeDevRequestData(QByteArray &data);
    bool readDevReplyData(QByteArray &data);

private:
    QByteArray replyByteArrayBuff;

};

#endif // TESTDEVREPLY_H
