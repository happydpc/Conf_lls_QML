#ifndef DEVICECOLLECTOR_H
#define DEVICECOLLECTOR_H

#include <QObject>
#include <memory>
#include "command/commandController.h"
#include "interfaces/ioAbstract.h"
#include "QTimer"
#include "QMutex"

class DeviceCollector : public QObject
{
    Q_OBJECT
public:
    explicit DeviceCollector(IoAbstract *p_int_abstract);

    void addCommand(const QList<CommandController::sCommandData> commands);
    bool getIsIdle() const;

signals:
    void deviceCheckIsReady(QString devType, QString uniqNameId, bool isOnline);
    void reqReadyReplyDataToDevice(QByteArray data, CommandController::sCommandData command);

private slots:
    void controllHandler();
    void readyReadReply();

private:
    bool isIdle;

    struct {
        QString checkedDeviceUniqName;
        QString devType;
        bool isIdle = true;
        bool isProcessed = false;
        bool isReady = false;
        bool result = false;
    }checkDeviceStruct;

    IoAbstract* int_abstract;
    std::shared_ptr<CommandController> commandController;
    std::shared_ptr<QTimer> reqTimerHanler;
    bool reqIsBusy;
    QScopedPointer<QTimer> sendReqTimer;
};

#endif // DEVICECOLLECTOR_H
