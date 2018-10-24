#include "viewController.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018_Data.h"

ViewController::ViewController(Model *pInterfaceModel, QObject *parent) : QObject(parent) {

    this->connFactory = new ConnectionFactory();
    this->interfaceTree = pInterfaceModel;

    connect(interfaceTree, SIGNAL(currentIndexIsChangedInteface(int)), this, SLOT(setChangedIndexInteface(int)));
    connect(connFactory, SIGNAL(updateTree(ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType)));

    // TODO: the service need and necessery for other action
    this->serviceList.push_back(new Progress_tmk24Service("PROGRESS TMK24"));
    this->serviceList.push_back(new Nozzle_Rev_0_00_Service("Nozzle Rev 0.0"));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
//        addConnection("serial", "ttyUSB0", QStringList("baudrate"), QStringList("19200"));
//        addDeviceToConnection("PROGRESS TMK24", QStringList("devId"), QStringList("3"));
//        addDeviceToConnection("PROGRESS TMK24", QStringList("devId"), QStringList("4"));
    });

    QTimer::singleShot(1000, Qt::CoarseTimer, [&] {
        //        addConnection("serial", "ttyACM0", QStringList("baudrate"), QStringList("115200"));
        //        addDeviceToConnection("Nozzle Rev 0.0", QStringList("devId"), QStringList("1"));
    });
}

QStringList ViewController::getListSession() {
    QStringList sessionList;
    for(int i=0; i<15; i++) {
        sessionList << QString("lalalla_%1").arg(i);
    }
    return sessionList;
}

bool ViewController::loadSession(QString sessionName) {

}

QString ViewController::saveCurrentSession() {
    return QString("AnyName") + " - Сохранено";
}

QString ViewController::saveCurrentSessionAs(QString sessionName) {
    return sessionName + " - Сохранено";
}

void ViewController::closeApplication() {
    exit(0);
}

