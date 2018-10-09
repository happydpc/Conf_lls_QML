#include "viewController.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include "device/Progress_TMK24/Progress_tmk24.h"
#include "device/Progress_TMK4UX/Progress_tmk4UX.h"
#include "device/Nozzle_Revision_0_00_Oct_2018/Nozzle_Revision_0_00_Service.h"

ViewController::ViewController(Model *pInterfaceModel, QObject *parent) : QObject(parent) {

    this->connFactory = new ConnectionFactory();

    this->interfaceTree = pInterfaceModel;

    connect(connFactory, SIGNAL(updateTree(ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType)));

    // TODO: the service need and necessery for other action
    this->serviceList.push_back(new Progress_tmk24Service("PROGRESS TMK24"));
    this->serviceList.push_back(new Nozzle_Rev_0_00_Service("Nozzle Revision 0.00 Oct 2018"));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        QStringList strLis;
        strLis = connFactory->getAvailableName();
        qDebug() << strLis;

        addConnectionSerialPort("ttyACM0", QString("115200"));
        addDeviceToConnection("Nozzle Revision 0.00 Oct 2018", QString::number(0), "");

//        addDeviceToConnection("PROGRESS TMK24", QString::number(1), "");
//        addDeviceToConnection("PROGRESS TMK24", QString::number(2), "");

//        for(int a=0; a<2; a++) {
//            addDeviceToConnection("PROGRESS TMK24", QString::number(a+5), "");
            //            addTarrirDev("PROGRESS TMK24", QString::number(a+5));
//        }
    });
}

QStringList ViewController::getAvailableNameToSerialPort() {
    QStringList retList;
    retList = connFactory->getAvailableName();
    emit devUpdateLogMessage(0, QString("Получение списка интерфейсов [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    return retList;
}

bool ViewController::addConnectionSerialPort(QString name, QString baudrate) {
    bool res = false;
    if((!name.isEmpty()) && (!baudrate.isEmpty())) {
        res = connFactory->addConnection("Serial", name, QStringList(baudrate));
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
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->removeDeviceAll();
    connFactory->removeConnection(interfaceTree->getIoIndex());
    connectToDevSignals();
    emit devUpdateLogMessage(1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    interfaceTree->removeConnection(interfaceTree->getIoIndex());
    if(getInterfaceCount() == 0) {
        emit interfaceAndDeviceListIsEmpty();
    }
}

void ViewController::removeActiveDevice() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->removeDeviceByIndex(interfaceTree->getDevIndex());
    emit devUpdateLogMessage(2, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    interfaceTree->removeDeviceToConnection(interfaceTree->getIoIndex(), interfaceTree->getDevIndex());
    interfaceTree->setDevIndex(0);
}

QStringList ViewController::getAvailableDeviceNameToSerialPort() {
    QStringList retList;
    QString name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        InterfaceSerial* pSerial = dynamic_cast<InterfaceSerial*>(connFactory->getInterace(name));
        pSerial->getDeviceFactory()->getAvailableDeviceTypes();
        retList = connFactory->getInterace(name)->getDeviceFactory()->getAvailableDeviceTypes();
    }
    return retList;
}

bool ViewController::addDeviceToConnection(QString devTypeName, QString idNum, QString password) {
    bool res = false;
    interfacesAbstract *pInterface = nullptr;
    // get current interface
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()));
    if(pInterface != nullptr) {     // TODO: throw!!!
        for(auto it:serviceList) {
            if(it->getTypeOwnDeviceName() == devTypeName) {
                res = pInterface->getDeviceFactory()->addNewDevice(pInterface->getDeviceFactory()->getDeviceType(devTypeName), idNum, QStringList(password), it);
                if(res) {
                    // change current device index
                    interfaceTree->setDevIndex((getDeviceCount()-1));
                    interfaceTree->addDeviceToConnection(getCurrentInterfaceNameToSerial(), getDeviceHeaderByIndex(interfaceTree->getDevIndex()).first(), false);//
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
    } else {
        qDebug() << "addDevice-" << interfaceTree->getIoIndex() << devTypeName <<" -ERR";
    }
    return res;
}

QString ViewController::getCurrentInterfaceNameToSerial() {
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

QList<QString> ViewController::getCurrentDevOtherData() {
    QList<QString> res;
    QString name;
    name = connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex());
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(interfaceTree->getDevIndex());
    }
    return res;
}

int ViewController::getDeviceCount() {
    return connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))
            ->getDeviceFactory()->getDeviceCount();
}

QStringList ViewController::getDeviceHeaderByIndex(int devIndex) {
    QStringList ret = connFactory->getInterace(connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))
            ->getDeviceFactory()->getDeviceHeaderByIndex(devIndex);
    return ret;
}

QStringList ViewController::getCurrentDevProperty() {
    QStringList ret = connFactory->getInterace(
                connFactory->getInteraceNameFromIndex(interfaceTree->getIoIndex()))->getDeviceFactory()
            ->getDevicePropertyByIndex(interfaceTree->getDevIndex());
    return ret;
}

