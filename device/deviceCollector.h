#ifndef DEVICECOLLECTOR_H
#define DEVICECOLLECTOR_H

#include <QObject>
#include <memory>
#include "command/commandController.h"
#include "QTimer"
#include "QMutex"

class DeviceCollector : public QObject
{
    Q_OBJECT
public:
    explicit DeviceCollector();

    bool getIsIdle();
    void addCommand(QList<CommandController::sCommandData> commands);


    void checkDeviceIsOnline(QString devType, QStringList keyParam, QStringList valParam);
    void placeReplyDataFromInterface(QByteArray data);
    void setDeviceCommandUpdateByIndex(int index);
    void setDeviceInitCommandByIndex(int index);
    void setDeviceReInitByIndex(int index);
    bool sendCustomCommadToDev(int indexDev, QString operation, QStringList keys, QStringList values);
    bool sendCustomCommadToDev(int indexDev, QString operation);
    void sendCustomCommandUseCallback(QString devType, QString operation, QStringList keys, QStringList values);

signals:
    void deviceCheckIsReady(QString devType, QString uniqNameId, bool isOnline);
    void writeData(QByteArray data);
    void readReplyData();

private slots:
    void devShedullerSlot();
    void onReplySend();

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

    QScopedPointer<QTimer> sendReqTimer;
    int indexProcessedDev = 50;
    const int delayTypicalCommandMs = 200;
    const int delayIncreasedCommandMs = 300;
};

#endif // DEVICECOLLECTOR_H