QStringList ViewController::getInterfaceAvailableToAdd(QString typeName) {
    QStringList res;
    res = connFactory->getAvailableName(typeName);
    emit devUpdateLogMessage(interfaceTree->getDevIndex(), 0, QString("Получение списка интерфейсов [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    return res;
}

bool ViewController::addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam) {
    bool res = false;
    if((!name.isEmpty()) && (!name.isEmpty())) {
        res = connFactory->addConnection(typeName, name, QPair<QStringList,QStringList>(keyParam, valueParam));
        if(res) {
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
            emit devUpdateLogMessage(interfaceTree->getDevIndex(), 0, QString("Добавление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            emit interfaceSetActiveProperty(interfaceTree->getIoIndex(),
                                            connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            emit addInterfaceSuccesfull(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                        connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty().first,
                                        connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty().second);
            interfaceTree->addConnection(name);
        } else {
            emit addConnectionFail(name);
        }
    }
    return res;
}

void ViewController::removeActiveInterface() {
    int indexRemove = interfaceTree->getIoIndex();
    interfaceTree->removeConnection(indexRemove);
    getDeviceFactoryByIndex(indexRemove)->removeDeviceAll();
    connFactory->removeConnection(indexRemove);
    emit deleteInterfaceSuccesfull(indexRemove);
    if(getInterfaceCount() == 0) {
        emit interfaceAndDeviceListIsEmpty();
    }
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::removeActiveDevice() {
    int indexRemove = interfaceTree->getDevIndex();
    interfaceTree->removeDeviceToConnection(interfaceTree->getIoIndex(), indexRemove);
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->removeDeviceByIndex(indexRemove);
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit deleteDeviceSuccesfull(indexRemove);
    if(getDeviceCount() == 0) {
        emit interfaceSetActiveProperty(interfaceTree->getIoIndex(),
                                        connFactory->getInterace(interfaceTree->getIoIndex())->getType());
    } else{
        emit devSetActiveDeviceProperty(interfaceTree->getDevIndex(),
                                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    }
}

bool ViewController::addDeviceToConnection(QString devTypeName, QStringList keyParam, QStringList valueParam) {
    bool res = false;
    interfacesAbstract *pInterface = nullptr;
    // get current interface
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()));
    if(pInterface != nullptr) {
        bool serviceIsFinded = false;
        ServiceDevicesAbstract *p_service = nullptr;
        for(auto services:serviceList) {
            if(services->getDeviceType() == devTypeName) {
                serviceIsFinded = true;
                p_service = services;
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
                emit devUpdateLogMessage(interfaceTree->getDevIndex(),0, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
                emit addDeviceSuccesfull(getDeviceFactoryByIndex(
                                             interfaceTree->getIoIndex())->getDeviceTypeNameByType(
                                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceType(interfaceTree->getDevIndex())),
                                         QStringList(), QStringList());
            } else {
                emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
                emit addDeviceFail(devTypeName, "Не получилось добавить одно или более устройств\nВозможные причины:\n 1) такой адрес уже используется\n 2) устройство отличается от типа уже добавленных устройств");
            }
        }
    }
    return res;
}

void ViewController::checkDeviceFromConnection(QString devTypeName, QStringList keyParam, QStringList valueParam) { // uniqIdDevice password
    if(devTypeName == QString(Progress_tmk24::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Progress_Tmk24, keyParam, valueParam);
    }
    if(devTypeName == QString(Progress_tmk4UX::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Progress_tmk4UX, keyParam, valueParam);
    }
    if(devTypeName == QString(Nozzle_Revision_0_00_Oct_2018::name)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->checkDeviceIsOnline(DevicesFactory::Type_Nozzle_rev_0_00, keyParam, valueParam);
    }
}

QStringList ViewController::getDeviceAvailableType() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getAvailableDeviceTypes();
}

QString ViewController::getCurrentInterfaceName() {
    QString name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    return name;
}

int ViewController::getInterfaceCount() {
    return connFactory->getCountConnection();
}

QList<QString> ViewController::getCurrentDevPeriodicDataKey() {
    QList<QString> res;
    QString name;
    name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
    }
    return res;
}

QList<QString> ViewController::getCurrentDevPeriodicDataValue() {
    QList<QString> res;
    QString name;
    name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
    }
    return res;
}

int ViewController::getDeviceCount() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
}

QStringList ViewController::getCurrentDevPropertyKey() {
    QStringList ret = connFactory->getInterace(
                connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))->getDeviceFactory()
            ->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first;
    return ret;
}

QStringList ViewController::getCurrentDevPropertyValue() {
    QStringList ret = connFactory->getInterace(
                connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))->getDeviceFactory()
            ->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second;
    return ret;
}

DevicesFactory* ViewController::getDeviceFactoryByIndex(int indexIterface) {
    return connFactory->getInterace(connFactory->getInteraceNameFromIndex(indexIterface))->getDeviceFactory();
}

bool ViewController::isCurrentDevice(QString uniqNameId) {
    if(interfaceTree->getIoIndex() < connFactory->getCountConnection()) {
        if(interfaceTree->getDevIndex() < getDeviceCount()) {
            if(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(interfaceTree->getDevIndex()) == uniqNameId) {
                return true;
            }
        }
    }
    return false;
}

bool ViewController::setCurrentDevCustomCommand(QString typeCommand, QStringList keys, QStringList values) {
    bool res = false;
    // сперва проверка на команды
    // которые можно выполнить сранужи
    if(getDeviceCount() != 0) {
        if(typeCommand == "change device head name") {
            for(auto i=0; i<keys.length(); i++) {
                if(keys[i] == "newHeader") {
                    res = interfaceTree->changeDeviceHeader(getCurrentInterfaceName(),
                                                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceNameWithId(interfaceTree->getDevIndex()), values[i]);
                    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceHeader(interfaceTree->getDevIndex(), values[i]);
                    return res;
                }
            }
        }
    }
    res = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(),
                                                                                      typeCommand, keys, values);
    return res;
}

DeviceAbstract* ViewController::getCurrentDeviceToAbstract() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
}