void ViewController::setCurrentDevNewIdAddress(QString newId, QString password, QString currentId) {

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

void ViewController::setCurrentDevLevelAsEmpty() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current level value as min");
}
void ViewController::setCurrentDevLevelAsFull() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current level value as max");
}

void ViewController::getCurrentDevSettingsWithoutRequest() {
    emit devUpdateReadSettingWithoutRequest("",
                                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).first,
                                            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceSettigns(interfaceTree->getDevIndex()).second);
}

void ViewController::getCurrentDevSettings() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "get current dev settings");
}

void ViewController::setCurrentDevSettings(QStringList key, QStringList settingsValues) {
    QPair<QStringList,QStringList> settings;
    int counter = 0;
    for(auto it:key) {
        settings.first.push_back(it);
        settings.second.push_back(settingsValues.at(counter));
        counter++;
    }
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "set current dev settings", settings);
}

void ViewController::getCurrentDevErrors() {
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "read current dev errors");
}

#include <QJsonDocument>

//************************************************************************/
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
            getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(
                        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(i), "set current dev tar table", table);
        }
    }
}

void ViewController::setCurrentDevChangeId(QString password, QString uniqNameIdNew, QString uniqNameIdCurrent) {
    QPair<QStringList,QStringList> id;
    id.first.push_back("netAddress_value");
    id.second.push_back(uniqNameIdNew);
    if((getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceProperty(interfaceTree->getDevIndex()).at(5) == password)
            && (uniqNameIdNew.toInt() > 0)) {
        getDeviceFactoryByIndex(interfaceTree->getIoIndex())->sendCustomCommadToDev(interfaceTree->getDevIndex(), "change current dev id", id);
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
            resList << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDevicePropertyByIndex(i).at(0); // sn
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

DeviceAbstract* ViewController::getCurrentDeviceToAbstract() {
    return getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(interfaceTree->getDevIndex());
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

//************************************************************************/
//**                        SECURITY, PROPERTYES                        **/
//************************************************************************/
void ViewController::deviceConnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devConnectedTmk4ux();
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devConnectedTmk24();
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
            emit devDisconnectedTmk4ux();
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devDisconnectedTmk24();
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(2, QString("Устройство потеряно [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyCurrentData(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devReadyOtherDataTmk4ux(getCurrentDevOtherData());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devReadyOtherDataTmk24(getCurrentDevOtherData());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
        emit devUpdateLogMessage(1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    }

    int devIndex = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->findDeviceIndex(uniqNameId);
    if(devIndex >= 0) {
        Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(
                    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceToDeviceAbstract(devIndex)->getServiceAbstract());
        pService->placeCurrenDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCurrentDataByIndex(devIndex));
        pService->placeCurrentChartDataFromDevice(uniqNameId, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceChartByIndex(devIndex));
    }
}
void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devReadyPropertiesTmk4ux(getCurrentDevProperty());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devReadyPropertiesTmk24(getCurrentDevProperty());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(0, QString("Получение информации с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyInit(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devFullReadyTmk4ux(getCurrentDevProperty());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devFullReadyTmk24(getCurrentDevProperty());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(0, QString("Настройка устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type) {
    disconnectToDevSignals();
    interfaceTree->setDevIndex(0);
    if(getInterfaceCount() > 0) {
        if(interfaceTree->getIoIndex() > getInterfaceCount()-1) {
            interfaceTree->setIoIndex(0);
        }
    }
    deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, interfaceTree->getDevIndex());

    switch(type) {
    case ConnectionFactory::Type_Update_ChangedIndex:
        //        emit changeInterfaceTreeStatus(interfaceTree->getIoIndex(), 1);
        break;
    case ConnectionFactory::Type_Update_Add:
    case ConnectionFactory::Type_Update_Removed:
        int count = connFactory->getCountConnection();
        QStringList list;
        QList<int> status;
        for(int i=0; i<count; i++) {
            list << connFactory->getInterace(i)->getInterfaceName();
            // TODO: status interface
            status.push_back(1);
        }
        break;
    }
    if(connFactory->getCountConnection() >0) {
        emit updatePropertiesSerialPort(connFactory->getInterace(interfaceTree->getIoIndex())->getInterfaceProperty());
    }
    emit devUpdateLogMessage(2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    connectToDevSignals();
}

void ViewController::deviceReadyCustomCommand(int indexDev, QString message, QStringList customData, CommandController::sCommandData commmandData) {
    DevicesFactory *pDevFactory = nullptr;
    pDevFactory = getDeviceFactoryByIndex(interfaceTree->getIoIndex());

    emit devUpdateLogMessage(2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));

    if(pDevFactory != nullptr) {
        switch(pDevFactory->getDeviceType(pDevFactory->getDeviceName(indexDev))) {
        case DevicesFactory::Type_Progress_Tmk24:
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_max) {
                if(commmandData.isNeedAckMessage) {
                    if (message == "Normal") {
                        emit devUpdateWriteScaleMeasureExecuted(pDevFactory->getDeviceName(indexDev));
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_calibrate_min) {
                if(commmandData.isNeedAckMessage) {
                    if (message == "Normal") {
                        emit devUpdateWriteScaleMeasureExecuted(pDevFactory->getDeviceName(indexDev));
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_settings) {
                if(commmandData.isNeedAckMessage) {
                    if (message == "Normal") {
                        emit devUpdateReadSettingExecuted(pDevFactory->getDeviceName(indexDev),           // devName
                                                          pDevFactory->getDeviceSettigns(indexDev).first, // key
                                                          pDevFactory->getDeviceSettigns(indexDev).second); // value
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_errors) {
                if(commmandData.isNeedAckMessage) {
                    if (message == "Normal") {
                        emit devUpdateReadErrorsExecuted(pDevFactory->getDeviceName(indexDev),
                                                         pDevFactory->getDeviceErrrors(indexDev));
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_read_cal_table) {
                if(commmandData.isNeedAckMessage) {
                    Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                    pService->placeTableFromDevice(commmandData.deviceIdent, customData);
                    if(pService->readTableAllDeviceIsReady()) {
                        emit devUpdateReadTarTable(pService->getDeviceCount());

                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_write_cal_table) {
                if(commmandData.isNeedAckMessage) {
                    Progress_tmk24Service* pService = dynamic_cast<Progress_tmk24Service*>(pDevFactory->getDeviceToDeviceAbstract(indexDev)->getServiceAbstract());
                    pService->placeAckReplyOfWriteTableFromDevice(commmandData.deviceIdent, (message == "Normal" ? (true) : (false)));
                    if(pService->readTableAllDeviceIsReady()) {
                        QStringList resWrite;
                        for(int index=0; index<pService->getDeviceCount(); index++) {
                            resWrite << QString("\nID%1 [%2][SN-%3]   статус - %4").arg(commmandData.deviceIdent)
                                        .arg(pService->getDeviceProperty(index).at(0))
                                        .arg(pService->getDeviceProperty(index).at(2))
                                        .arg(message == QString("Normal") ? QString("Успешно записано") :
                                                                   (message == QString("Data no valid") ? (QString("Устройство отвергло данные")) : QString("Нет ответа")));
                        }
                        emit devUpdateWriteTarTableExecuted(resWrite);
                    }
                }
            }
            if(commmandData.devCommand == Progress_tmk24Data::lls_write_settings) {
                if(commmandData.isNeedAckMessage) {
                    if(message == "Error") {
                        emit devUpdateWriteSettingExecuted(pDevFactory->getDeviceName(indexDev));
                    } else if (message == "Normal") {
                        emit devUpdateWriteSettingExecuted(pDevFactory->getDeviceName(indexDev));
                    }
                }
            }
            break;
        case DevicesFactory::Type_Progress_tmk4UX:
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        interfaceTree->setDevStatusByIndex(indexDev, getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceStatusByIndex(indexDev));
        break;
    case DevicesFactory::Type_Update_RamakeAfterChangeInterface:
    case DevicesFactory::Type_Update_Removed:
    case DevicesFactory::Type_Update_Added: {
        if(getInterfaceCount() > 0) {
            int count = getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceCount();
            QStringList list;
            QList<int> status;
            for(int i=0; i<count; i++) {
                list << getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeaderByIndex(i);
                status.push_back(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceStatusByIndex(i));
            }
            emit devUpdateLogMessage(2, QString("Перестроение дерева устройств [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        }
    }
        break;
    case DevicesFactory::Type_Update_PasswordIncorrect:
        emit devUpdatePasswordIncorrect(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceName(indexDev), getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeaderByIndex(indexDev).first());
        emit devUpdateLogMessage(2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    case DevicesFactory::Type_Update_TypeIncorrect:
        emit devUpdateLogMessage(2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit devUpdateTypeDevIncorrect(getDeviceFactoryByIndex(interfaceTree->getIoIndex())->getDeviceHeaderByIndex(indexDev).first());
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
    }
}

void ViewController::setChangedIndexDevice(int interfaceIndex, int devIndex) {
    disconnectToDevSignals();
    interfaceTree->setDevIndex(devIndex);
    interfaceTree->setIoIndex(interfaceIndex);
    connectToDevSignals(); // get interface property
    getDeviceFactoryByIndex(interfaceTree->getIoIndex())->setDeviceInitCommandByIndex(interfaceTree->getDevIndex());
    emit devUpdateLogMessage(2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit setActiveDeviceProperty(QString(getCurrentDevProperty().at(0)).toLower());
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList list;
    QList<int> status;
    // add interace command to read current property interface
    //...
    disconnectToDevSignals();
    interfaceTree->setIoIndex(interfaceIndex);
    interfaceTree->setDevIndex(0);
    interfaceTreeChanged(ConnectionFactory::Type_Update_ChangedIndex);
    connectToDevSignals(); // get interface property
    emit devUpdateLogMessage(1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    emit setActivePropertySerialPort();
}
