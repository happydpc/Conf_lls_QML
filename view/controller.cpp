#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {
    this->peripherals = std::make_shared<Peripherals>();
    connect(&ioTreeModel, &ModelDevTree::indexIoIsChanged, peripherals.get(), &Peripherals::indexIoIsChanged);
    connect(&ioTreeModel, &ModelDevTree::indexDevIsChanged, peripherals.get(), &Peripherals::indexDevIsChanged);
}

ModelDevTree* Controller::getIoTreeModel() {
    return &ioTreeModel;
}

QStringList Controller::getAvailableIoToAdd(QString typeName) {
    return peripherals->getAvailableIo(typeName);
}

bool Controller::addIo(QString typeIoName, QString ioName, QStringList keys, QStringList params) {
    bool res = false;
    auto handler = peripherals->addIo(typeIoName, ioName, keys, params);
    res = handler.get();
    if(res) {
        peripherals->getCurrentIoName()
        emit addIoSucces(typeIoName, p_interface->getType(),
                                    p_interface->getInterfaceProperty().first,
                                    p_interface->getInterfaceProperty().second);
        emit interfaceSetActiveProperty((connFactory->getCountConnection()) ? (connFactory->getCountConnection()-1) : (connFactory->getCountConnection()),
                                        connFactory->getInterace((connFactory->getCountConnection()>=1) ? (connFactory->getCountConnection()-1) : (connFactory->getCountConnection()))->getType());
        interfaceTree->addConnection(name);
    } else {
        emit addConnectionFail(name);
    }
}

void Controller::removeActiveIo() {
    peripherals->removeIo(peripherals->getCurrentIoName());
}

bool Controller::addDevToIo(QString ioName, QString devTypeName, QStringList keys, QStringList param) {
    auto res = peripherals->addDev(ioName, devTypeName, keys, param);
    if(res.get()) {

    }
}

void Controller::removeActiveDev() {
    peripherals->removeDev(peripherals->getCurrentIoName(), peripherals->getCurrentDevName());
}

QStringList Controller::getDevAvailableType() const {
    return peripherals->getDevType();
}

bool Controller::devExecCommand(const QString ioName, const QString devIdName, const QString commandType,
                                const QStringList keys, const QStringList params) {
    return peripherals->devSendCustomCommand(ioName, devIdName, commandType, keys, params);
}

void Controller::eventFromPeripheral(const int ioIndex, const int devIndex, const QStringList keys, const QStringList param) {
    for(int it=0; it<keys.length(); it++) {
        if(keys.at(it) == "eventType") {
            if(param.at(it) == "deviceCreated") {

            }
            if(param.at(it) == "deviceConnected") {
//                emit devConnected(interfaceTree->getIoIndex(),
//                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
//                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
            }
            if(param.at(it) == "deviceDisconnected") {
//                emit devDisconnected(interfaceTree->getIoIndex(),
                //////                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                //////                             devType);
            }
            if(param.at(it) == "deviceInited") {
                //////        emit devReady(interfaceTree->getIoIndex(),
                //////                      interfaceTree->getDevIndex(),
                //////                      connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            }
            if(param.at(it) == "deviceUpdated") {
                //////        emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                //////                                  interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                //////                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                //////                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
            }
            if(param.at(it) == "deviceMessage") {
                //    while(!message.empty()) {
                //        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, message.first());
                //        message.pop_front();
                //    }
                //////    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Устройста подключено[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            }
            if(param.at(it) == "ioCreated") {

            }
            if(param.at(it) == "ioDisconnected") {

            }
            if(param.at(it) == "ioConnected") {

            }
            if(param.at(it) == "ioConnected") {
                //    while(!message.empty()) {
                //        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, message.first());
                //        message.pop_front();
                //    }
            }
        }
    }
}

QString Controller::getTypeLogo() const {
#ifdef PROGRESS
    return "progress";
#endif
#ifdef GLOSSAV
    return("gs");
#endif
    return QString();
}
