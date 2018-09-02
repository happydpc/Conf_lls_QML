#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include "deviceAbstract.h"
#include "subDevices/Progress_tmk24.h"
#include "subDevices/Progress_tmk13.h"
#include "subDevices/Progress_Base.h"

class Device : public DeviceAbstract
{
public:
    explicit Device(DeviceAbstract::E_DeviceType type,
                    QString deviceUniqIdentName,
                    int deviceUniqIdentId,
                    QStringList &parameters);
    ~Device();
    Device(const Device&);

    void setState(DeviceAbstract::E_State state) override;
    DeviceAbstract::E_State getState() override;
    DeviceAbstract::E_DeviceType getType() override;
    QStringList getSettings() override;
    bool setSettings(QStringList settings) override;
    QStringList getCurrentData() override;
    QStringList getParameters() override;
    QString getUniqIdentName() override;
    int getUniqIdentId() override;
    QList<CommandController::sCommandData> getCommandListToIdlePoll() override;

    bool makeDataToCommand(CommandController::sCommandData &commandData) override;
    bool placeReplyDataOfCommand(QByteArray &array) override;

    QString getCaptionToTypeDevice(DeviceAbstract::E_DeviceType type);
    DeviceAbstract::E_DeviceType getDeviceTypeFromTypeCaption(QString type);

    QStringList getDeviceAvaibleTypes();

    DeviceAbstract::E_DeviceType type;
private:

    ProgressBase *progressBase;
    Progress_tmk24 *progressTmk24;
    Progress_tmk13 *progressTmk13;
};

#endif // DEVICE_H
