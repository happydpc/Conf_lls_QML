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

#define USE_DB_VIEWCONTROLLER       0

ViewController::ViewController(Model *pInterfaceModel, QObject *parent) : QObject(parent) {
    this->softwareUpdater = new Updater();
    this->connFactory = new ConnectionFactory();
    this->interfaceTree = pInterfaceModel;
    this->sessionSecurity = new SessionSecurity();
    this->updateIoStatusTimer = new QTimer();

    connect(softwareUpdater, SIGNAL(needUpdate(QString)), this, SLOT(updateVersion(QString)));

    updateIoStatusTimer->start(500);
    QObject::connect(updateIoStatusTimer, &QTimer::timeout, [this](){
        for(int ioCounter=0; ioCounter<connFactory->getCountConnection(); ioCounter++) {
            interfaceTree->setIoStatus(ioCounter, connFactory->getInterace(ioCounter)->isOpen());
        }
    });

    connect(interfaceTree, SIGNAL(currentIndexIsChangedInteface(int)), this, SLOT(setChangedIndexInteface(int)));
    connect(connFactory, SIGNAL(updateTree(int,ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(int,ConnectionFactory::E_ConnectionUpdateType)));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        //        addConnection("serial", "ttyUSB0", QStringList("baudrate"), QStringList("19200"));
        //        addDeviceToConnection("PROGRESS TMK24", QStringList("id"), QStringList("3"));
        //        addDeviceToConnection("PROGRESS TMK24", QStringList("id"), QStringList("4"));
    });

    QTimer::singleShot(1000, Qt::CoarseTimer, [&] {
        //        addConnection("serial", "ttyACM0", QStringList("baudrate"), QStringList("115200"));
        //        addDeviceToConnection("Nozzle Rev 0.0", QStringList("id"), QStringList("1"));
    });

    //    QTimer::singleShot(10000, Qt::CoarseTimer, [&] {
    //        checkUpdateVersionSoftware();
    //    });

#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: -create Ok";
#endif
}

ViewController::~ViewController() {
    delete softwareUpdater;
    delete connFactory;
    delete interfaceTree;
    delete sessionSecurity;
    delete updateIoStatusTimer;
}

void ViewController::checkUpdateVersionSoftware() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - checkUpdate";
#endif
    softwareUpdater->checkNewUpdate();
}

void ViewController::updateVersion(QString downloadUrl) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - emit updateSoftReady";
#endif
    emit isAvailableNewVersion(downloadUrl);
}

// TODO: need uniqPtr
QList<ServiceDevicesAbstract*> ViewController::getNewServices() {
    QList<ServiceDevicesAbstract*> res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getNewService";
#endif
    res << new Progress_tmk24Service("PROGRESS TMK24");
    res << new Nozzle_Rev_0_00_Service("Nozzle Rev 0.0");
    return res;
}

void ViewController::resetSession() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - resetSession";
#endif
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
    // очистка всех item на форме
    // иначе надо долго очищать по одному
    emit clearAllFrontEndItems();
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - resetSession -Ok";
#endif
}

bool ViewController::removeSessionByName(QString sessionName) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeSessionByName";
#endif
    return sessionSecurity->removeSession(sessionName);
}

QStringList ViewController::getListSession() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getListSession";
#endif
    return sessionSecurity->getAvailableSessions();
}

bool ViewController::loadSession(QString sessionName) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - loadSession=" << sessionName;
#endif
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
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - loadSession=" << sessionName << "-Ok";
#endif
    return t_load_session.getIsValid();
}

QString ViewController::saveCurrentSession() {
    Session session;
    Session::sDevices t_session_dev;
    Session::sInterface t_session_io;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - saveCurrentSession";
#endif
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
        p_dev_factory = connFactory->getInterace(ioCounter)->getDeviceFactory();
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
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - saveCurrentSession -OK " << resNameSession;
#endif
    return resNameSession;
}

QString ViewController::saveCurrentSessionAs(QString sessionName) {
    Session session;
    Session::sDevices t_session_dev;
    Session::sInterface t_session_io;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - saveCurrentSessinonAs=" << sessionName;
#endif
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
        p_dev_factory = connFactory->getInterace(ioCounter)->getDeviceFactory();
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
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - saveCurrentSessinonAs -OK =" << resNameSession;
#endif
    return resNameSession;
}

void ViewController::closeApplication() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - closeApplication";
#endif
    exit(0);
}

