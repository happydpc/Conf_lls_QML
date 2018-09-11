#include "viewController.h"
#include <QDebug>
#include <QTime>

ViewController::ViewController(QObject *parent) : QObject(parent) {
    this->connFactory = new ConnectionFactory();

    connect(connFactory, SIGNAL(updateTree(ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType)));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        QStringList strLis;
        strLis = connFactory->getAvailableName();
        qDebug() << strLis;
        addConnectionSerialPort(strLis.first(), QString("19200"));
        addConnectionSerialPort(strLis.last(), QString("19200"));

        for(int i=0; i<1; i++) { // 15
            addDeviceToConnection("Progress tmk24", QString::number(i+1), "1234"); // tmk4UX tmk24
        }
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
        res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, name, QStringList(baudrate));
        if(res) {
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
            emit devUpdateLogMessage(0, QString("Добавление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        } else {
            emit addConnectionFail(name);
        }
    }
    return res;
}

bool ViewController::removeActiveConnectionSerialPort() {
    disconnectToDevSignals();
    getDeviceFactoryByIndex(index.interfaceIndex)->removeDeviceAll();
    connFactory->removeConnection(index.interfaceIndex);
    connectToDevSignals();
    emit devUpdateLogMessage(1, QString("Удаление интерфейса [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    return true;
}

QStringList ViewController::getAvailableDeviceNameToSerialPort() {
    QStringList retList;
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    retList = connFactory->getInterace(name)->getDeviceFactory()->getAvailableDeviceTypes();
    return retList;
}

bool ViewController::addDeviceToConnection(QString devTypeName, QString idNum, QString password) {
    bool res = false;
    Interface *pInterface = nullptr;
    // get current interface
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex));
    if(pInterface != nullptr) {     // TODO: throw!!!
        res = pInterface->getDeviceFactory()->addNewDevice(pInterface->getDeviceFactory()->getDeviceType(devTypeName), idNum, QStringList(password));
        if(res) {
            // change current device index
            index.deviceIndex = (getDeviceCount()-1);
            // make it device - "not ready"
            // while not read settings
            pInterface->getDeviceFactory()->setDeviceReInitByIndex(index.deviceIndex);
            emit devUpdateLogMessage(0, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        } else {
            emit devUpdateLogMessage(2, QString("Добавление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
            emit addDeviceFail(devTypeName);
        }
    } else {
        qDebug() << "addDevice-" << index.interfaceIndex << devTypeName <<" -ERR";
    }
    return res;
}

void ViewController::removeActiveDevice() {
    getDeviceFactoryByIndex(index.interfaceIndex)->removeDeviceByIndex(index.deviceIndex);
    emit devUpdateLogMessage(2, QString("Удаление устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

QString ViewController::getCurrentInterfaceNameToSerial() {
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    return name;
}

int ViewController::getInterfaceCount() {
    return connFactory->getCountConnection();
}


QList<int> ViewController::getCurrentDevChart() {
    QList<int> res;
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceChartByIndex(index.deviceIndex);
    return res;
}

QList<QString> ViewController::getCurrentDevOtherData() {
    QList<QString> res;
    QString name;
    name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    if(!name.isEmpty()) {
        res = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(index.deviceIndex);
    }
    return res;
}

int ViewController::getDeviceCount() {
    return connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex))
            ->getDeviceFactory()->getDeviceCount();
}

QStringList ViewController::getDeviceHeaderByIndex(int devIndex) {
    QStringList ret = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex))
            ->getDeviceFactory()->getDeviceHeaderByIndex(devIndex);
    return ret;
}

QStringList ViewController::getCurrentDevPropertyByIndex() {
    QStringList ret = connFactory->getInterace(
                connFactory->getInteraceNameFromIndex(index.interfaceIndex))->getDeviceFactory()
            ->getDevicePropertyByIndex(index.deviceIndex);
    return ret;
}

DevicesFactory* ViewController::getDeviceFactoryByIndex(int indexIterface) {
    QString interfaceName = connFactory->getInteraceNameFromIndex(indexIterface);
    return connFactory->getInterace(connFactory->getInteraceNameFromIndex(indexIterface))->getDeviceFactory();
}

bool ViewController::isCurrentDevice(QString uniqNameId) {
    if(index.interfaceIndex < connFactory->getCountConnection()) {
        if(index.deviceIndex < getDeviceCount()) {
            if(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceIdTextByIndex(index.deviceIndex) == uniqNameId) {
                return true;
            }
        }
    }
    return false;
}

void ViewController::setCurrentDevLevelAsEmpty() {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "set current level value as min", QStringList(""));
}
void ViewController::setCurrentDevLevelAsFull() {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "set current level value as max", QStringList(""));
}

void ViewController::getCurrentDevSettings() {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "get current dev settings", QStringList(""));
}

void ViewController::setCurrentDevSettings(QStringList settings) {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "set current dev settings", settings);
}

void ViewController::getCurrentDevErrors() {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "read current dev errors", QStringList(""));
}

void ViewController::getCurrentDevTarTable() {
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "read current dev tar table", QStringList(""));
}

