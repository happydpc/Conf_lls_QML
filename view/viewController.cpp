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

        for(int i=0; i<2; i++) { // 15
            addDeviceToConnection("Progress tmk13", QString::number(i+1));
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
            connect(getDeviceFactoryByIndex(index.interfaceIndex),
                    SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType,int)),
                    this, SLOT(deviceTreeChanged(DevicesFactory::E_DeviceUpdateType,int)));
            setChangedIndexInteface(index.interfaceIndex);
            qDebug() << "addConnectionSerialPort -open= "<< res << name;
        }
    }
    return res;
}

// TODO: check it!
bool ViewController::removeConnectionSerialPort(QString name) {
    if(connFactory->getCountConnection() != 0) {
        disconnect(getDeviceFactoryByIndex(index.interfaceIndex),
                   SIGNAL(deviceUpdateTree(DevicesFactory::E_DeviceUpdateType)));
        connFactory->removeConnection(name);
    }
    return true;
}

QStringList ViewController::getAvailableDeviceNameToSerialPort() {
    QStringList retList;
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    retList = connFactory->getInterace(name)->getDeviceFactory()->getAvailableDeviceTypes();
    return retList;
}

bool ViewController::addDeviceToConnection(QString devTypeName, QString idNum) {
    bool res = false;
    Interface *pInterface = nullptr;
    // get current interface
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex));
    if(pInterface != nullptr) {     // TODO: throw!!!
        res = pInterface->getDeviceFactory()->addNewDevice(pInterface->getDeviceFactory()->getDeviceType(devTypeName), idNum, QStringList(""));
        if(res) {
            // change current device index
            index.deviceIndex = (getDeviceCount()-1);
            // make it device - "not ready"
            // while not read settings
            pInterface->getDeviceFactory()->setDeviceReInitByIndex(index.deviceIndex);
            // add device command to read current property device
            setChangedIndexDevice(index.deviceIndex);
        }
    } else {
        qDebug() << "addDevice-" << index.interfaceIndex << devTypeName <<" -ERR";
    }
    return res;
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
        pInterface->getDeviceFactory()->setDeviceInitCommandByIndex(index.deviceIndex);
    }
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList list;
    QList<int> status;
    // add interace command to read current property interface
    //...
    // reconnect slots
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
    emit remakeDeviceTree(list, status);
}

QString ViewController::getCurrentInterfaceNameToSerial() {
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    return name;
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
        case DevicesFactory::Type_Progress_Tmk13:
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
        case DevicesFactory::Type_Progress_Tmk13:
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
        case DevicesFactory::Type_Progress_Tmk13:
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
        case DevicesFactory::Type_Progress_Tmk13:
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
        case DevicesFactory::Type_Progress_Tmk13:
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
    case DevicesFactory::Type_Update_Added:
        int count = getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceCount();
        QStringList list;
        QList<int> status;
        for(int i=0; i<count; i++) {
            list << getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceHeaderByIndex(i);
            status.push_back(getDeviceFactoryByIndex(index.interfaceIndex)->getDeviceStatusByIndex(i));
        }
        emit remakeDeviceTree(list, status);
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