//************************************************************************/
//**                        SECURITY, PROPERTYES                        **/
//************************************************************************/
void ViewController::deviceConnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        emit devConnected(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
    }
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),0, QString("Устройста подключено[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceDisconnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        emit devDisconnected(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId),
                             getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceTypeNameByType(type));
    }
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Устройство потеряно [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyCurrentData(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    switch(type) {
    case DevicesFactory::Type_Progress_tmk4UX: {
        if(isCurrentDevice(uniqNameId)) {
            emit devReadyPeriodicData(interfaceTree->getDevIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        }
    }
        break;
    case DevicesFactory::Type_Progress_Tmk24: {
        emit devReady(interfaceTree->getDevIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType());
        emit devReadyPeriodicData(interfaceTree->getDevIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                  getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        int devIndex = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId);
        if(devIndex >= 0) {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(
                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(devIndex)->getServiceAbstract());
            pService->placeCurrenDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(devIndex));
        }
    }
        break;
    case DevicesFactory::Type_Nozzle_rev_0_00: {
        if(isCurrentDevice(uniqNameId)) {
            emit devReadyPeriodicData(interfaceTree->getDevIndex(), connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).first,
                                      getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId)).second);
        }
    }
        break;
    case DevicesFactory::Type_Undefined: break;
    }
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceCheckReady(DevicesFactory::E_DeviceType devType, QString devUniqNameId, bool result) {
    if(devType == DevicesFactory::Type_Progress_Tmk24) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Progress_tmk24::name), devUniqNameId, "...", result);
    }
    if(devType == DevicesFactory::Type_Progress_tmk4UX) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Progress_tmk4UX::name), devUniqNameId, "...", result);
    }
    if(devType == DevicesFactory::Type_Nozzle_rev_0_00) {
        emit devReadyCheckCommand(interfaceTree->getIoIndex(), QString(Nozzle_Revision_0_00_Oct_2018::name), devUniqNameId, "...", result);
    }
}

void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    emit devReadyProperties(interfaceTree->getDevIndex(),
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()),
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getIoIndex()).first,
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getIoIndex()).second);
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),0, QString("Получение информации с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyInit(DevicesFactory::E_DeviceType type, QString uniqNameId) {}

void ViewController::interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type) {
    deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, interfaceTree->getDevIndex());

    switch(type) {
    case ConnectionFactory::Type_Update_ChangedIndex:
    case ConnectionFactory::Type_Update_Add:
    case ConnectionFactory::Type_Update_Removed:
        break;
    }
    if(connFactory->getCountConnection() >0) {
        emit interfaceReadyProperties(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      interfaceTree->getIoIndex(),
                                      connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty().first,
                                      connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty().second);
    }
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceLogMessage(int indexDev, QStringList message) {
    while(!message.empty()) {
        emit devUpdateLogMessage(interfaceTree->getDevIndex(),0, message.first());
        message.pop_front();
    }
}