void ViewController::setCurrentDevTarTable(QStringList values, QStringList levels) {
    QStringList table;
    int size = values.size();
    for(auto i=0; i<size; i++) {
        table.push_back(values.at(i));
        table.push_back(levels.at(i));
    }
    getDeviceFactoryByIndex(index.interfaceIndex)->sendCustomCommadToDev(index.deviceIndex, "set current dev tar table", table);
}

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
    }
    emit devUpdateLogMessage(1, QString("Получение данных с устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devReadyPropertiesTmk4ux(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devReadyPropertiesTmk24(getCurrentDevPropertyByIndex());
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
            emit devFullReadyTmk4ux(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devFullReadyTmk24(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
    emit devUpdateLogMessage(0, QString("Настройка устройста [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type) {
    if(getInterfaceCount() > 0) {
        if(index.interfaceIndex > getInterfaceCount()-1) {
            index.interfaceIndex = 0;
        }
    }
    disconnectToDevSignals();
    index.deviceIndex = 0;
    deviceTreeChanged(DevicesFactory::Type_Update_RamakeAfterChangeInterface, index.deviceIndex);

    switch(type) {
    case ConnectionFactory::Type_Update_ChangedIndex:
        emit changeInterfaceTreeStatus(index.interfaceIndex, 1);
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
        emit remakeInterfaceTree(list, status);
        break;
    }
    if(connFactory->getCountConnection() >0) {
        emit updatePropertiesSerialPort(connFactory->getInterace(index.interfaceIndex)->getInterfaceProperty());
    }
    emit devUpdateLogMessage(2, QString("Перестроение дерева интерфейсов[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    connectToDevSignals();
}

void ViewController::deviceReadyCustomCommand(int indexDev, QString message, QStringList customData) {
    DevicesFactory *pDevFactory = nullptr;
    pDevFactory = getDeviceFactoryByIndex(index.interfaceIndex);
    if(pDevFactory != nullptr) {
        switch(pDevFactory->getDeviceType(pDevFactory->getDeviceName(indexDev))) {
        case DevicesFactory::Type_Progress_Tmk24:
            if(message == "lls_calibrate_max") {
                emit devUpdateWriteScaleMeasureExecuted(pDevFactory->getDeviceName(indexDev));
            }
            if(message == "lls_calibrate_min") {
                emit devUpdateWriteScaleMeasureExecuted(pDevFactory->getDeviceName(indexDev));
            }
            if(message == "lls_read_settings") {
                emit devUpdateReadSettingExecuted(pDevFactory->getDeviceName(indexDev),
                                                  pDevFactory->getDeviceSettigns(indexDev));
            }
            if(message == "lls_read_errors") {;
                emit devUpdateReadErrorsExecuted(pDevFactory->getDeviceName(indexDev),
                                                 pDevFactory->getDeviceErrrors(indexDev));
            }
            if(message == "lls_read_cal_table") {
                emit devUpdateReadTarTable(pDevFactory->getDeviceName(indexDev), customData);
            }
            if(message == "lls_write_cal_table") {
                emit devUpdateWriteTarTableExecuted(pDevFactory->getDeviceName(indexDev));
            }
            break;
        case DevicesFactory::Type_Progress_tmk4UX:
            break;
        case DevicesFactory::Type_Undefined: break;
        }
        emit devUpdateLogMessage(2, QString("Получен ответ с команды [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
    }
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        emit changeDeviceTreeStatus(indexDev, getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(indexDev));
        break;
    case DevicesFactory::Type_Update_RamakeAfterChangeInterface:
    case DevicesFactory::Type_Update_Removed:
    case DevicesFactory::Type_Update_Added: {
        if(getInterfaceCount() > 0) {
            int count = getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceCount();
            QStringList list;
            QList<int> status;
            for(int i=0; i<count; i++) {
                list << getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(i);
                status.push_back(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(i));
            }
            emit remakeDeviceTree(list, status);
            emit devUpdateLogMessage(2, QString("Перестроение дерева устройств [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        }
    }
        break;
    case DevicesFactory::Type_Update_PasswordIncorrect:
        // внутри эвента удаляется устройство
        emit devUpdatePasswordIncorrect(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(indexDev).first());
        emit devUpdateLogMessage(2, QString("Не правильный пароль [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        break;
    case DevicesFactory::Type_Update_TypeIncorrect:
        emit devUpdateLogMessage(2, QString("Не правильный тип [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
        emit devUpdateTypeDevIncorrect(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(indexDev).first());
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
        disconnect(getDeviceFactoryByIndex(i), SIGNAL(deviceReadyCustomCommand(int,QString, QStringList)),
                   this, SLOT(deviceReadyCustomCommand(int,QString, QStringList)));
    }
}

void ViewController::connectToDevSignals() {
    if(connFactory->getCountConnection() > 0) {
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
        connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyCustomCommand(int,QString,QStringList)),
                this, SLOT(deviceReadyCustomCommand(int,QString,QStringList)));
    }
}

void ViewController::setChangedIndexDevice(int devIndex) {
    disconnectToDevSignals();
    index.deviceIndex = devIndex;
    connectToDevSignals(); // get interface property
    getDeviceFactoryByIndex(index.interfaceIndex)->setDeviceInitCommandByIndex(index.deviceIndex);
    emit devUpdateLogMessage(2, QString("Переключение устройства [%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList list;
    QList<int> status;
    // add interace command to read current property interface
    //...
    index.interfaceIndex = interfaceIndex;
    interfaceTreeChanged(ConnectionFactory::Type_Update_ChangedIndex);
    emit devUpdateLogMessage(1, QString("Переключение интерфейса[%1]").arg(QTime::currentTime().toString("HH:mm:ss")));
}