QStringList ViewController::getInterfaceAvailableToAdd(QString typeName) {
    QStringList res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getInterfaceAvailableToAdd=" << typeName;
#endif
    res = connFactory->getAvailableName(typeName);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(),
                             interfaceTree->getDevIndex(), 0,
                             QString("Получение списка интерфейсов [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getInterfaceAvailableToAdd -OK = " << typeName;
#endif
    return res;
}

bool ViewController::addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam) {
    bool res = false;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addConnection=" << typeName << " " << name;
#endif
    if((!name.isEmpty()) && (!name.isEmpty())) {
        res = connFactory->addConnection(typeName, name, QPair<QStringList,QStringList>(keyParam, valueParam));
        if(res) {
            // create finished
            // when add service
            // TODO: the service need and necessery for other action
            serviceList.push_back(getNewServices());
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
            emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 0, QString("Добавление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            // only added to the end
            // when take last count and plus 1
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
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addConnection -OK " << typeName << " " << name;
#endif
    return res;
}

void ViewController::removeActiveInterface() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeActiveInterface";
#endif
    int indexRemove = interfaceTree->getIoIndex();
    serviceList.removeAt(indexRemove);
    interfaceTree->removeConnection(indexRemove);
    getDeviceFactoryByIndex(indexRemove)->removeDeviceAll();
    connFactory->removeConnection(indexRemove);
    emit deleteInterfaceSuccesfull(indexRemove);
    if(getInterfaceCount() == 0) {
        emit interfaceAndDeviceListIsEmpty();
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeActiveInterface -OK";
#endif
}

void ViewController::removeActiveDevice() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeActiveDevice";
#endif
    int indexRemove = interfaceTree->getDevIndex();
    interfaceTree->removeDeviceToConnection(interfaceTree->getIoIndex(), indexRemove);
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->removeDeviceByIndex(indexRemove);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit deleteDeviceSuccesfull(interfaceTree->getIoIndex(), indexRemove);
    if(getDeviceCount() == 0) {
        emit interfaceSetActiveProperty(interfaceTree->getIoIndex(),
                                        connFactory->getInterace(interfaceTree->getIoIndex())->getType());
    } else{
        emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeActiveDevice -OK";
#endif
}

bool ViewController::addDeviceToConnection(QString ioName, QString devTypeName, QStringList keyParam, QStringList valueParam) {
    bool res = false;
    interfacesAbstract *pInterface = nullptr;
    bool serviceIsFinded = false;
    ServiceDevicesAbstract *p_service = nullptr;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addDeviceToConnection = " << ioName << " " << devTypeName ;
#endif
    // get interface
    pInterface = connFactory->getInterace(ioName);
    if(pInterface == nullptr) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - addDeviceToConnection -ERR nullprt " << ioName << " " << devTypeName ;
#endif
        return false;
    }
    for(auto services:serviceList[interfaceTree->getIoIndex()]) {
        if(services->getDeviceType() == devTypeName) {
            serviceIsFinded = true;
            p_service = services; break;
        }
    }
    if(serviceIsFinded) {
        res = pInterface->getDeviceFactory()->addNewDevice(pInterface->getDeviceFactory()->getDeviceType(devTypeName),
                                                           QPair<QStringList,QStringList>(keyParam, valueParam), p_service);
        if(res) {
            // change current device index
            interfaceTree->addDeviceToConnection(getCurrentInterfaceName(), "init_device");
            interfaceTree->changeDeviceHeader(getCurrentInterfaceName(), "init_device",
                                              getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeader(interfaceTree->getDevIndex()));
            interfaceTree->changeDeviceName(getCurrentInterfaceName(), "init_device",
                                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceNameWithId(interfaceTree->getDevIndex()));
            connect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
            // make it device - "not ready"
            // while not read settings
            pInterface->getDeviceFactory()->setDeviceReInitByIndex(interfaceTree->getDevIndex());
            emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            emit addDeviceSuccesfull(interfaceTree->getIoIndex(),
                                     getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceTypeNameByType(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceType(interfaceTree->getDevIndex())),
                                     getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first,
                                     getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second);
        } else {
            emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(), 2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            emit addDeviceFail(devTypeName, "Не получилось добавить одно или более устройств\nВозможные причины:\n 1) такой адрес уже используется\n 2) устройство отличается от типа уже добавленных устройств");
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addDeviceToConnection -OK " << ioName << " " << devTypeName ;
#endif
    return res;
}

bool ViewController::addDeviceToConnection(QString devTypeName, QStringList keyParam, QStringList valueParam) {
    return addDeviceToConnection(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()), devTypeName, keyParam, valueParam);
}

void ViewController::checkDeviceFromConnection(QString devTypeName, QStringList keyParam, QStringList valueParam) { // uniqIdDevice password
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - checkDeviceFromConnection = " << devTypeName ;
#endif
    if(devTypeName == QString(Progress_tmk24::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Progress_Tmk24, keyParam, valueParam);
    }
    if(devTypeName == QString(Progress_tmk4UX::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Progress_tmk4UX, keyParam, valueParam);
    }
    if(devTypeName == QString(Nozzle_Revision_0_00_Oct_2018::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Nozzle_rev_0_00, keyParam, valueParam);
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - checkDeviceFromConnection -OK " << devTypeName ;
#endif
}

QStringList ViewController::getDeviceAvailableType() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getDeviceAvailableType";
#endif
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getAvailableDeviceTypes();
}

QString ViewController::getCurrentInterfaceName() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentInterfaceName";
#endif
    QString name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentInterfaceName -OK " << name;
#endif
    return name;
}

int ViewController::getInterfaceCount() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getInterfaceCount";
#endif
    int count = connFactory->getCountConnection();
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getInterfaceCount -OK " << count;
#endif
    return count;
}

QList<QString> ViewController::getCurrentDevPeriodicDataKey() {
    QList<QString> res;
    QString name;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPeriodicDataKey";
#endif
    name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPeriodicDataKey -OK ";
#endif
    return res;
}

QList<QString> ViewController::getCurrentDevPeriodicDataValue() {
    QList<QString> res;
    QString name;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPeriodicDataValue";
#endif
    name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPeriodicDataValue -OK ";
#endif
    return res;
}

int ViewController::getDeviceCount() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getDeviceCount";
#endif
    int count = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getDeviceCount -OK " << count;
#endif
    return count;
}

