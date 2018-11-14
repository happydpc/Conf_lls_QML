#include "viewController.h"
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QFile>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018_Data.h"

ViewController::ViewController(Model *pInterfaceModel, QObject *parent) : QObject(parent) {
    this->softwareUpdater = new Updater();
    this->connFactory = std::make_shared<ConnectionFactory>();
    this->interfaceTree = pInterfaceModel;
    this->sessionSecurity = new SessionSecurity();

    connect(softwareUpdater, SIGNAL(needUpdate(QString)), this, SLOT(updateVersion(QString)));
    this->updateIoStatusTimer = std::make_shared<QTimer>();
    connect(updateIoStatusTimer.get(), &QTimer::timeout, [=](){
        for(int ioCounter=0; ioCounter<connFactory->getCountConnection(); ioCounter++) {
            interfacesAbstract *p_abst_interface = connFactory->getInterace(ioCounter);
            if(p_abst_interface != nullptr) {
                interfaceTree->setIoStatus(ioCounter, p_abst_interface->isOpen());
            }
        }
    });
    updateIoStatusTimer->start(500);

    connect(interfaceTree, SIGNAL(currentIndexIsChangedInteface(int)), this, SLOT(setChangedIndexInteface(int)));
    connect(connFactory.get(), SIGNAL(updateTree(int,ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(int,ConnectionFactory::E_ConnectionUpdateType)));

    QTimer * testTimer = new QTimer();
    connect(testTimer, &QTimer::timeout, this, [=]() {
        if(addConnection("serial", "COM8", QStringList("baudrate"), QStringList("115200"))) {
            addDeviceToConnection("COM8", "Nozzle Rev 0.0", QStringList("id"), QStringList("1"));
        }
        testTimer->stop();
    });
    testTimer->start(1000);

    //    QTimer::singleShot(60000, Qt::CoarseTimer, [&] {
    //        checkUpdateVersionSoftware();
    //    });
}

ViewController::~ViewController() {
    deviceController.reset();
    connFactory.reset();
    updateIoStatusTimer.reset();
    delete softwareUpdater;
    delete interfaceTree;
    delete sessionSecurity;
}

QString ViewController::getTypeLogo() {
    QString ret;
#ifdef PROGRESS
    ret = "progress";
#endif
#ifdef GLOSSAV
    ret = "gs";
#endif
    return ret;
}

void ViewController::checkUpdateVersionSoftware() {
    softwareUpdater->checkNewUpdate();
}

void ViewController::updateVersion(QString downloadUrl) {
    emit isAvailableNewVersion(downloadUrl);
}

void ViewController::resetSession() {
    disconnect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
    disconnectToDevSignals();
    for(int devCout=0;devCout<connFactory->getCountConnection(); devCout++) {
        getDeviceFactoryByIndex(devCout)->removeDeviceAll();
    }
    connFactory->removeAll();
    interfaceTree->removeAll();
    connectToDevSignals();
    connect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
    emit interfaceAndDeviceListIsEmpty();
    emit clearAllFrontEndItems();
}

bool ViewController::removeSessionByName(QString sessionName) {
    return sessionSecurity->removeSession(sessionName);
}

QStringList ViewController::getListSession() {
    return sessionSecurity->getAvailableSessions();
}

bool ViewController::loadSession(QString sessionName) {
    Session t_load_session = sessionSecurity->getSessionByName(sessionName);
    if(t_load_session.getIsValid()) {
        for(auto itInteface:t_load_session.getInterfaces()) {
            if(addConnection(itInteface.typeName, itInteface.name, itInteface.propKey, itInteface.propValue)) {
                for(auto itDevice:itInteface.devices) {
                    addDeviceToConnection(itInteface.name, itDevice.typeName, itDevice.propKey, itDevice.propValue);
                }
                emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                                getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
            }
        }
    }
    return t_load_session.getIsValid();
}

QString ViewController::saveCurrentSession() {
    Session session;
    Session::sDevices t_session_dev;
    Session::sInterface t_session_io;
    int connAll = connFactory->getCountConnection();
    session.setSessionName("Сеанс_" + QDateTime::currentDateTimeUtc().toString("yyyy/M/d/hh:mm:ss:z"));
    for(int ioCounter=0; ioCounter<connAll; ioCounter++) {
        DevicesFactory *p_dev_factory = nullptr;
        // interfaces
        t_session_io.name = connFactory->getInterace(ioCounter)->getInterfaceName();
        t_session_io.propKey = connFactory->getInterace(ioCounter)->getInterfaceProperty().first;
        t_session_io.propValue = connFactory->getInterace(ioCounter)->getInterfaceProperty().second;
        t_session_io.typeName= connFactory->getInterace(ioCounter)->getType();
        session.addInterface(t_session_io);
        // devices
        p_dev_factory = connFactory->getDeviceController(ioCounter)->getDeviceFactory();
        if(p_dev_factory != nullptr) {
            int devAll = p_dev_factory->getDeviceCount();
            for(int devCounter=0; devCounter<devAll; devCounter++) {
                t_session_dev.propKey.clear();
                t_session_dev.propValue.clear();
                t_session_dev.typeName = p_dev_factory->getDeviceName(devCounter);
                t_session_dev.propKey = p_dev_factory->getDevicePropertyByIndex(devCounter).first;
                t_session_dev.propValue = p_dev_factory->getDevicePropertyByIndex(devCounter).second;
                session.addDevice(t_session_dev);
            }
        }
    }
    QString resNameSession = sessionSecurity->saveSession(session);
    return resNameSession;
}

QString ViewController::saveCurrentSessionAs(QString sessionName) {
    Session session;
    Session::sDevices t_session_dev;
    Session::sInterface t_session_io;
    int connAll = connFactory->getCountConnection();
    session.setSessionName(QString("%1_%2").arg(sessionName).arg(QDateTime::currentDateTimeUtc().toString("yyyy/M/d/hh:mm:ss:z")));
    for(int ioCounter=0; ioCounter<connAll; ioCounter++) {
        DevicesFactory *p_dev_factory = nullptr;
        // interfaces
        t_session_io.name = connFactory->getInterace(ioCounter)->getInterfaceName();
        t_session_io.propKey = connFactory->getInterace(ioCounter)->getInterfaceProperty().first;
        t_session_io.propValue = connFactory->getInterace(ioCounter)->getInterfaceProperty().second;
        t_session_io.typeName= connFactory->getInterace(ioCounter)->getType();
        session.addInterface(t_session_io);
        // devices
        p_dev_factory = connFactory->getDeviceController(ioCounter)->getDeviceFactory();
        if(p_dev_factory != nullptr) {
            int devAll = p_dev_factory->getDeviceCount();
            for(int devCounter=0; devCounter<devAll; devCounter++) {
                t_session_dev.propKey.clear();
                t_session_dev.propValue.clear();
                t_session_dev.typeName = p_dev_factory->getDeviceName(devCounter);
                t_session_dev.propKey = p_dev_factory->getDevicePropertyByIndex(devCounter).first;
                t_session_dev.propValue = p_dev_factory->getDevicePropertyByIndex(devCounter).second;
                session.addDevice(t_session_dev);
            }
        }
    }
    QString resNameSession = sessionSecurity->saveSession(session);
    return resNameSession;
}

QStringList ViewController::getInterfaceAvailableToAdd(QString typeName) {
    QStringList res;
    res = connFactory->getAvailableName(typeName);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(),
                             interfaceTree->getDevIndex(), 0,
                             QString("Получение списка интерфейсов [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    return res;
}

bool ViewController::addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam) {
    bool res = connFactory->addConnection(typeName, name, QPair<QStringList,QStringList>(keyParam, valueParam));
    if(res) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 0, QString("Добавление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        interfacesAbstract *p_interface = nullptr;
        p_interface = connFactory->getInterace(interfaceTree->getIoIndex());
        if(p_interface != nullptr) {
            emit addInterfaceSuccesfull(p_interface->getType(),
                                        p_interface->getInterfaceProperty().first,
                                        p_interface->getInterfaceProperty().second);
            emit interfaceSetActiveProperty((connFactory->getCountConnection()) ? (connFactory->getCountConnection()-1) : (connFactory->getCountConnection()),
                                            connFactory->getInterace((connFactory->getCountConnection()>=1) ? (connFactory->getCountConnection()-1) : (connFactory->getCountConnection()))->getType());
            interfaceTree->addConnection(name);
        }
    } else {
        emit addConnectionFail(name);
    }
    return res;
}

void ViewController::removeActiveInterface() {
    int indexRemove = interfaceTree->getIoIndex();
    interfaceTree->removeConnection(indexRemove);
    connFactory->getDeviceController(indexRemove)->resetAll();
    connFactory->removeConnection(indexRemove);
    emit deleteInterfaceSuccesfull(indexRemove);
    if(getInterfaceCount() == 0) {
        emit interfaceAndDeviceListIsEmpty();
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::removeActiveDevice() {
    int indexRemove = interfaceTree->getDevIndex();
    interfaceTree->removeDeviceToConnection(interfaceTree->getIoIndex(), indexRemove);
    QString devId = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceByIndex(indexRemove)->second->getUniqId();
    connFactory->getDeviceController(indexRemove)->removeDevice(devId);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit deleteDeviceSuccesfull(interfaceTree->getIoIndex(), indexRemove);
    if(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount() == 0) {
        emit interfaceSetActiveProperty(interfaceTree->getIoIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType());
    } else{
        emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    }
}

bool ViewController::addDeviceToConnection(QString ioName, QString devTypeName, QStringList keyParam, QStringList valueParam) {
    bool res = false;
    auto devController = connFactory->getDeviceController(interfaceTree->getIoIndex());
    res = devController->addDevice(devTypeName, keyParam, valueParam);
    if(res) { // change current device index
        interfaceTree->addDeviceToConnection(getCurrentInterfaceName(), "init_device");
        interfaceTree->changeDeviceHeader(getCurrentInterfaceName(), "init_device",
                                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeader(interfaceTree->getDevIndex()));
        interfaceTree->changeDeviceName(getCurrentInterfaceName(), "init_device",
                                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceNameWithId(interfaceTree->getDevIndex()));
        connect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit addDeviceSuccesfull(interfaceTree->getIoIndex(),
                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getIoIndex()),
                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first,
                                 getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second);
    } else {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit addDeviceFail(devTypeName, "Не получилось добавить одно или более устройств\nВозможные причины:\n 1) такой адрес уже используется\n 2) устройство отличается от типа уже добавленных устройств");
    }
    return res;
}

QStringList ViewController::getDeviceAvailableType() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getAvailableDeviceTypes();
}

QString ViewController::getCurrentInterfaceName() {
    return connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
}

int ViewController::getInterfaceCount() {
    return connFactory->getCountConnection();
}

DevicesFactory* ViewController::getDeviceFactoryByIndex(int indexIterface) {
    try {
        return connFactory->getDeviceController(indexIterface)->getDeviceFactory();
    } catch(...) {} // TODO:---
}

bool ViewController::setCurrentDevCustomCommand(QString typeCommand, QStringList keys, QStringList values) {
    bool res = false;
    // сперва проверка на команды
    // которые можно выполнить сранужи
    DeviceController *p_dev_controller = connFactory->getDeviceController(interfaceTree->getIoIndex());
    if(p_dev_controller != nullptr) {
        keys << "devId";
        values << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(interfaceTree->getDevIndex());
        res = p_dev_controller->sendCommadToDev(typeCommand, keys, values);
    }
    return res;
}

DeviceAbstract* ViewController::getCurrentDeviceToAbstract() {
    DeviceAbstract * p_devfact = nullptr;
    try {
        p_devfact = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
    }
    catch(...) { // TODO:---
    }
    return p_devfact;
}

//************************************************************************/
//**                        SECURITY, PROPERTYES                        **/
//************************************************************************/
void ViewController::deviceConnected(QString devType, QString uniqNameId) {
        emit devConnected(interfaceTree->getIoIndex(),
                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Устройста подключено[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceDisconnected(QString devType, QString uniqNameId) {
        emit devDisconnected(interfaceTree->getIoIndex(),
                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                             devType);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Устройство потеряно [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceReadyCurrentData(QString devType, QString uniqNameId) {
        emit devReady(interfaceTree->getIoIndex(),
                      interfaceTree->getDevIndex(),
                      connFactory->getInterace(interfaceTree->getIoIndex())->getType());
        emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                  interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceReadyProperties(QString devType, QString uniqNameId) {
    emit devReadyProperties(devType, interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first,
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, QString("Получение информации с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceReadyInit(QString devType, QString uniqNameId) {}

void ViewController::interfaceTreeChanged(int ioIndex, ConnectionFactory::E_ConnectionUpdateType type) {
    switch(type) {
    case ConnectionFactory::Type_Update_ChangedIndex:
    case ConnectionFactory::Type_Update_Add:
    case ConnectionFactory::Type_Update_Removed:
        break;
    }
    deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, interfaceTree->getDevIndex());
    if(connFactory->getCountConnection() >0) {
        interfacesAbstract *p_interface = nullptr;
        interfaceTree->setIoStatus(ioIndex, connFactory->getInterace(ioIndex)->isOpen());
        p_interface = connFactory->getInterace(interfaceTree->getIoIndex());
        if(p_interface != nullptr) {
            emit interfaceReadyProperties(p_interface->getType(),
                                          interfaceTree->getIoIndex(),
                                          p_interface->getInterfaceProperty().first,
                                          p_interface->getInterfaceProperty().second);
        }
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceLogMessage(int indexDev, QStringList message) {
    while(!message.empty()) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, message.first());
        message.pop_front();
    }
}

void ViewController::deviceReadyCustomCommand(int devIndex, QString devTypeName, QStringList devKey, QStringList devValue, CommandController::sCommandData command) {
    DevicesFactory *pDevFactory = nullptr;
    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
    if(pDevFactory != nullptr) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit devCustomCommandExecuted(devTypeName, interfaceTree->getIoIndex(), devIndex, devKey, devValue);
    }
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        if(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount() >= indexDev) {
            interfaceTree->setDevStatus(indexDev, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceStatusByIndex(indexDev));
        }
        break;
    case DevicesFactory::Type_Update_RamakeAfterChangeInterface: break;
    case DevicesFactory::Type_Update_Removed: break;
    case DevicesFactory::Type_Update_Added: break;
    case DevicesFactory::Type_Update_PasswordIncorrect:
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    case DevicesFactory::Type_Update_TypeIncorrect:
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    }
}

void ViewController::disconnectToDevSignals() {
    try {
        int countConn = connFactory->getCountConnection();
        for(int i=0; i<countConn; i++) {
            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(i);
            if(p_dev_factory != nullptr) {
                disconnect(p_dev_factory, &DevicesFactory::deviceConnectedSignal, this, &ViewController::deviceConnected);
                disconnect(p_dev_factory, &DevicesFactory::deviceDisconnectedSignal, this, &ViewController::deviceDisconnected);
                disconnect(p_dev_factory, &DevicesFactory::deviceReadyCurrentDataSignal, this, &ViewController::deviceReadyCurrentData);
                disconnect(p_dev_factory, &DevicesFactory::deviceReadyInitSignal, this, &ViewController::deviceReadyInit);
                disconnect(p_dev_factory, &DevicesFactory::deviceReadyPropertiesSignal, this, &ViewController::deviceReadyProperties);
                disconnect(p_dev_factory, &DevicesFactory::deviceUpdateTree, this, &ViewController::deviceTreeChanged);
                disconnect(p_dev_factory, &DevicesFactory::deviceReadyCustomCommand, this, &ViewController::deviceReadyCustomCommand);
                disconnect(p_dev_factory, &DevicesFactory::deviceReadyLog, this, &ViewController::deviceLogMessage);
            }
        }
    }catch(...) { // TODO:---
    }
}

void ViewController::connectToDevSignals() {
    try {
        if(connFactory->getCountConnection() > 0) {
            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
            if(p_dev_factory != nullptr) {
                connect(p_dev_factory, &DevicesFactory::deviceConnectedSignal, this,  &ViewController::deviceConnected);
                connect(p_dev_factory, &DevicesFactory::deviceDisconnectedSignal, this, &ViewController::deviceDisconnected);
                connect(p_dev_factory, &DevicesFactory::deviceReadyCurrentDataSignal, this, &ViewController::deviceReadyCurrentData);
                connect(p_dev_factory, &DevicesFactory::deviceReadyInitSignal, this, &ViewController::deviceReadyInit);
                connect(p_dev_factory, &DevicesFactory::deviceReadyPropertiesSignal, this, &ViewController::deviceReadyProperties);
                connect(p_dev_factory, &DevicesFactory::deviceUpdateTree, this, &ViewController::deviceTreeChanged);
                connect(p_dev_factory, &DevicesFactory::deviceReadyCustomCommand, this, &ViewController::deviceReadyCustomCommand);
                connect(p_dev_factory, &DevicesFactory::deviceReadyLog, this, &ViewController::deviceLogMessage);
            }
        }
    } catch(...) {} // TODO:---
}

void ViewController::setChangedIndexDevice(int interfaceIndex, int devIndex) {
    disconnectToDevSignals();
    connectToDevSignals();
    QStringList keys;
    QStringList values;
    keys << "devId";
    values << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceByIndex(interfaceIndex)->first;
    if(connFactory->getDeviceController(interfaceTree->getIoIndex())->sendCommadToDev("update device", keys, values)) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), getDeviceFactoryByIndex(interfaceIndex)->getDeviceName(devIndex));
    }
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    disconnectToDevSignals();
    interfaceTreeChanged(interfaceIndex, ConnectionFactory::Type_Update_ChangedIndex);
    connectToDevSignals(); // get interface property
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit interfaceSetActiveProperty(interfaceTree->getIoIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType());
}


////setTableFromFrontEnd
//void ViewController::setTableFromFrontEnd(QString uniqDevName, QStringList valuesLiters, QStringList valuesFuelLevel) {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        pService->placeTableFromFrontEnd(uniqDevName, valuesLiters, valuesFuelLevel);
//    }
//}

//sendReqWriteTarrirAllDev
//void ViewController::sendReqWriteTarrirAllDev() {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        for(auto i:pService->requestWriteTableToAllDevice()) {
//            // извлекаем данные из таблциц
//            QPair<QStringList,QStringList> table;
//            table = pService->getTableAtDeviceToPair(i);
//            // отправляем всем dev из списка команду на запись таблиц
//            //            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->deviceCollector->sendCustomCommadToDev(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i),
//            //                                                                                        "set current dev tar table",
//            //                                                                                        table.first, table.second);
//        }
//    }
//}

//int ViewController::getTarMaxCountStep() {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        if(pService !=nullptr) {
//            return pService->getMaxCountStep();
//        }
//    }
//    return 0;
//}

//void ViewController::sendReqExportTarrirAllDevToCsv(QString pathFile) {
//    QStringList exportList;
//    QString str;
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        int devAll = pService->getDeviceCount();
//        // id[devType], объем, уровень топлива
//        for(int devCounter=0; devCounter<devAll; devCounter++) {
//            QStringList litersList;
//            QStringList fuelLevelList;
//            // получаем стоблец с liters и fuelLevel
//            QPair<QStringList,QStringList> tableData;
//            tableData = pService->getTableAtDeviceToPair(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(devCounter));
//            for(int tableCounter=0; tableCounter<tableData.first.size(); tableCounter++) {
//                // lites
//                litersList << tableData.first.at(tableCounter);
//                // fuelLevel
//                fuelLevelList << tableData.second.at(tableCounter);
//            }
//            str.clear();
//            str.push_back("\"" + QString("ID/Тип") + "\"" + ",");
//            str.push_back("\"" + QString("Объем") + "\"" + ",");
//            str.push_back("\"" + QString("Уровень") + "\"");
//            exportList.push_back(str);
//            for(int makeCounter=0; makeCounter<litersList.size(); makeCounter++) {
//                str.clear();
//                str.push_back("\"" + QString("ID%1[%2]").arg(pService->getDeviceProperty(devCounter).at(1)).arg(pService->getDeviceProperty(devCounter).at(0)) + "\"" + ",");
//                str.push_back("\"" + ((litersList.size() >= makeCounter) ? (litersList.at(makeCounter) + "\"" + ",") : QString("Нет данных")));
//                str.push_back("\"" + ((fuelLevelList.size() >= makeCounter) ? (fuelLevelList.at(makeCounter) + "\"") : QString("Нет данных")));
//                exportList.push_back(str);
//            }
//        }
//        if(!exportList.empty()) {
//            if(pathFile.size() > 0) {
//                if(!pathFile.contains(".csv")) {
//                    pathFile.push_back(".csv");
//                }
//                if(pathFile.count(':') > 1) { // windows
//                    pathFile.remove("file:///");
//                } else {
//                    pathFile.remove("file://"); // unix
//                }
//                QFile file(pathFile);
//                if (file.open(QFile::WriteOnly | QFile::Text)) {
//                    QTextStream s(&file);
//                    for (int counterExport=0; counterExport<exportList.size(); ++counterExport) {
//                        s << exportList.at(counterExport) << '\n';
//                    }
//                }
//                file.close();
//            }
//        }
//    }
//}

//QStringList ViewController::getAvailableDevTarrirAdd_DevType() {
//    //    QStringList resList;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//    //        for(int i=0; i<devCount; i++) {
//    //            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(i);
//    //        }
//    //    }
//    //    return resList;
//}
//QStringList ViewController::getAvailableDevTarrirAdd_DevId() {
//    //    QStringList resList;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//    //        for(int i=0; i<devCount; i++) {
//    //            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(i);
//    //        }
//    //    }
//    //    return resList;
//}
//QStringList ViewController::getAvailableDevTarrirAdd_DevSerialNumber() {
//    //    QStringList resList;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//    //        for(int i=0; i<devCount; i++) {
//    //            QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).first;
//    //            for(int i2 =0; i2<keyList.size(); i2++) {
//    //                if(keyList.at(i2) == QString("serialNum")) {                                                                                 // TOOD:!!!!!
//    //                    resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).second.at(0);
//    //                }
//    //            }
//    //        }
//    //    }
//    //    return resList;
//}

//QStringList ViewController::getTarCurrentDeviceData(int index) {
//    //    QStringList res;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //            if(pService != nullptr) {
//    //                res = pService->getCurrentDataDevice(index);
//    //            }
//    //        }
//    //    }
//    //    return res;
//}

//QList<int> ViewController::getTarCurrentDeviceChartData(int index) {
//    //    QList<int> res;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //            if(pService != nullptr) {
//    //                res = pService->getCurrentChartDataDevice(index);
//    //            }
//    //        }
//    //    }
//    //    return res;
//}

//int ViewController::getStayedDevTarrirCount() {
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //            if(pService != nullptr) {
//    //                return pService->getDeviceCount();
//    //            }
//    //        }
//    //    }
//    //    return 0;
//}

//QStringList ViewController::getStayedDevTarrir_DevProperty(QString propertyName) {
//    //    QStringList res;
//    //    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//    //        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //            if(pService != nullptr) {
//    //                for(int i=0; i<pService->getDeviceCount(); i++) {
//    //                    if(propertyName.toLower() == "type") {
//    //                        res << pService->getDeviceProperty(i).at(0); // type
//    //                    }
//    //                    if(propertyName.toLower() == "id") {
//    //                        res << pService->getDeviceProperty(i).at(1); // id
//    //                    }
//    //                    if(propertyName.toLower() == "sn") {
//    //                        res << pService->getDeviceProperty(i).at(2); // serialNum
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//    //    return res;
//}


//bool ViewController::addTarrirDev(QString devTypeName, QString devId) {
//    //    bool res = false;
//    //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        res = pService->addDevice(devTypeName, devId,"-----");
//    //    }
//    //    return res;
//}

//void ViewController::removeTarrirDev(QString devTypeName, QString devId) {
//    //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        if(pService != nullptr) {
//    //            pService->removeDevice(devTypeName, devId);
//    //        }
//    //    }
//}

//void ViewController::setLastRealTimeValuesToStep(int indexStep) {
//    //#if USE_DB_VIEWCONTROLLER == 1
//    //    qDebug() << "ViewController: - setLastRealTimeValuesToStep";
//    //#endif
//    ////    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        //  Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        //  pService->setLastRealTimeValuesToStep(indexStep);
//    ////    }
//    //#if USE_DB_VIEWCONTROLLER == 1
//    //    qDebug() << "ViewController: - setLastRealTimeValuesToStep -OK";
//    //#endif
//}

////1) считать таблицу с добавленных устройств
//// отправляем в контроллер список dev с id
//// указываем что считать таблицу
//// ожидаем ответа по очереди
//// когда последний опрошен, отсылаем результат в qml
//// если ответа небыло, значение выделить красным и вывести message
//void ViewController::sendReqGetTarrirAllDev() {
//    //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        if(pService != nullptr) {
//    //            for(auto i:pService->requestGetTableFromAllDevice()) {      // TODO: плохо, можно взять пустой список и ждать ответа
//    //                if(i.length() > 0) {
//    //                    // отправляем всем dev из списка команду на чтение таблицы
//    //                    DevicesFactory *pdeviceFactory = nullptr;
//    //                    pdeviceFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
//    //                    if(pdeviceFactory != nullptr) {
//    //                        int devIndex = pdeviceFactory->findDeviceIndex(i);
//    //                        if(devIndex >= 0) {
//    //                            pdeviceFactory->deviceCollector->sendCustomCommadToDev(devIndex, "read current dev tar table");
//    //                        } else {
//    //                            qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR find device";
//    //                        }
//    //                    } else {
//    //                        qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR nullprt deviceFactory";
//    //                    }
//    //                }
//    //            }
//    //        }
//    //    }
//}

//QStringList ViewController::getTableAtDevice(int index) {
//    //    QStringList res;
//    //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        if(pService != nullptr) {
//    //            res = pService->getTableAtDevice(index);
//    //        }
//    //    }
//    //    return res;
//}

//int ViewController::getTableCountReady() {
//    //    int res = 0;
//    //    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//    //        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//    //        if(pService != nullptr) {
//    //            res = pService->requestGetTableFromAllDevice().size();
//    //        }
//    //    }
//    //    return res;
//}
