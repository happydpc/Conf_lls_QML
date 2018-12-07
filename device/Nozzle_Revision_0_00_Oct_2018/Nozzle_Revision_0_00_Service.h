#ifndef NOZZLE_REV_0_00_SERVICE_H
#define NOZZLE_REV_0_00_SERVICE_H

#include <QObject>
#include "../service/serviceDevicesAbstract.h"

class Nozzle_Rev_0_00_Service : public ServiceDevicesAbstract
{
public:
    explicit Nozzle_Rev_0_00_Service(std::string owDeviceName);

private:
    std::string lastError;
    Nozzle_Rev_0_00_Service* m_pinstance;
};

#endif // Nozzle_Rev_0_00_Service_H