QStringList ViewController::getCurrentDevPropertyKey() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPropertyKey";
#endif
    QStringList ret;
    interfacesAbstract *p_interface = nullptr;
    p_interface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()));
    if(p_interface != nullptr) {
        ret = p_interface->getDeviceFactory()->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first;
    } else {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - getCurrentDevPropertyKey -ERR nullprt";
#endif
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPropertyKey -OK ";
#endif
    return ret;
}

QStringList ViewController::getCurrentDevPropertyValue() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPropertyValue";
#endif
    QStringList ret;
    interfacesAbstract *p_interface = nullptr;
    p_interface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()));
    if(p_interface != nullptr) {
        ret = p_interface->getDeviceFactory()->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second;
    } else {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - getCurrentDevPropertyValue -ERR nullprt";
#endif
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevPropertyValue -OK ";
#endif
    return ret;
}

DevicesFactory* ViewController::getDeviceFactoryByIndex(int indexIterface) {
    try {
        return connFactory->getInterace(connFactory->getInteraceNameFromIndex(indexIterface))->getDeviceFactory();
    } catch(...) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - getDeviceFactoryByIndex -ERR " << indexIterface;
#endif
    }
}

bool ViewController::isCurrentDevice(QString uniqNameId) {
    try {
        if(interfaceTree->getIoIndex() < connFactory->getCountConnection()) {
            if(interfaceTree->getDevIndex() < getDeviceCount()) {
                if(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(interfaceTree->getDevIndex()) == uniqNameId) {
                    return true;
                }
            }
        }
    } catch(...) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - isCurrentDevice -ERR " << uniqNameId;
#endif
    }
    return false;
}

bool ViewController::setCurrentDevCustomCommand(QString typeCommand, QStringList keys, QStringList values) {
    bool res = false;
    // сперва проверка на команды
    // которые можно выполнить сранужи
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setCurrentDevCustomCommand =" << typeCommand;
#endif
    if(getDeviceCount() != 0) {
        if(typeCommand == "change device head name") {
            for(auto i=0; i<keys.length(); i++) {
                if(keys[i] == "newHeader") {
                    res = interfaceTree->changeDeviceHeader(getCurrentInterfaceName(),
                                                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceNameWithId(interfaceTree->getDevIndex()), values[i]);
                    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceHeader(interfaceTree->getDevIndex(), values[i]);
#if USE_DB_VIEWCONTROLLER == 1
                    qDebug() << "ViewController: - setCurrentDevCustomCommand -OK =" << res;
#endif
                    return res;
                }
            }
        }
    }
    res = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(),
                                                                                      typeCommand, keys, values);
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setCurrentDevCustomCommand =OK " << res;
#endif
    return res;
}

