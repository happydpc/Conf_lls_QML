#include "viewController.h"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent) {
    this->connFactory = new ConnectionFactory();

    connect(connFactory, SIGNAL(updateTree(ConnectionFactory::E_ConnectionUpdateType)),
            this, SLOT(interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType)));

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        QStringList strLis;
        strLis = connFactory->getAvailableName();
        qDebug() << strLis;
        addConnectionSerialPort(strLis.first(), QString("19200"));

        for(int i=0; i<5; i++) { // 15
            addDeviceToConnection("Progress tmk4UX", QString::number(i+1), "1234"); // tmk4UX tmk24
        }
    });
}

QStringList ViewController::getAvailableNameToSerialPort() {
    QStringList retList;
    retList = connFactory->getAvailableName();
    return retList;
}

bool ViewController::addConnectionSerialPort(QString name, QString baudrate) {
    bool res = false;
    if((!name.isEmpty()) && (!baudrate.isEmpty())) {
        res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, name, QStringList(baudrate));
        if(res) {
            if(getDeviceCount() >0) {
                index.interfaceIndex = (getDeviceCount()-1);
            }
            connect(getDeviceFactoryByIndex(index.interfaceIndex),
                    SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                    this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
            setChangedIndexInteface(index.interfaceIndex);
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
        } else {
            emit addConnectionFail(name);
        }
    }
    return res;
}

// TODO: check it!
bool ViewController::removeActiveConnectionSerialPort() {
    if(getInterfaceCount() > 0) {
        disconnect(getDeviceFactoryByIndex(index.interfaceIndex),
                   SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType)));
        getDeviceFactoryByIndex(index.interfaceIndex)->removeDeviceAll();
        connFactory->removeConnection(index.interfaceIndex);
        setChangedIndexInteface(index.interfaceIndex);
    }
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
            // add device command to read current property device
            setChangedIndexDevice(index.deviceIndex);
        } else {
            emit addDeviceFail(devTypeName);
        }
    } else {
        qDebug() << "addDevice-" << index.interfaceIndex << devTypeName <<" -ERR";
    }
    return res;
}

void ViewController::removeActiveDevice() {
    getDeviceFactoryByIndex(index.interfaceIndex)->removeDeviceByIndex(index.deviceIndex);
    if(getDeviceCount() > 0) {
        if((index.deviceIndex > 0) && (index.deviceIndex <= getDeviceCount())) {
            index.deviceIndex--;
        } else {
            index.deviceIndex = 0;
            setChangedIndexInteface(index.interfaceIndex);
        }
    } else {
        index.deviceIndex = 0;
        setChangedIndexInteface(index.interfaceIndex);
    }
    setChangedIndexDevice(index.deviceIndex);
}

void ViewController::setChangedIndexDevice(int devIndex) {
    Interface *pInterface = nullptr;
    // reconnect slots
    disconnectToDevSignals();
    index.deviceIndex = devIndex;
    connectToDevSignals();
    // get interface property
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex));
    if(pInterface != nullptr) {     // TODO: its throw exeption!!!
        if(pInterface->getDeviceFactory()->getDeviceCount() != 0) {
            pInterface->getDeviceFactory()->setDeviceInitCommandByIndex(index.deviceIndex);
        }
    }
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList list;
    QList<int> status;
    // add interace command to read current property interface
    //...
    // reconnect slots
    if(getInterfaceCount() > 0) {
        disconnectToDevSignals();
        index.interfaceIndex = interfaceIndex;
        connectToDevSignals();
        // get interface property
        emit updatePropertiesSerialPort(connFactory->getInterace(index.interfaceIndex)->getInterfaceProperty());
        //
        int count = getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceCount();
        for(int i=0; i<count; i++) {
            list << getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(i);
            status.push_back(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(i));
        }
    }
    emit remakeDeviceTree(list, status);
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
    name = connFactory->getInteraceNameFromIndex(index.deviceIndex);
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
    ret.push_front(connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex))->
                   getDeviceFactory()->getDeviceName(index.deviceIndex));
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

void ViewController::deviceConnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devConnectedTmk13();
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devConnectedTmk24();
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}
void ViewController::deviceDisconnected(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devDisconnectedTmk13();
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devDisconnectedTmk24();
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}
void ViewController::deviceReadyCurrentData(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devReadyOtherDataTmk13(getCurrentDevOtherData());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devReadyOtherDataTmk24(getCurrentDevOtherData());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}
void ViewController::deviceReadyProperties(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devReadyPropertiesTmk13(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devReadyPropertiesTmk24(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}
void ViewController::deviceReadyInit(DevicesFactory::E_DeviceType type, QString uniqNameId) {
    if(isCurrentDevice(uniqNameId)) {
        switch(type) {
        case DevicesFactory::Type_Progress_tmk4UX:
            emit devFullReadyTmk13(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Progress_Tmk24:
            emit devFullReadyTmk24(getCurrentDevPropertyByIndex());
            break;
        case DevicesFactory::Type_Undefined: break;
        }
    }
}

void ViewController::interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type) {
    switch(type) {
    case ConnectionFactory::Type_Update_Add:
    case ConnectionFactory::Type_Update_Removed: {
        int count = connFactory->getCountConnection();
        QStringList list;
        QList<int> status;
        for(int i=0; i<count; i++) {
            list << connFactory->getInterace(i)->getInterfaceName();
            // TODO: status interface
            status.push_back(1);
        }
        emit remakeInterfaceTree(list, status);
    }
        break;
    }
}

void ViewController::deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int indexDev) {
    switch(type) {
    case DevicesFactory::Type_Update_ChangeStatus:
        emit changeDeviceTreeStatus(indexDev, getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(indexDev));
        break;
    case DevicesFactory::Type_Update_Removed:
    case DevicesFactory::Type_Update_Added: {
        int count = getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceCount();
        QStringList list;
        QList<int> status;
        for(int i=0; i<count; i++) {
            list << getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(i);
            status.push_back(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(i));
        }
        emit remakeDeviceTree(list, status);
    }
        break;
    case DevicesFactory::Type_Update_PasswordIncorrect: {
//        emit devUpdatePasswordIncorrect(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(indexDev).first());
        // удаляем устройство
        removeActiveDevice();
    }
    case DevicesFactory::Type_Update_TypeIncorrect: {
//        emit devUpdateTypeDevIncorrect(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(indexDev).first());
        // удаляем устройство
//        removeActiveDevice();
    }
        break;
    }
}

void ViewController::disconnectToDevSignals() {
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
    disconnect(getDeviceFactoryByIndex(index.interfaceIndex),
               SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
               this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
}

void ViewController::connectToDevSignals() {
    connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceConnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceConnected(DevicesFactory::E_DeviceType,QString)));
    connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceDisconnectedSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceDisconnected(DevicesFactory::E_DeviceType,QString)));
    connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyCurrentDataSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyCurrentData(DevicesFactory::E_DeviceType,QString)));
    connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyInitSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyInit(DevicesFactory::E_DeviceType,QString)));
    connect(getDeviceFactoryByIndex(index.interfaceIndex), SIGNAL(deviceReadyPropertiesSignal(DevicesFactory::E_DeviceType,QString)), this, SLOT(deviceReadyProperties(DevicesFactory::E_DeviceType,QString)));
    connect(getDeviceFactoryByIndex(index.interfaceIndex),
            SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
            this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
}
