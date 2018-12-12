#include "devicesFactory.h"
#include <QtDebug>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DevicesFactory::DevicesFactory() {}

DevicesFactory::~DevicesFactory() {}

DeviceAbstract* DevicesFactory::newDevice(const std::vector<std::string> keyParam,
                                          const std::vector<std::string> valueParam) {
    std::shared_ptr<DeviceAbstract> device;
    try {
        uint8_t keyCount = 0;
        for(auto keyItem : keyParam) {
            if(keyParam[keyCount] == "devTypeName") {
                if(valueParam[keyCount] == std::string(Progress_tmk24::name)) {
                    device = std::make_shared<Progress_tmk24>(keyParam, valueParam);
                } else if(valueParam[keyCount] == std::string(Nozzle_Revision_0_00_Oct_2018::name)) {
                    device = std::make_shared<Nozzle_Revision_0_00_Oct_2018>(keyParam, valueParam);
                }
            }
        }
    } catch(...) {
        return nullptr;
    }
    return device.get();
}

std::vector<std::string> DevicesFactory::getAvailableTypeDevice() const {
    std::vector<std::string> res;
    res.push_back(std::string(Progress_tmk24::name));
    res.push_back(std::string(Nozzle_Revision_0_00_Oct_2018::name));
    return res;
}
