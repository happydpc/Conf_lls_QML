#ifndef DEVICECOLLECTOR_H
#define DEVICECOLLECTOR_H

#include <QObject>
#include <memory>
#include "command/commandController.h"
#include "interfaces/interfacesAbstract.h"
#include "QTimer"
#include "QMutex"

class DeviceCollector : public QObject
{
    Q_OBJECT
public:
    explicit DeviceCollector(interfacesAbstract *p_int_abstract);

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

    interfacesAbstract* int_abstract;
    std::unique_ptr<CommandController> commandController;
    std::unique_ptr<QTimer> reqTimerHanler;
    bool reqIsBusy;
    QScopedPointer<QTimer> sendReqTimer;
};

#endif // DEVICECOLLECTOR_H
