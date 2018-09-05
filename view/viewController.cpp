#include "viewController.h"
#include <QDebug>

ViewController::ViewController(QObject *parent) : QObject(parent) {
    this->connFactory = new ConnectionFactory();

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        QStringList strLis;
        strLis = connFactory->getAvailableName();
        qDebug() << strLis;
        bool res = false;
        addConnectionSerialPort(strLis.first(), QString("19200"));
    });

    this->updateCurrentDataDevTimer = new QTimer();
    connect(this->updateCurrentDataDevTimer, SIGNAL(timeout()), this, SLOT(updateCurrentDataSlot()));
    this->updateCurrentDataDevTimer->start(500);
}

QStringList ViewController::getAvailableNameToSerialPort() {
    QStringList retList;
    retList = connFactory->getAvailableName();
    return retList;
}

bool ViewController::addConnectionSerialPort(QString name, QString baudrate) {
    bool res = false;
    res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, name, QStringList(baudrate));
    qDebug() << "addConnectionSerialPort -open= "<< res << name;
    if(res) {
        emit addInterfaceSignal(name, true);
        setChangedIndexInteface(index.interfaceIndex);
    }
    return res;
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
            pInterface->getDeviceFactory()->setDeviceAsNotReadyByIndex(index.deviceIndex);
            // update new device event
            emit addDeviceSignal(getDeviceHeaderByIndex(index.deviceIndex).at(0), true);
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
    pInterface = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex));
    if(pInterface != nullptr) {     // TODO: its throw exeption!!!
        index.deviceIndex = devIndex;
        pInterface->getDeviceFactory()->setDeviceInitCommandByIndex(index.deviceIndex);
    }
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList property;
    index.interfaceIndex = interfaceIndex;
    // add interace command to read current property interface
    //...
    // get interface property
    property = connFactory->getInterace(index.interfaceIndex)->getInterfaceProperty();
    if(!property.empty()) {
        emit updatePropertiesSerialPort_Signal(property);
    }
}

QString ViewController::getCurrentInterfaceNameToSerial() {
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    return name;
}

QList<int> ViewController::getCurrentDevChart() {
    QList<int> res;
    QString name = connFactory->getInteraceNameFromIndex(index.deviceIndex);
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
    int ret = connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex))
            ->getDeviceFactory()->getDeviceCount();
    return ret;
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

void ViewController::updateCurrentDataSlot() {
    QStringList ret;
    DevicesFactory::E_DeviceType type = DevicesFactory::Type_Undefined;
    if(connFactory->getCountConnection() >0) {
        if(connFactory->getInterace(connFactory->getInteraceNameFromIndex(index.interfaceIndex))->getDeviceFactory()->getDeviceCount() >0) {
            QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
            if(!name.isEmpty()) {
                type = connFactory->getInterace(name)->
                        getDeviceFactory()->getDeviceType(index.deviceIndex);
                if(connFactory->getInterace(name)->getDeviceFactory()->
                        getDevStateByIndex(index.deviceIndex) == DeviceAbstract::STATE_NORMAL_READY) {
                    ret = connFactory->getInterace(name)->getDeviceFactory()->getDeviceCurrentDataByIndex(index.deviceIndex);
                    if(!ret.isEmpty()) {
                        switch(type) {
                        case DevicesFactory::Type_Progress_Tmk13:
                            emit updateDataDevTmk13_Signal(ret);
                            break;
                        case DevicesFactory::Type_Progress_Tmk24:
                            emit updateDataDevTmk24_Signal(ret);
                            break;
                        case DevicesFactory::Type_Undefined:
                            qDebug() << "Update current data - Type_Undefined";
                            break;
                        }
                    } else {
                        qDebug() << "Update current data - result=" << ret;
                    }
                } else {
                    switch(type) {
                    case DevicesFactory::Type_Progress_Tmk13:
//                        emit updateDevTmk13_NoReady_Signal();
                        break;
                    case DevicesFactory::Type_Progress_Tmk24:
//                        emit updateDevTmk24_NoReady_Signal();
                        break;
                    case DevicesFactory::Type_Undefined:
                        qDebug() << "Update current data - Type_Undefined";
                        break;
                    }
                }
            }
        }
    }
}

void ViewController::connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface) {
    //        connect(connFactory,
    //                SIGNAL(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString)),
    //                SLOT(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString))
    //                );
}