void ViewController::deviceReadyCustomCommand(int indexDev, QString message,
                                              QStringList keyCustomData, QStringList valueCustomData,
                                              CommandController::sCommandData commmandData) {
    DevicesFactory *pDevFactory = nullptr;
    QStringList keys;
    QStringList values;
    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
    if(pDevFactory != nullptr) {
        emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        switch(pDevFactory->getDeviceType(pDevFactory->getDeviceName(indexDev))) {
        case DevicesFactory::Type_Progress_Tmk24: {
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_max) {
                keys << "lls_calibrate_max" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_min) {
                keys << "lls_calibrate_min" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_settings) {
                keys << "lls_read_settings" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_errors) {
                keys << "lls_read_errors" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceErrrors(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceErrrors(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_cal_table) {
                Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                pService->placeTableFromDevice(commmandData.deviceIdent, keyCustomData, valueCustomData);
                if(pService->readTableAllDeviceIsReady()) {
                    //emit devUpdateReadTarTable(pService->getDeviceCount());
                    keys << "lls_read_cal_table" << keyCustomData;
                    values << message.toLower() << valueCustomData;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  interfaceTree->getDevIndex(),
                                                  keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_write_cal_table) {
                Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
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
                                                  interfaceTree->getDevIndex(),
                                                  keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_lvl_all) {
                keys << "lls_read_lvl_all" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }

            if(commmandData.devCommand == Progress_tmk24Data::lls_write_settings) {
                keys << "lls_write_settings" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
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
                                              interfaceTree->getDevIndex(),
                                              QStringList("getPassword"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig) { // settings
                keys << "getAccelConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig) { // settings
                keys << "getNetworkConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand) {}
            // current data
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData) { // current data
                keys << "getAccelData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData) { // current data
                keys << "getNetworkData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getOtherData) { // current data
                keys << "getOtherData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData) { // current data
                keys << "getCardProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData) { // current data
                keys << "getBatteryProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              keys, values, commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword) { // reply exec
                keys << "E_ConsoleCommandType_setPassword" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              QStringList("setNetworkPassword"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig) { // reply exec
                keys << "E_ConsoleCommandType_setAccelConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              QStringList("setAccelConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint) { // reply exec
                keys << "E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              QStringList("setAccelUseCurrentValuesAsNullPoint"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig) { // reply exec
                keys << "E_ConsoleCommandType_setNetworkConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              QStringList("setNetworkConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setBatteryNewAccum) { // reply exec
                keys << "E_ConsoleCommandType_setBatteryNewAccum" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                values << message.toLower() << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              interfaceTree->getDevIndex(),
                                              QStringList("setBatteryNewAccum"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
        }
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        if(getDeviceCount() >= indexDev) {
            interfaceTree->setDevStatusByIndex(indexDev, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceStatusByIndex(indexDev));
        }
        break;
    case DevicesFactory::Type_Update_RamakeAfterChangeInterface: break;
    case DevicesFactory::Type_Update_Removed: break;
    case DevicesFactory::Type_Update_Added: break;
    case DevicesFactory::Type_Update_PasswordIncorrect:
        //        emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
        //                            "Смена пароля", QStringList(QString("Пароль не верный [Тип=%1]").
        //                                                        arg(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev))));
        emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    case DevicesFactory::Type_Update_TypeIncorrect:
        emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        //emit devWrongTypeIncorrect(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
        //                          getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeaderByIndex(indexDev).first());
        break;
    }
}

void ViewController::disconnectToDevSignals() {
    int countConn = connFactory->getCountConnection();
    for(int i=0; i<countConn; i++) {
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
        disconnect(getDeviceFactoryByIndex(i),
                   SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                   this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)),
                   this, SLOT(deviceReadyCustomCommand(int,QString, QStringList,QStringList, CommandController::sCommandData)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyLog(int,QStringList)),
                   this, SLOT(deviceLogMessage(int, QStringList)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceCheckIsReady(DevicesFactory::E_DeviceType,QString,bool)),
                   this, SLOT(deviceCheckReady(DevicesFactory::E_DeviceType,QString,bool)));
    }
}

void ViewController::connectToDevSignals() {
    if(connFactory->getCountConnection() > 0) {
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)),
                this, SLOT(deviceReadyCustomCommand(int,QString,QStringList,QStringList,CommandController::sCommandData)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyLog(int, QStringList)),
                this, SLOT(deviceLogMessage(int, QStringList)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceCheckIsReady(DevicesFactory::E_DeviceType,QString,bool)),
                this, SLOT(deviceCheckReady(DevicesFactory::E_DeviceType,QString,bool)));
    }
}

void ViewController::setChangedIndexDevice(int interfaceIndex, int devIndex) {
    disconnectToDevSignals();
    connectToDevSignals(); // get interface property
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceCommandUpdateByIndex(interfaceTree->getDevIndex());
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit devSetActiveDeviceProperty(interfaceTree->getDevIndex(),
                                    getDeviceFactoryByIndex(interfaceIndex)->getDeviceName(devIndex));
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    // add interace command to read current property interface
    //...
    disconnectToDevSignals();
    interfaceTreeChanged(ConnectionFactory::Type_Update_ChangedIndex);
    connectToDevSignals(); // get interface property
    emit devUpdateLogMessage(interfaceTree->getDevIndex(),1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit interfaceSetActiveProperty(interfaceTree->getIoIndex(),
                                    connFactory->getInterace(interfaceTree->getIoIndex())->getType());
}


































//************************************************************************/
//**                  ONLY PROGRESS TMK24                               **/
//**                        TARIR                                       **/
//************************************************************************/
void ViewController::getCurrentDevTarTable() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "read current dev tar table");
}
void ViewController::setTableFromFrontEnd(QString uniqDevName, QStringList valuesLiters, QStringList valuesFuelLevel) {
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        pService->placeTableFromFrontEnd(uniqDevName, valuesLiters, valuesFuelLevel);
    }
}

