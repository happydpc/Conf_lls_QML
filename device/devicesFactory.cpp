#include "devicesFactory.h"
#include <QtDebug>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DevicesFactory::DevicesFactory() {}

DevicesFactory::~DevicesFactory() {}

DeviceAbstract* DevicesFactory::newDevice(const std::string devType,
                                          const std::list<std::string> keyParam,
                                          const std::list<std::string> valueParam) {
    std::shared_ptr<DeviceAbstract> device;
    try {
        if(devType == std::string(Progress_tmk24::name)) {
            device = std::make_shared<Progress_tmk24>(keyParam, valueParam);
        } else if(devType == std::string(Nozzle_Revision_0_00_Oct_2018::name)) {
            device = std::make_shared<Nozzle_Revision_0_00_Oct_2018>(keyParam, valueParam);
        }
    } catch(...) {
        return nullptr;
    }
    return device.get();
}

std::list<std::string> DevicesFactory::getAvailableTypeDevice() const {
    std::list<std::string> res;
    res.push_back(std::string(Progress_tmk24::name));
    res.push_back(std::string(Nozzle_Revision_0_00_Oct_2018::name));
    return res;
}
