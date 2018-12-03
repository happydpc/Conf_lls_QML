#include "peripherals.h"

Peripherals::Peripherals(QObject *parent) : QObject(parent) {
    this->connFactory = std::make_shared<ConnectionFactory>();
    this->connComposition = std::make_shared<ConnectionComposition>();
    this->updateStatusTimer = std::make_shared<QTimer>();
    this->updateStatusTimer->start(100);

    connect(this->updateStatusTimer.get(), &QTimer::timeout, [&]() {

    });
}

QStringList Peripherals::getAvailableIo(const QString typeIoName) const {
    return connFactory->getAvailableName(typeIoName);
}

QPair<QStringList, QStringList> Peripherals::getIoProperty(int ioIndex) const {
//    connComposition->getDevIsConnected()
//    QPair<QStringList, QStringList>res;
}

bool Peripherals::addIo(const QString typeIoName,
                        const QString ioName,
                        const QStringList keyParam,
                        const QStringList valueParam) {
    return connComposition->addIo(connFactory->createConnection(typeIoName, ioName, QPair<QStringList,QStringList>(keyParam, valueParam)));
}

void Peripherals::removeIo(int ioIndex) {
    connComposition->removeIo(ioIndex);
}

bool Peripherals::addDev(int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam) {
    bool res = false;
    std::shared_ptr<DevicesFactory> devFactory = std::make_shared<DevicesFactory>();
    auto dev = devFactory->newDevice(devTypeName, keyParam, valueParam, nullptr);
    if(dev != nullptr) {
        connComposition->addDev(ioIndex, dev);
//        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
//        emit addDeviceSuccesfull(interfaceTree->getIoIndex(),
//                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getIoIndex()),
//                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first,
//                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second);
    } else {
//        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
//        emit addDeviceFail(devTypeName, "Не получилось добавить одно или более устройств\nВозможные причины:\n 1) такой адрес уже используется\n 2) устройство отличается от типа уже добавленных устройств");
    }
    return res;
}

void Peripherals::removeDev(int ioIndex, int devIndex) {

}

QString Peripherals::getDevType(int ioIndex, int devIndex) const {

}

QPair<QString, QString> Peripherals::getDevProperty(int ioIndex, int devIndex) const {

}

bool Peripherals::devExecCommand(int ioIndex, int devIndex,
                                 QString comandType, QStringList keys, QStringList params) {
    bool res = false;
//    DeviceController *p_dev_controller = connFactory->getDeviceController(ioName);
//    if(p_dev_controller != nullptr) {
//        res = p_dev_controller->sendCommadToDev(commandType, keys, params);
//    }
    return res;
}

void Peripherals::indexDevIsChanged(int ioIndex, int devIndex) {

}

void Peripherals::indexIoIsChanged(int ioIndex, int devIndex) {

}

//void Controller::ioTreeChanged(int ioIndex, int devIndex, ConnectionFactory::E_ConnectionUpdateType changeType) {
//    switch(changeType) {
//    case ConnectionFactory::Type_Update_ChangedIndex:
//    case ConnectionFactory::Type_Update_Add:
//    case ConnectionFactory::Type_Update_Removed:
//        break;
//    }
//    //deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, interfaceTree->getDevIndex());
////    if(connFactory->getCountConnection() >0) {
////        IoAbstract *p_interface = nullptr;
////        interfaceTree->setIoStatus(ioIndex, connFactory->getInterace(ioIndex)->isOpen());
////        p_interface = connFactory->getInterace(interfaceTree->getIoIndex());
////        if(p_interface != nullptr) {
////            emit interfaceReadyProperties(p_interface->getType(),
////                                          interfaceTree->getIoIndex(),
////                                          p_interface->getInterfaceProperty().first,
////                                          p_interface->getInterfaceProperty().second);
////        }
////    }
////    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
//}


//void Controller::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
////    switch(type) {
////    case DevicesFactory::Type_Update_ChangeStatus:
////        if(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount() >= indexDev) {
////            interfaceTree->setDevStatus(indexDev, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceStatusByIndex(indexDev));
////        }
////        break;
////    case DevicesFactory::Type_Update_RamakeAfterChangeInterface: break;
////    case DevicesFactory::Type_Update_Removed: break;
////    case DevicesFactory::Type_Update_Added: break;
////    case DevicesFactory::Type_Update_PasswordIncorrect:
////        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
////        break;
////    case DevicesFactory::Type_Update_TypeIncorrect:
////        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
////        break;
////    }
//}