DeviceAbstract* ViewController::getCurrentDeviceToAbstract() {
    DeviceAbstract * p_devfact = nullptr;
    try {
        p_devfact = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
    }
    catch(...) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - getCurrentDeviceToAbstract -ERR catch";
#endif
    }
    return p_devfact;
}


//************************************************************************/
//**                        SECURITY, PROPERTYES                        **/
//************************************************************************/
void ViewController::deviceConnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceConnected -"<<type;
#endif
    if(isCurrentDevice(uniqNameId)) {
        emit devConnected(interfaceTree->getIoIndex(),
                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, QString("Устройста подключено[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceConnected -OK -"<<type;
#endif
}

void ViewController::deviceDisconnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceDisconnected -" << type << " " << uniqNameId;
#endif
    if(isCurrentDevice(uniqNameId)) {
        emit devDisconnected(interfaceTree->getIoIndex(),
                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceTypeNameByType(type));
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Устройство потеряно [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceDisconnected -OK -"<<type << " " << uniqNameId;
#endif
}

void ViewController::deviceReadyCurrentData(DevicesFactory::E_DeviceType type, QString uniqNameId) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyCurrentData -" << type << " " << uniqNameId;
#endif
    switch(type) {
    case DevicesFactory::Type_Progress_tmk4UX: {
        if(isCurrentDevice(uniqNameId)) {
            emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        }
    }
        break;
    case DevicesFactory::Type_Progress_Tmk24: {
        int devIndex = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId);
        if(isCurrentDevice(uniqNameId)) {
            emit devReady(interfaceTree->getIoIndex(),
                          interfaceTree->getDevIndex(),
                          connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        }
        if(devIndex >= 0) {
            ServiceDevicesAbstract *p_serviceAbstact = nullptr;
            p_serviceAbstact = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(devIndex)->getServiceAbstract();
            if(p_serviceAbstact != nullptr) {
                try {
                    Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(p_serviceAbstact);
                    pService->placeCurrenDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(devIndex));
                    pService->placeCurrentChartDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceChartByIndex(devIndex));
                } catch(...) {
                    qDebug() << "-ERR (catch - Progress_tmk24Service* pService)";
                }
            }
        }
    }
        break;
    case DevicesFactory::Type_Nozzle_rev_0_00: {
        if(isCurrentDevice(uniqNameId)) {
            emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        }
    }
        break;
    case DevicesFactory::Type_Undefined: break;
    }
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyCurrentData -OK" << type << " " << uniqNameId;
#endif
}

void ViewController::deviceCheckReady(DevicesFactory::E_DeviceType devType, QString devUniqNameId, bool result) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceCheckReady -" << devType << " " << devUniqNameId;
#endif
    if(devType == DevicesFactory::Type_Progress_Tmk24) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Progress_tmk24::name), devUniqNameId, "...", result);
    }
    if(devType == DevicesFactory::Type_Progress_tmk4UX) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Progress_tmk4UX::name), devUniqNameId, "...", result);
    }
    if(devType == DevicesFactory::Type_Nozzle_rev_0_00) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Nozzle_Revision_0_00_Oct_2018::name), devUniqNameId, "...", result);
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceCheckReady -OK" << devType << " " << devUniqNameId;
#endif
}

void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyProperties -" << type << " " << uniqNameId;
#endif
    emit devReadyProperties(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()),
                            interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first,
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second);
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, QString("Получение информации с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyProperties -OK" << type << " " << uniqNameId;
#endif
}

void ViewController::deviceReadyInit(DevicesFactory::E_DeviceType type, QString uniqNameId) {}

void ViewController::interfaceTreeChanged(int ioIndex, ConnectionFactory::E_ConnectionUpdateType type) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - interfaceTreeChanged " << ioIndex;
#endif
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
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - interfaceTreeChanged -OK" << ioIndex;
#endif
}

void ViewController::deviceLogMessage(int indexDev, QStringList message) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceLogMessage" << indexDev << " " << message;
#endif
    while(!message.empty()) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),0, message.first());
        message.pop_front();
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceLogMessage -OK" << indexDev << " " << message;
#endif
}

