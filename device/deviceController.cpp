#include "deviceController.h"
#include "device/Progress_TMK24/Progress_tmk24Service.h"
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"

DeviceController::DeviceController(interfacesAbstract *p_int_abstract) {
    this->deviceFactory = std::make_shared<DevicesFactory>();
    this->deviceCollector = std::make_shared<DeviceCollector>(p_int_abstract);
    this->updateTimer = std::make_unique<QTimer>();
    this->devMutex = std::make_unique<QMutex>();
    this->updateTimer->start(100);

    serviceList.push_back(std::make_shared<Progress_tmk24Service>("PROGRESS TMK24"));
    serviceList.push_back(std::make_shared<Nozzle_Rev_0_00_Service>("Nozzle Rev 0.0"));

    connect(this->updateTimer.get(), SIGNAL(timeout()), this, SLOT(updater()));
    connect(this->deviceCollector.get(), &DeviceCollector::reqReadyReplyDataToDevice, this,
            [&](QByteArray replyData, CommandController::sCommandData command) {
        if(devMutex.get()->tryLock(100)) {
            auto dev = deviceFactory.get()->findDeviceByUnicIdent(command.deviceIdent);
            if(dev != nullptr) {
                dev->second->placeDataReplyToCommand(replyData, command);
            }
            devMutex.get()->unlock();
        }
    });
}

DevicesFactory* DeviceController::getDeviceFactory() {
    DevicesFactory* p_ret_factoty = nullptr;
    p_ret_factoty = deviceFactory.get();
    return p_ret_factoty;
}

DeviceCollector* DeviceController::getDeviceCollector() {
    DeviceCollector* p_ret_collector = nullptr;
    p_ret_collector = deviceCollector.get();
    return p_ret_collector;
}

void DeviceController::resetAll() {
    deviceFactory.reset();
    deviceCollector.reset();
}

void DeviceController::updater() {
    static int indexProcessedDev = 0;
    // if collector is ready
    if(deviceCollector.get()->getIsIdle()) {
        // if deviceMap is not empty
        if(deviceFactory.get()->getDeviceCount()) {
            // bust all device
            if(indexProcessedDev < deviceFactory.get()->getDeviceCount()-1) {
                indexProcessedDev ++;
            } else {
                indexProcessedDev = 0;
            }
            DeviceAbstract *p_abstr_dev = nullptr;
            p_abstr_dev = getDeviceFactory()->getDeviceToDeviceAbstract(indexProcessedDev);
            if(p_abstr_dev != nullptr) {
                switch(p_abstr_dev->getState()) {
                case DeviceAbstract::STATE_DISCONNECTED:
                    deviceCollector.get()->addCommand(p_abstr_dev->getCommandToCheckConnected());
                    break;
                case DeviceAbstract::STATE_GET_TYPE:
                    deviceCollector.get()->addCommand(p_abstr_dev->getCommandToGetType());
                    break;
                case DeviceAbstract::STATE_CHECK_PASSWORD:
                    deviceCollector.get()->addCommand(p_abstr_dev->getCommandtoCheckPassword());
                    break;
                case DeviceAbstract::STATE_START_INIT:
                    deviceCollector.get()->addCommand(p_abstr_dev->getCommandListToInit());
                    break;
                case DeviceAbstract::STATE_NORMAL_READY:
                    deviceCollector.get()->addCommand(p_abstr_dev->getCommandListToCurrentData());
                    break;
                }
            }
        }
    }
}

bool DeviceController::addDevice(QString devTypeName, QStringList keyParam, QStringList valueParam) {
    if(devMutex->tryLock(1000)) {
        for(auto service:serviceList) {
            if(service.get()->getDeviceType() == devTypeName) {
                deviceFactory.get()->addNewDevice(devTypeName, keyParam, valueParam, service.get());
                devMutex->unlock();
                return true;
            }
        }
        devMutex->unlock();
    }
    return false;
}

bool DeviceController::removeDevice(QString devId) {
    if(devMutex->tryLock(1000)) {
        deviceFactory.get()->removeDevice(devId);
        devMutex->unlock();
    }
}

//********************************************/
// its for send deffered request
//********************************************/
bool DeviceController::sendCommadToDev(QString devId, QString operation, QStringList keys, QStringList values) {
    QList<CommandController::sCommandData> command;
    QPair<QStringList,QStringList> arguments;
    bool res = false;
    for(int i=0; i<keys.size(); i++) {
        arguments.first.push_back(keys.at(i));
        arguments.second.push_back(values.at(i));
    }
    if(devMutex->tryLock(1000)) {
        auto dev = deviceFactory->findDeviceByUnicIdent(devId);
        if(dev != nullptr) {
            auto devComman = dev->second->getCommandCustom(operation, arguments);
            if(!devComman.empty()) {
                deviceCollector->addCommand(devComman);
            }
            devMutex->unlock();
        }
        res = true;
    }
    return res;
}

//********************************************/
// its for imediately exect command
//********************************************/
QStringList DeviceController::exeCommadToDev(QString devId, QString operation, QStringList keys, QStringList values) {
    QList<CommandController::sCommandData> command;
    QPair<QStringList,QStringList> arguments;
    bool res = false;
    for(int i=0; i<keys.size(); i++) {
        arguments.first.push_back(keys.at(i));
        arguments.second.push_back(values.at(i));
    }
    if(devMutex->tryLock(1000)) {
        auto dev = deviceFactory->findDeviceByUnicIdent(devId);
        if(dev != nullptr) {
            auto devComman = dev->second->getCommandCustom(operation, arguments);
            if(!devComman.empty()) {
                deviceCollector->addCommand(devComman);
            }
            devMutex->unlock();
        }
        res = true;
    }
    return res;
}

void DeviceController::setDeviceReInitByIndex(int index) {
    deviceFactory->findDeviceByIndex(index)->second->setState(DeviceAbstract::STATE_DISCONNECTED);
}
