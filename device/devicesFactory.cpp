#include "devicesFactory.h"
#include <QtDebug>
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DevicesFactory::DevicesFactory() {}

DevicesFactory::~DevicesFactory() {}

DeviceAbstract* DevicesFactory::newDevice(const QString devType,
                                  const QStringList keyParam, const QStringList valueParam,
                                  ServiceDevicesAbstract *pDevService) {
    std::shared_ptr<DeviceAbstract> device;
    QString devId, devHeader;
    for(int i=0; i<keyParam.size(); i++) {
        if(keyParam[i] == "id") {
            devId = valueParam[i];
        }
        if(keyParam[i] == "header") {
            devHeader = valueParam[i];
        }
    }
    if(!devId.isEmpty()) {
        if(devHeader.isEmpty()) {
            devHeader = "deviceHeader";
        }
        if(devType.toLower() == QString(Progress_tmk24::name).toLower()) {
            device = std::make_shared<Progress_tmk24>(devId, devHeader, keyParam, valueParam, pDevService);
        } else if(devType.toLower() == QString(Nozzle_Revision_0_00_Oct_2018::name).toLower()) { // TODO: need uniqPtr
            device = std::make_shared<Nozzle_Revision_0_00_Oct_2018>(devId, devHeader);
        }
    }
    return device.get();
}