void ViewController::deviceReadyCustomCommand(int indexDev, QString message,
                                              QStringList keyCustomData, QStringList valueCustomData,
                                              CommandController::sCommandData commmandData) {
    DevicesFactory *pDevFactory = nullptr;
    QStringList keys;
    QStringList values;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyCustomCommand " << indexDev << " " << message;
#endif
    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
    if(pDevFactory != nullptr) {
        emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        switch(pDevFactory->getDeviceType(pDevFactory->getDeviceName(indexDev))) {
        case DevicesFactory::Type_Progress_Tmk24: {
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_max) {
                keys << "lls_calibrate_max" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_min) {
                keys << "lls_calibrate_min" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_settings) {
                keys << "lls_read_settings" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_errors) {
                keys << "lls_read_errors" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceErrrors(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceErrrors(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_cal_table) {
                Progress_tmk24Service* pService = nullptr;
                pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                if(pService != nullptr) {
                    pService->placeTableFromDevice(commmandData.deviceIdent, keyCustomData, valueCustomData);
                    if(pService->readTableAllDeviceIsReady()) {
                        //emit devUpdateReadTarTable(pService->getDeviceCount());
                        keys << "lls_read_cal_table" << keyCustomData;
                        values << message.toLower() << valueCustomData;
                        emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                      interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                                      keys, values, commmandData.isNeedAckMessage);
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_write_cal_table) {
                Progress_tmk24Service* pService = nullptr;
                pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                if(pService != nullptr) {
                    pService->placeAckReplyOfWriteTableFromDevice(commmandData.deviceIdent, (message == "Normal" ? (true) : (false)));
                    if(pService->readTableAllDeviceIsReady()) {
                        QStringList resWrite;
                        for(int index=0; index<pService->getDeviceCount(); index++) {
                            resWrite << QString("\nID%1 [%2][SN-%3]   статус - %4").arg(commmandData.deviceIdent)
                                        .arg(pService->getDeviceProperty(index).at(0))
                                        .arg(pService->getDeviceProperty(index).at(2))
                                        .arg(message == QString("Normal") ? QString("Успешно записано") :
                                                                            (message == QString("Data no valid") ?
                                                                                 (QString("Устройство отвергло данные")) :
                                                                                 QString("Нет ответа")));
                        }
                        keys << "lls_write_cal_table" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                        values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                        emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                      interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                                      keys, values, commmandData.isNeedAckMessage);
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_lvl_all) {
                keys << "lls_read_lvl_all" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }

            if(commmandData.devCommand == Progress_tmk24Data::lls_write_settings) {
                keys << "lls_write_settings" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
        }
            break;
            // -- Type_Nozzle_Revision_0_00_Oct_2018
        case DevicesFactory::Type_Nozzle_rev_0_00: {
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_EmptyCommand) {}
            // init
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword) {
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("getPassword"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig) { // settings
                keys << "getAccelConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig) { // settings
                keys << "getNetworkConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand) {}
            // current data
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData) { // current data
                keys << "getAccelData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData) { // current data
                keys << "getNetworkData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData) { // current data
                keys << "getOtherData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData) { // current data
                keys << "getCardProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData) { // current data
                keys << "getBatteryProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword) { // reply exec
                keys << "E_ConsoleCommandType_setPassword" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("setNetworkPassword"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig) { // reply exec
                keys << "E_ConsoleCommandType_setAccelConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("setAccelConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint) { // reply exec
                keys << "E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("setAccelUseCurrentValuesAsNullPoint"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig) { // reply exec
                keys << "E_ConsoleCommandType_setNetworkConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("setNetworkConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum) { // reply exec
                keys << "E_ConsoleCommandType_setBatteryNewAccum" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                              QStringList("setBatteryNewAccum"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
        }
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceReadyCustomCommand -OK" << indexDev << " " << message;
#endif
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceTreeChanged " << indexDev;
#endif
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        if(getDeviceCount() >= indexDev) {
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
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - deviceTreeChanged -OK" << indexDev;
#endif
}

void ViewController::disconnectToDevSignals() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - disconnectToDevSignals";
#endif
    try {
        int countConn = connFactory->getCountConnection();
        for(int i=0; i<countConn; i++) {
            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(i);
            if(p_dev_factory != nullptr) {
                disconnect(p_dev_factory, SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
                disconnect(p_dev_factory, SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
                disconnect(p_dev_factory, SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
                disconnect(p_dev_factory, SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
                disconnect(p_dev_factory, SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
                disconnect(p_dev_factory,
                           SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                           this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
                disconnect(p_dev_factory, SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)),
                           this, SLOT(deviceReadyCustomCommand(int,QString, QStringList,QStringList, CommandController::sCommandData)));
                disconnect(p_dev_factory, SIGNAL(deviceReadyLog(int,QStringList)),
                           this, SLOT(deviceLogMessage(int, QStringList)));
                disconnect(p_dev_factory, SIGNAL(deviceCheckIsReady(DevicesFactory::E_DeviceType,QString,bool)),
                           this, SLOT(deviceCheckReady(DevicesFactory::E_DeviceType,QString,bool)));
            }
        }
    }catch(...) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - disconnectToDevSignals -ERR catch";
#endif
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - disconnectToDevSignals -OK";
#endif
}

void ViewController::connectToDevSignals() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - connectToDevSignals";
#endif
    try {
        if(connFactory->getCountConnection() > 0) {
            DevicesFactory *p_dev_factory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
            if(p_dev_factory != nullptr) {
                connect(p_dev_factory, SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
                connect(p_dev_factory, SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
                connect(p_dev_factory, SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
                connect(p_dev_factory, SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
                connect(p_dev_factory, SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
                connect(p_dev_factory, SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                        this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
                connect(p_dev_factory, SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)),
                        this, SLOT(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)));
                connect(p_dev_factory, SIGNAL(deviceReadyLog(int, QStringList)),
                        this, SLOT(deviceLogMessage(int, QStringList)));
                connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceCheckIsReady(DevicesFactory::E_DeviceType,QString,bool)),
                        this, SLOT(deviceCheckReady(DevicesFactory::E_DeviceType,QString,bool)));
            }
        }
    } catch(...) {
#if USE_DB_VIEWCONTROLLER == 1
        qDebug() << "ViewController: - connectToDevSignals -ERR catch";
#endif
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - connectToDevSignals -OK";
#endif
}

void ViewController::setChangedIndexDevice(int interfaceIndex, int devIndex) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setChangedIndexDevice " << interfaceIndex << " " << devIndex;
#endif
    disconnectToDevSignals();
    connectToDevSignals(); // get interface property
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceCommandUpdateByIndex(interfaceTree->getDevIndex());
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit devSetActiveDeviceProperty(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),
                                    getDeviceFactoryByIndex(interfaceIndex)->getDeviceName(devIndex));
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setChangedIndexDevice -OK" << interfaceIndex << " " << devIndex;
#endif
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    // add interace command to read current property interface
    //...
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setChangedIndexInteface " << interfaceIndex;
#endif
    disconnectToDevSignals();
    interfaceTreeChanged(interfaceIndex, ConnectionFactory::Type_Update_ChangedIndex);
    connectToDevSignals(); // get interface property
    emit devUpdateLogMessage(interfaceTree->getIoIndex(), interfaceTree->getDevIndex(),1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit interfaceSetActiveProperty(interfaceTree->getIoIndex(),
                                    connFactory->getInterace(interfaceTree->getIoIndex())->getType());
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setChangedIndexInteface -OK" << interfaceIndex;
#endif
}


































//************************************************************************/
//**                  ONLY PROGRESS TMK24                               **/
//**                        TARIR                                       **/
//************************************************************************/
void ViewController::getCurrentDevTarTable() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevTarTable";
#endif
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "read current dev tar table");
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getCurrentDevTarTable -OK";
#endif
}
void ViewController::setTableFromFrontEnd(QString uniqDevName, QStringList valuesLiters, QStringList valuesFuelLevel) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setTableFromFrontEnd";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        pService->placeTableFromFrontEnd(uniqDevName, valuesLiters, valuesFuelLevel);
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setTableFromFrontEnd -OK";
#endif
}

void ViewController::sendReqWriteTarrirAllDev() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqWriteTarrirAllDev";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        for(auto i:pService->requestWriteTableToAllDevice()) {
            // извлекаем данные из таблциц
            QPair<QStringList,QStringList> table;
            table = pService->getTableAtDeviceToPair(i);
            // отправляем всем dev из списка команду на запись таблиц
            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i),
                                                                                        "set current dev tar table",
                                                                                        table.first, table.second);
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqWriteTarrirAllDev -OK";
#endif
}

void ViewController::setCurrentDevChangeId(QString password, QString uniqNameIdNew, QString uniqNameIdCurrent) {
    QPair<QStringList,QStringList> id;
    QString devpassword;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setCurrentDevChangeId";
#endif
    id.first.push_back("netAddress_value");
    id.second.push_back(uniqNameIdNew);
    QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first;
    for(int i2 =0; i2<keyList.size(); i2++) {
        if(keyList.at(i2) == QString("password")) {
            devpassword = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second.at(i2);
        }
    }
    if(devpassword == password && uniqNameIdNew.toInt() > 0) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "change current dev id",
                                                                                    id.first, id.second);
    } else {
        emit devErrorOperation(tr("Ошибка операции!\nНе правильные параметры или ошибка в действиях оператора"));
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - setCurrentDevChangeId -OK";
#endif
}

int ViewController::getTarMaxCountStep() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarMaxCountStep";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        if(pService !=nullptr) {
            return pService->getMaxCountStep();
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarMaxCountStep -OK";
#endif
    return 0;
}

void ViewController::sendReqExportTarrirAllDevToCsv(QString pathFile) {
    QStringList exportList;
    QString str;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqExportTarrirAllDevToCsv";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        int devAll = pService->getDeviceCount();
        // id[devType], объем, уровень топлива
        for(int devCounter=0; devCounter<devAll; devCounter++) {
            QStringList litersList;
            QStringList fuelLevelList;
            // получаем стоблец с liters и fuelLevel
            QPair<QStringList,QStringList> tableData;
            tableData = pService->getTableAtDeviceToPair(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(devCounter));
            for(int tableCounter=0; tableCounter<tableData.first.size(); tableCounter++) {
                // lites
                litersList << tableData.first.at(tableCounter);
                // fuelLevel
                fuelLevelList << tableData.second.at(tableCounter);
            }
            str.clear();
            str.push_back("\"" + QString("ID/Тип") + "\"" + ",");
            str.push_back("\"" + QString("Объем") + "\"" + ",");
            str.push_back("\"" + QString("Уровень") + "\"");
            exportList.push_back(str);
            for(int makeCounter=0; makeCounter<litersList.size(); makeCounter++) {
                str.clear();
                str.push_back("\"" + QString("ID%1[%2]").arg(pService->getDeviceProperty(devCounter).at(1)).arg(pService->getDeviceProperty(devCounter).at(0)) + "\"" + ",");
                str.push_back("\"" + ((litersList.size() >= makeCounter) ? (litersList.at(makeCounter) + "\"" + ",") : QString("Нет данных")));
                str.push_back("\"" + ((fuelLevelList.size() >= makeCounter) ? (fuelLevelList.at(makeCounter) + "\"") : QString("Нет данных")));
                exportList.push_back(str);
            }
        }
        if(!exportList.empty()) {
            if(pathFile.size() > 0) {
                if(!pathFile.contains(".csv")) {
                    pathFile.push_back(".csv");
                }
                if(pathFile.count(':') > 1) { // windows
                    pathFile.remove("file:///");
                } else {
                    pathFile.remove("file://"); // unix
                }
                QFile file(pathFile);
                if (file.open(QFile::WriteOnly | QFile::Text)) {
                    QTextStream s(&file);
                    for (int counterExport=0; counterExport<exportList.size(); ++counterExport) {
                        s << exportList.at(counterExport) << '\n';
                    }
                }
                file.close();
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqExportTarrirAllDevToCsv -OK";
#endif
}

QStringList ViewController::getAvailableDevTarrirAdd_DevType() {
    QStringList resList;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevType";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(i);
        }
    }
    return resList;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevType -OK";
#endif
}
QStringList ViewController::getAvailableDevTarrirAdd_DevId() {
    QStringList resList;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevId";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(i);
        }
    }
    return resList;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevId -OK";
#endif
}
QStringList ViewController::getAvailableDevTarrirAdd_DevSerialNumber() {
    QStringList resList;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevSerialNumber";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).first;
            for(int i2 =0; i2<keyList.size(); i2++) {
                if(keyList.at(i2) == QString("serialNum")) {                                                                                 // TOOD:!!!!!
                    resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).second.at(0);
                }
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getAvailableDevTarrirAdd_DevSerialNumber -OK";
#endif
    return resList;
}

QStringList ViewController::getTarCurrentDeviceData(int index) {
    QStringList res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarCurrentDeviceData";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            if(pService != nullptr) {
                res = pService->getCurrentDataDevice(index);
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarCurrentDeviceData -OK";
#endif
    return res;
}

QList<int> ViewController::getTarCurrentDeviceChartData(int index) {
    QList<int> res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarCurrentDeviceChartData";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            if(pService != nullptr) {
                res = pService->getCurrentChartDataDevice(index);
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTarCurrentDeviceChartData -OK";
#endif
    return res;
}

int ViewController::getStayedDevTarrirCount() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getStayedDevTarrirCount";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            if(pService != nullptr) {
                return pService->getDeviceCount();
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getStayedDevTarrirCount -OK";
#endif
    return 0;
}

QStringList ViewController::getStayedDevTarrir_DevProperty(QString propertyName) {
    QStringList res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getStayedDevTarrir_DevProperty";
#endif
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            if(pService != nullptr) {
                for(int i=0; i<pService->getDeviceCount(); i++) {
                    if(propertyName.toLower() == "type") {
                        res << pService->getDeviceProperty(i).at(0); // type
                    }
                    if(propertyName.toLower() == "id") {
                        res << pService->getDeviceProperty(i).at(1); // id
                    }
                    if(propertyName.toLower() == "sn") {
                        res << pService->getDeviceProperty(i).at(2); // serialNum
                    }
                }
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getStayedDevTarrir_DevProperty -OK";
#endif
    return res;
}


bool ViewController::addTarrirDev(QString devTypeName, QString devId) {
    bool res = false;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addTarrirDev";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        res = pService->addDevice(devTypeName, devId,"-----");
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - addTarrirDev -OK";
#endif
    return res;
}
void ViewController::removeTarrirDev(QString devTypeName, QString devId) {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeTarrirDev -OK";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        if(pService != nullptr) {
            pService->removeDevice(devTypeName, devId);
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - removeTarrirDev -OK";
#endif
}

void ViewController::setLastRealTimeValuesToStep(int indexStep) {
    //#if USE_DB_VIEWCONTROLLER == 1
    //    qDebug() << "ViewController: - setLastRealTimeValuesToStep";
    //#endif
    ////    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
    //        //  Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
    //        //  pService->setLastRealTimeValuesToStep(indexStep);
    ////    }
    //#if USE_DB_VIEWCONTROLLER == 1
    //    qDebug() << "ViewController: - setLastRealTimeValuesToStep -OK";
    //#endif
}

//1) считать таблицу с добавленных устройств
// отправляем в контроллер список dev с id
// указываем что считать таблицу
// ожидаем ответа по очереди
// когда последний опрошен, отсылаем результат в qml
// если ответа небыло, значение выделить красным и вывести message
void ViewController::sendReqGetTarrirAllDev() {
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqGetTarrirAllDev";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        if(pService != nullptr) {
            for(auto i:pService->requestGetTableFromAllDevice()) {      // TODO: плохо, можно взять пустой список и ждать ответа
                if(i.length() > 0) {
                    // отправляем всем dev из списка команду на чтение таблицы
                    DevicesFactory *pdeviceFactory = nullptr;
                    pdeviceFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
                    if(pdeviceFactory != nullptr) {
                        int devIndex = pdeviceFactory->findDeviceIndex(i);
                        if(devIndex >= 0) {
                            pdeviceFactory->sendCustomCommadToDev(devIndex, "read current dev tar table");
                        } else {
                            qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR find device";
                        }
                    } else {
                        qDebug() << "ViewController: - sendReqGetTarrirAllDev -ERR nullprt deviceFactory";
                    }
                }
            }
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - sendReqGetTarrirAllDev -OK";
#endif
}

QStringList ViewController::getTableAtDevice(int index) {
    QStringList res;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTableAtDevice";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        if(pService != nullptr) {
            res = pService->getTableAtDevice(index);
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTableAtDevice -OK";
#endif
    return res;
}

int ViewController::getTableCountReady() {
    int res = 0;
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTableCountReady";
#endif
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        if(pService != nullptr) {
            res = pService->requestGetTableFromAllDevice().size();
        }
    }
#if USE_DB_VIEWCONTROLLER == 1
    qDebug() << "ViewController: - getTableCountReady -OK";
#endif
    return res;
}
