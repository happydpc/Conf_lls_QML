#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QQueue>
#include "device/device.h"

class CommandController : public QObject
{
    Q_OBJECT
public:
    explicit CommandController(QObject *parent = nullptr);

    typedef struct {
        QStringList devParam;
        QByteArray commandReqData;
        int typeComamnd;
    }sCommandElement;

    bool addCommandToStack(QStringList devParamIdent, int command, QByteArray commandData);
    bool getCommandFirstCommandFromStack(QStringList &devParamItend, int &command, QByteArray &commandData);

    bool isEmpty();

signals:

public slots:

private:
    QQueue< QPair<QStringList, QPair<QByteArray,int>>> commandQueue;
};

#endif // COMMANDCONTROLLER_H
