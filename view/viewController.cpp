#include "viewController.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Oct_2018_Data.h"

ViewController::ViewController(Model *pInterfaceModel, QObject *parent) : QObject(parent) {

    this->connFactory = new ConnectionFactory();

    this->interfaceTree = pInterfaceModel;

    connect(connFactory, SIGNAL(updateTree(ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType)));

    // TODO: the service need and necessery for other action
    this->serviceList.push_back(new Progress_tmk24Service("PROGRESS TMK24"));
    this->serviceList.push_back(new Nozzle_Rev_0_00_Service("Nozzle Revision 0.00 Oct 2018"));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        addConnection("serial", "ttyACM0", QStringList("baudrate"), QStringList("115200"));
        addConnection("serial", "ttyUSB0", QStringList("baudrate"), QStringList("115200"));
        addDeviceToConnection("PROGRESS TMK24", QStringList("uniqDevName"), QStringList("55"));
        addDeviceToConnection("Nozzle Revision 0.00 Oct 2018", QStringList("uniqDevName"), QStringList("1"));
        addDeviceToConnection("Nozzle Revision 0.00 Oct 2018", QStringList("uniqDevName"), QStringList("2"));
    });
}

//      addDeviceToConnection("PROGRESS TMK24", QString::number(1), "");
//      addTarrirDev("PROGRESS TMK24", QString::number(a+5));

QStringList ViewController::getInterfaceAvailableToAdd(QString typeName) {
    QStringList res;
    res = connFactory->getAvailableName(typeName);
    emit devUpdateLogMessage(0, QString("Получение списка интерфейсов [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    return res;
}

bool ViewController::addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam) {
    bool res = false;
    if((!name.isEmpty()) && (!name.isEmpty())) {
        res = connFactory->addConnection(typeName, name, QPair<QStringList,QStringList>(keyParam, valueParam));
        if(res) {
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
            emit devUpdateLogMessage(0, QString("Добавление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            interfaceTree->addConnection(name);
        } else {
            emit addConnectionFail(name);
        }
    }
    return res;
}

void ViewController::removeActiveInterface() {
    disconnectToDevSignals();
    int indexRemove = interfaceTree->getIoIndex();
    interfaceTree->removeConnection(indexRemove);
    getDeviceFactoryByIndex(indexRemove)->removeDeviceAll();
    connFactory->removeConnection(indexRemove);
    if(getInterfaceCount() == 0) {
        emit interfaceAndDeviceListIsEmpty();
    }
    connectToDevSignals();
    emit devUpdateLogMessage(1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::removeActiveDevice() {
    int indexRemove = interfaceTree->getDevIndex();
    interfaceTree->removeDeviceToConnection(interfaceTree->getIoIndex(), indexRemove);
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->removeDeviceByIndex(indexRemove);
    emit devUpdateLogMessage(2, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    if(getDeviceCount() == 0) {
        emit interfaceSetActiveProperty(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
    } else{
        emit devSetActiveDeviceProperty(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
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
                interfaceTree->addDeviceToConnection(getCurrentInterfaceName(), "undefined", false);
                QString devHeader = getDeviceHeaderByIndex(interfaceTree->getDevIndex()).last();
                interfaceTree->changeDeviceHeader(getCurrentInterfaceName(), "undefined", devHeader);
                connect(interfaceTree, SIGNAL(currentIndexIsChangedDevice(int,int)), this, SLOT(setChangedIndexDevice(int,int)));
                connect(interfaceTree, SIGNAL(currentIndexIsChangedInteface(int)), this, SLOT(setChangedIndexInteface(int)));
                // make it device - "not ready"
                // while not read settings
                pInterface->getDeviceFactory()->setDeviceReInitByIndex(interfaceTree->getDevIndex());
                emit devUpdateLogMessage(0, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            } else {
                emit devUpdateLogMessage(2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
                emit addDeviceFail(devTypeName);
            }
        }
    }
    return res;
}

QStringList ViewController::getDeviceAvailableType() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getAvailableDeviceTypes();
}

// TODO: find devices
void ViewController::setDeviceFindConnected(QString devType) {
}

QString ViewController::getCurrentInterfaceName() {
    QString name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    return name;
}

int ViewController::getInterfaceCount() {
    return connFactory->getCountConnection();
}


QList<int> ViewController::getCurrentDevChart() {
    QList<int> res;
    QString name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceChartByIndex(interfaceTree->getDevIndex());
    }
    return res;
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

QStringList ViewController::getDeviceHeaderByIndex(int devIndex) {
    QStringList ret = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))
            ->getDeviceFactory()->getDeviceHeaderByIndex(devIndex);
    return ret;
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

void ViewController::getCurrentDevCustomCommand(QString typeCommand) {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), typeCommand); //"get current dev settings"
}
void ViewController::getCurrentDevCustomCommandWithoutAckDialog(QString typeCommand, QStringList keys, QStringList values) {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), typeCommand, keys, values); //"get current dev settings witout dialog"
}

void ViewController::setCurrentDevCustomCommand(QString typeCommand, QStringList keys, QStringList values) {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), typeCommand, keys, values);
}