//void Controller::disconnectToDevSignals() {
//////    try {
//////        int countConn = connFactory->getCountConnection();
//////        for(int i=0; i<countConn; i++) {
//////            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(i);
//////            if(p_dev_factory != nullptr) {
//////                disconnect(p_dev_factory, &DevicesFactory::deviceConnectedSignal, this, &Controller::deviceConnected);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceDisconnectedSignal, this, &Controller::deviceDisconnected);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceReadyCurrentDataSignal, this, &Controller::deviceReadyCurrentData);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceReadyInitSignal, this, &Controller::deviceReadyInit);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceReadyPropertiesSignal, this, &Controller::deviceReadyProperties);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceUpdateTree, this, &Controller::deviceTreeChanged);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceReadyCustomCommand, this, &Controller::deviceReadyCustomCommand);
//////                disconnect(p_dev_factory, &DevicesFactory::deviceReadyLog, this, &Controller::deviceLogMessage);
//////            }
//////        }
//////    }catch(...) { // TODO:---
//////    }
//}

//void Controller::connectToDevSignals() {
//////    try {
//////        if(connFactory->getCountConnection() > 0) {
//////            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
//////            if(p_dev_factory != nullptr) {
//////                connect(p_dev_factory, &DevicesFactory::deviceConnectedSignal, this,  &Controller::deviceConnected);
//////                connect(p_dev_factory, &DevicesFactory::deviceDisconnectedSignal, this, &Controller::deviceDisconnected);
//////                connect(p_dev_factory, &DevicesFactory::deviceReadyCurrentDataSignal, this, &Controller::deviceReadyCurrentData);
//////                connect(p_dev_factory, &DevicesFactory::deviceReadyInitSignal, this, &Controller::deviceReadyInit);
//////                connect(p_dev_factory, &DevicesFactory::deviceReadyPropertiesSignal, this, &Controller::deviceReadyProperties);
//////                connect(p_dev_factory, &DevicesFactory::deviceUpdateTree, this, &Controller::deviceTreeChanged);
//////                connect(p_dev_factory, &DevicesFactory::deviceReadyCustomCommand, this, &Controller::deviceReadyCustomCommand);
//////                connect(p_dev_factory, &DevicesFactory::deviceReadyLog, this, &Controller::deviceLogMessage);
//////            }
//////        }
//////    } catch(...) {} // TODO:---
//}

//void Controller::setChangedIndexDevice(int interfaceIndex, int devIndex) {
////    disconnectToDevSignals();
////    connectToDevSignals();
////    QStringList keys;
////    QStringList values;
////    keys << "devId";
////    values << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceByIndex(interfaceIndex)->first;
////    if(connFactory->getDeviceController(interfaceTree->getIoIndex())->sendCommadToDev("update device", keys, values)) {
////        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
////        emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), getDeviceFactoryByIndex(interfaceIndex)->getDeviceName(devIndex));
////    }
//}

//void Controller::setChangedIndexInteface(int interfaceIndex) {
////    disconnectToDevSignals();
////    interfaceTreeChanged(interfaceIndex, ConnectionFactory::Type_Update_ChangedIndex);
////    connectToDevSignals(); // get interface property
////    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
////    emit interfaceSetActiveProperty(interfaceTree->getIoIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType());
//}


//DeviceAbstract* Controller::getCurrentDeviceToAbstract() {
//    DeviceAbstract * p_devfact = nullptr;
//    try {
//        p_devfact = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
//    }
//    catch(...) { // TODO:---
//    }
//    return p_devfact;
//}

//DevicesFactory* Controller::getDeviceFactoryByIndex(int indexIterface) {
//    try {
//        return connFactory->getDeviceController(indexIterface)->getDeviceFactory();
//    } catch(...) {} // TODO:---
//}

//void Controller::deviceReadyCustomCommand(int devIndex, QString devTypeName, QStringList devKey, QStringList devValue, CommandController::sCommandData command) {
//    DevicesFactory *pDevFactory = nullptr;
//    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
//    if(pDevFactory != nullptr) {
//        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
//        emit devCustomCommandExecuted(devTypeName, interfaceTree->getIoIndex(), devIndex, devKey, devValue);
//    }
//}
