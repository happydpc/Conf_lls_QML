#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include "deviceAbstract.h"
#include "subDevices/Progress_tmk324.h"
#include "subDevices/Progress_Base.h"

class Device : public DeviceAbstract
{
public:
    explicit Device(DeviceAbstract::E_DeviceType type,
                    QStringList &parameters);
    ~Device();

    void setState(DeviceAbstract::E_State state) override;
    DeviceAbstract::E_State getState() override;
    DeviceAbstract::E_DeviceType getType() override;
    QStringList getSettings() override;
    bool setSettings(QStringList settings) override;
    QStringList getCurrentData() override;
    QStringList getParameters() override;
    QVector<int> getCommandListToIdlePoll() override;

    bool makeDataToCommand(QByteArray &array, int commandType, QByteArray commandArg) override;
    bool placeReplyDataOfCommand(QByteArray &array, int commandType) override;

    DeviceAbstract::E_DeviceType type;
private:
    Progress_tmk324 *progressTmk324;
    ProgressBase *progressBase;
    QStringList parameters;
};

#endif // DEVICE_H