void ViewController::setCurrentDevCustomCommandWithoutAckDialog(QString typeCommand, QStringList keys, QStringList values) {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), typeCommand, keys, values);
}

//void ViewController::setCurrentDevLevelAsEmpty() {
//    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current level value as min");
//}
//void ViewController::setCurrentDevLevelAsFull() {
//    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current level value as max");
//}

//-- it copy values from settings wihout request at device
//void ViewController::getCurrentDevSettingsWithoutRequest() {
//    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
//                        tr("Чтение настроек"), QStringList(tr("Чтение настроек успешно выполнено")));
//}
//void ViewController::setCurrentDevSettings(QStringList keys, QStringList values) {
//    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current dev settings", keys, values);
//}

//************************************************************************/
//**                        TARIR                                       **/
//************************************************************************/
//void ViewController::getCurrentDevTarTable() {
//    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "read current dev tar table");
//}
//void ViewController::setTableFromFrontEnd(QString uniqDevName, QStringList valuesLiters, QStringList valuesFuelLevel) {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        pService->placeTableFromFrontEnd(uniqDevName, valuesLiters, valuesFuelLevel);
//    }
//}

//void ViewController::sendReqWriteTarrirAllDev() {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        for(auto i:pService->requestWriteTableToAllDevice()) {
//            // извлекаем данные из таблциц
//            QPair<QStringList,QStringList> table;
//            table = pService->getTableAtDeviceToPair(i);
//            // отправляем всем dev из списка команду на запись таблиц
//            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(
//                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i), "set current dev tar table", table);
//        }
//    }
//}

//void ViewController::setCurrentDevChangeId(QString password, QString uniqNameIdNew, QString uniqNameIdCurrent) {
//    QPair<QStringList,QStringList> id;
//    QString devpassword;
//    id.first.push_back("netAddress_value");
//    id.second.push_back(uniqNameIdNew);
//    // TOOD:!!!!!
//    QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).first;
//    for(int i2 =0; i2<keyList.size(); i2++) {
//        if(keyList.at(i2) == QString("password")) {
//            devpassword = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(interfaceTree->getDevIndex()).second.at(i2);
//        }
//    }
//    if(devpassword == password && uniqNameIdNew.toInt() > 0) {
//        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "change current dev id", id);
//    } else {
//        emit devErrorOperation(tr("Ошибка операции!\nНе правильные параметры или ошибка в действиях оператора"));
//    }
//}