void ViewController::sendReqWriteTarrirAllDev() {
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
}

void ViewController::setCurrentDevChangeId(QString password, QString uniqNameIdNew, QString uniqNameIdCurrent) {
    QPair<QStringList,QStringList> id;
    QString devpassword;
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
}

int ViewController::getTarMaxCountStep() {
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        return pService->getMaxCountStep();
    }
    return 0;
}

void ViewController::sendReqExportTarrirAllDevToCsv(QString pathFile) {
    QStringList exportList;
    QString str;

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
}

QStringList ViewController::getAvailableDevTarrirAdd_DevType() {
    QStringList resList;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(i);
        }
    }
    return resList;
}
QStringList ViewController::getAvailableDevTarrirAdd_DevId() {
    QStringList resList;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(i);
        }
    }
    return resList;
}
QStringList ViewController::getAvailableDevTarrirAdd_DevSerialNumber() {
    QStringList resList;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
        for(int i=0; i<devCount; i++) {
            QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).first;
            for(int i2 =0; i2<keyList.size(); i2++) {
                if(keyList.at(i2) == QString("serialnumber")) {                                                                                 // TOOD:!!!!!
                    resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).second.at(0);
                }
            }
        }
    }
    return resList;
}

QStringList ViewController::getTarCurrentDeviceData(int index) {
    QStringList res;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            res = pService->getCurrentDataDevice(index);
        }
    }
    return res;
}

QList<int> ViewController::getTarCurrentDeviceChartData(int index) {
    QList<int> res;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            res = pService->getCurrentChartDataDevice(index);
        }
    }
    return res;
}

int ViewController::getStayedDevTarrirCount() {
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
            return pService->getDeviceCount();
        }
    }
    return 0;
}

QStringList ViewController::getStayedDevTarrir_DevProperty(QString propertyName) {
    QStringList res;
    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
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
    return res;
}


bool ViewController::addTarrirDev(QString devTypeName, QString devId) {
    bool res = false;
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        res = pService->addDevice(devTypeName, devId,"-----");
    }
    return res;
}
void ViewController::removeTarrirDev(QString devTypeName, QString devId) {
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        pService->removeDevice(devTypeName, devId);
    }
}

void ViewController::setLastRealTimeValuesToStep(int indexStep) {
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        //        pService->setLastRealTimeValuesToStep(indexStep);
    }
}

//1) считать таблицу с добавленных устройств
// отправляем в контроллер список dev с id
// указываем что считать таблицу
// ожидаем ответа по очереди
// когда последний опрошен, отсылаем результат в qml
// если ответа небыло, значение выделить красным и вывести message
void ViewController::sendReqGetTarrirAllDev() {
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        for(auto i:pService->requestGetTableFromAllDevice()) {
            // отправляем всем dev из списка команду на чтение таблицы
            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(
                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i),
                        "read current dev tar table");
        }
    }
}

QStringList ViewController::getTableAtDevice(int index) {
    QStringList res;
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        res = pService->getTableAtDevice(index);
    }
    return res;
}

int ViewController::getTableCountReady() {
    int res = 0;
    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
        res = pService->requestGetTableFromAllDevice().size();
    }
    return res;
}