//int ViewController::getTarMaxCountStep() {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        return pService->getMaxCountStep();
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
//    QStringList resList;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//        for(int i=0; i<devCount; i++) {
//            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(i);
//        }
//    }
//    return resList;
//}
//QStringList ViewController::getAvailableDevTarrirAdd_DevId() {
//    QStringList resList;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//        for(int i=0; i<devCount; i++) {
//            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceIdTextByIndex(i);
//        }
//    }
//    return resList;
//}
//QStringList ViewController::getAvailableDevTarrirAdd_DevSerialNumber() {
//    QStringList resList;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        int devCount = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
//        for(int i=0; i<devCount; i++) {
//            QStringList keyList = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).first;
//            for(int i2 =0; i2<keyList.size(); i2++) {
//                if(keyList.at(i2) == QString("serialnumber")) {                                                                                 // TOOD:!!!!!
//                    resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).second.at(0);
//                }
//            }
//        }
//    }
//    return resList;
//}

//QStringList ViewController::getTarCurrentDeviceDataKey(int index) {
//    QStringList res;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//            res = pService->getCurrentDataDevice(index);
//        }
//    }
//    return res;
//}

//QStringList ViewController::getTarCurrentDeviceDataValue(int index) {
//    QStringList res;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//            res = pService->getCurrentDataDevice(index);
//        }
//    }
//    return res;
//}

//QList<int> ViewController::getTarCurrentDeviceChartData(int index) {
//    QList<int> res;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//            res = pService->getCurrentChartDataDevice(index);
//        }
//    }
//    return res;
//}

//DeviceAbstract* ViewController::getCurrentDeviceToAbstract() {
//    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
//}

//int ViewController::getStayedDevTarrirCount() {
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//            return pService->getDeviceCount();
//        }
//    }
//    return 0;
//}

//QStringList ViewController::getStayedDevTarrir_DevProperty(QString propertyName) {
//    QStringList res;
//    if(getInterfaceCount() > 0 && getDeviceCount() > 0) {
//        if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//            Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//            for(int i=0; i<pService->getDeviceCount(); i++) {
//                if(propertyName.toLower() == "type") {
//                    res << pService->getDeviceProperty(i).at(0); // type
//                }
//                if(propertyName.toLower() == "id") {
//                    res << pService->getDeviceProperty(i).at(1); // id
//                }
//                if(propertyName.toLower() == "sn") {
//                    res << pService->getDeviceProperty(i).at(2); // serialNum
//                }
//            }
//        }
//    }
//    return res;
//}


//bool ViewController::addTarrirDev(QString devTypeName, QString devId) {
//    bool res = false;
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        res = pService->addDevice(devTypeName, devId,"-----");
//    }
//    return res;
//}
//void ViewController::removeTarrirDev(QString devTypeName, QString devId) {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        pService->removeDevice(devTypeName, devId);
//    }
//}

//void ViewController::setLastRealTimeValuesToStep(int indexStep) {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        //        pService->setLastRealTimeValuesToStep(indexStep);
//    }
//}

//1) считать таблицу с добавленных устройств
// отправляем в контроллер список dev с id
// указываем что считать таблицу
// ожидаем ответа по очереди
// когда последний опрошен, отсылаем результат в qml
// если ответа небыло, значение выделить красным и вывести message
//void ViewController::sendReqGetTarrirAllDev() {
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        for(auto i:pService->requestGetTableFromAllDevice()) {
//            // отправляем всем dev из списка команду на чтение таблицы
//            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(
//                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i),
//                        "read current dev tar table");
//        }
//    }
//}

//QStringList ViewController::getTableAtDevice(int index) {
//    QStringList res;
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        res = pService->getTableAtDevice(index);
//    }
//    return res;
//}

//int ViewController::getTableCountReady() {
//    int res = 0;
//    if(getCurrentDeviceToAbstract()->getDevTypeName() == "PROGRESS TMK24") {
//        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(getCurrentDeviceToAbstract()->getServiceAbstract());
//        res = pService->requestGetTableFromAllDevice().size();
//    }
//    return res;
//}

//************************************************************************/
//**                        SECURITY, PROPERTYES                        **/
//************************************************************************/
void ViewController::deviceConnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devConnected(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devConnected(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(0, QString("Устройста подключено[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceDisconnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devDisconnected(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devDisconnected(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(2, QString("Устройство потеряно [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyCurrentData(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX: {
            emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
        }
            break;
        case DevicesFactory::Type_Progress_Tmk24: {
            emit devReadyPeriodicData(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
            int devIndex = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId);
            if(devIndex >= 0) {
                Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(
                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(devIndex)->getServiceAbstract());
                pService->placeCurrenDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(devIndex));
                pService->placeCurrentChartDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceChartByIndex(devIndex));
            }
        }
            break;
        case DevicesFactory::Type_Nozzle_rev_0_00: {
            emit devReadyPeriodicData(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()));
        }
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        emit devReadyProperties(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(interfaceTree->getDevIndex()), QStringList());
    }
    emit devUpdateLogMessage(0, QString("Получение информации с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyInit(DevicesFactory::E_DeviceType type, QString uniqNameId) {}

void ViewController::interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type) {
    disconnectToDevSignals();
    deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, interfaceTree->getDevIndex());

    switch(type) {
    case ConnectionFactory::Type_Update_ChangedIndex:
    case ConnectionFactory::Type_Update_Add:
    case ConnectionFactory::Type_Update_Removed:
        break;
    }
    if(connFactory->getCountConnection() >0) {
        emit interfaceReadyProperties(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                                      connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty());
    }
    emit devUpdateLogMessage(2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    connectToDevSignals();
}

void ViewController::deviceLogMessage(int indexDev, QStringList message) {
    while(!message.empty()) {
        emit devUpdateLogDeviceMessage(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), message.first());
        message.pop_front();
    }
}

void ViewController::deviceReadyCustomCommand(int indexDev, QString message, QStringList argList, CommandController::sCommandData commmandData) {
    DevicesFactory *pDevFactory = nullptr;
    QStringList keys;
    QStringList values;
    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());
    if(pDevFactory != nullptr) {
        emit devUpdateLogMessage(2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        switch(pDevFactory->getDeviceType(pDevFactory->getDeviceName(indexDev))) {
        case DevicesFactory::Type_Progress_Tmk24: {
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_max) {
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Задание границы измерения"),
                                        QStringList(tr("Задание границы измерения успешно выполнено")));
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_calibrate_max"), QStringList("normal"), commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Задание границы измерения"),
                                        QStringList(tr("Задание границы измерения не выполнено!")));
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_min) {
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Задание границы измерения"),
                                        QStringList(tr("Задание границы измерения успешно выполнено")));
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_calibrate_mix"), QStringList("normal"), commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Задание границы измерения"),
                                        QStringList(tr("Задание границы измерения не выполнено")));
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_settings) {
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение настроек"),
                                        QStringList(tr("Чтение настроек успешно выполнено")));
                    keys << "lls_read_settings" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение настроек"),
                                        QStringList(tr("Чтение настроек не выполнено")));
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_errors) {
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение ошибок"),
                                        QStringList(tr("Чтение ошибок успешно выполнено")));
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_read_errors"), QStringList("normal"), commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение ошибок"),
                                        QStringList(tr("Чтение ошибок не выполнено")));
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_cal_table) {
                Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                pService->placeTableFromDevice(commmandData.deviceIdent, argList);
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение таблицы"),
                                        QStringList(tr("Чтение таблицы успешно выполнено")));
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_read_cal_table"), QStringList("normal"), commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Чтение таблицы"),
                                        QStringList(tr("Чтение таблицы не выполнено")));
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
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Запись таблицы"), resWrite);
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_write_cal_table"), QStringList("normal"), commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_write_settings) {
                if (message == "Normal") {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Запись настроек"),
                                        QStringList(tr("Запись настроек успешно выполнена")));
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("lls_write_settings"), QStringList("normal"), commmandData.isNeedAckMessage);
                } else {
                    emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(), tr("Запись настроек"),
                                        QStringList(tr("Запись настроек не выполнена")));
                }
            }
        }
            break;
            // -- Type_Nozzle_Revision_0_00_Oct_2018
        case DevicesFactory::Type_Nozzle_rev_0_00: {
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_EmptyCommand) {}
            // init
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getPassword) {
                emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                              QStringList("getBatteryProperty"), QStringList("normal"), commmandData.isNeedAckMessage);
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelConfig) { // settings
                if(message.toLower() == "normal") {
                    keys << "getAccelConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkConfig) { // settings
                if(message.toLower() == "normal") {
                    keys << "getNetworkConfig" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getIsReadyCommand) {}
            // current data
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getAccelData) { // current data
                if(message.toLower() == "normal") {
                    keys << "getAccelData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getNetworkData) { // current data
                if(message.toLower() == "normal") {
                    keys << "getNetworkData" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getCardData) { // current data
                if(message.toLower() == "normal") {
                    keys << "getCardProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_getBatteryData) { // current data
                if(message.toLower() == "normal") {
                    keys << "getBatteryProperty" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).first;
                    values << "normal" << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex()).second;
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), keys, values, commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setPassword) { // reply exec
                if(message.toLower() == "normal") {
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("setNetworkPassword"), QStringList("normal"), commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelConfig) { // reply exec
                if(message.toLower() == "normal") {
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("setAccelConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setAccelUseCurrentValuesAsNullPoint) { // reply exec
                if(message.toLower() == "normal") {
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("setAccelUseCurrentValuesAsNullPoint"), QStringList("normal"), commmandData.isNeedAckMessage);
                }
            }
            if(commmandData.devCommand == Nozzle_Revision_0_00_Oct_2018_Data::E_ConsoleCommandType_setNetworkConfig) { // reply exec
                if(message.toLower() == "normal") {
                    emit devCustomCommandExecuted(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                                  QStringList("setNetworkConfig"), QStringList("normal"), commmandData.isNeedAckMessage);
                }
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
    case DevicesFactory::Type_Update_RamakeAfterChangeInterface:
    case DevicesFactory::Type_Update_Removed:
    case DevicesFactory::Type_Update_Added:
        break;
    case DevicesFactory::Type_Update_PasswordIncorrect:
        emit devShowMessage(connFactory->getInterace(interfaceTree->getIoIndex())->getType(),
                            "Смена пароля",
                            QStringList(QString("Пароль не верный [Тип=%1]")
                                        .arg(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev))));
        emit devUpdateLogMessage(2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    case DevicesFactory::Type_Update_TypeIncorrect:
        emit devUpdateLogMessage(2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit devWrongTypeIncorrect(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev),
                                   getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeaderByIndex(indexDev).first());
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
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,CommandController::sCommandData)),
                   this, SLOT(deviceReadyCustomCommand(int,QString, QStringList, CommandController::sCommandData)));
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyLog(int,QStringList)),
                   this, SLOT(deviceLogMessage(int, QStringList)));
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
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyCustomCommand(int,QString,QStringList,CommandController::sCommandData)),
                this, SLOT(deviceReadyCustomCommand(int,QString,QStringList,CommandController::sCommandData)));
        connect(getDeviceFactoryByIndex(interfaceTree->getIoIndex()), SIGNAL(deviceReadyLog(int, QStringList)),
                this, SLOT(deviceLogMessage(int, QStringList)));
    }
}

void ViewController::setChangedIndexDevice(int interfaceIndex, int devIndex) {
    disconnectToDevSignals();
    connectToDevSignals(); // get interface property
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceInitCommandByIndex(interfaceTree->getDevIndex());
    emit devUpdateLogMessage(2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit setActiveDeviceProperty(getDeviceFactoryByIndex(interfaceIndex)->getDeviceName(devIndex));
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    // add interace command to read current property interface
    //...
    disconnectToDevSignals();
    interfaceTreeChanged(ConnectionFactory::Type_Update_ChangedIndex);
    connectToDevSignals(); // get interface property
    emit devUpdateLogMessage(1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit interfaceSetActiveProperty(connFactory->getInterace(interfaceTree->getIoIndex())->getType());
}
