#include "viewController.h"
#include <QDebug>

//    bool res = false;
//    QStringList strLis;

ViewController::ViewController(QObject *parent) : QObject(parent) {
    this->connFactory = new ConnectionFactory();

    QTimer::singleShot(500, Qt::CoarseTimer, [&] {
        QStringList strLis;
        strLis = connFactory->getAvailableName(interfacesAbstract::InterfaceTypeSerialPort);
        qDebug() << strLis;
        bool res = false;
        addConnectionSerialPort(strLis.first(), QString("19200"));
        //    int contAvailableList = 0;
        //    while(contAvailableList != strLis.size()) {
        //        res = connFactory->addConnection(
        //                    interfacesAbstract::InterfaceTypeSerialPort, strLis.at(contAvailableList),
        //                    QStringList("9600"));
        //        qDebug() << "IsOpen = "<< res << strLis.at(contAvailableList);
        //        contAvailableList++;
        //    }
        //    int id_dev = 1;
        //    for(int i=0; i<3; i++) {
        //        //        QString nameInterface = QString("ttyACM%1").arg(i);
        //        QString nameInterface = QString("ttyACM0");
        //        Interface *pInterface = nullptr;
        //        pInterface = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, nameInterface);

        //        if(pInterface != nullptr) {
        //            res = pInterface->getDeviceFactory()->addNewDevice(
        //                        DeviceAbstract::Type_Progress_Tmk24,
        //                        QString("/%1/lls_tmk3.24_%2").arg(nameInterface).arg(i),
        //                        id_dev, QStringList(""));
        //            qDebug() << "Interface-" << nameInterface << " -open Ok";
        //        } else {
        //            qDebug() << "Interface-" << nameInterface << " -no open!";
        //        }
        //    }
    });

    this->updateCurrentDataDevTimer = new QTimer();
    connect(this->updateCurrentDataDevTimer, SIGNAL(timeout()), this, SLOT(updateCurrentDataSlot()));
    this->updateCurrentDataDevTimer->start(100);
}

QStringList ViewController::getAvailableNameToSerialPort() {
    QStringList retList;
    retList = connFactory->getAvailableName(interfacesAbstract::InterfaceTypeSerialPort);
    return retList;
}

bool ViewController::addConnectionSerialPort(QString name, QString baudrate) {
    bool res = false;
    res = connFactory->addConnection(interfacesAbstract::InterfaceTypeSerialPort, name, QStringList(baudrate));
    qDebug() << "addConnectionSerialPort -open= "<< res << name;
    if(res) {
        emit addInterfaceSignal(name, true);
    }
    return res;
}

QStringList ViewController::getAvailableDeviceNameToSerialPort() {
    QStringList retList;
    QString name = connFactory->getInteraceNameFromIndex(currentIndexInterface);
    retList = connFactory->getInterace(
                interfacesAbstract::InterfaceTypeSerialPort, name)->
            getDeviceFactory()->getAvailableDeviceTypes();
    return retList;
}

bool ViewController::addDeviceToConnection(QString devTypeName, QString idNum) {
    bool res = false;
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    QString devName = QString("%1/_%2_id=%3").arg(name).arg(devTypeName).arg(idNum);
    Interface *pInterface = nullptr;
    DeviceAbstract::E_DeviceType typeDev;
    pInterface = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name);
    if(pInterface != nullptr) {
        typeDev = pInterface->getDeviceFactory()->getDeviceTypeFromTypeCaption(devTypeName);
        res = pInterface->getDeviceFactory()->addNewDevice(typeDev, devName, idNum.toInt(), QStringList(""));
        if(res) {
            QString devNameToForm = getDeviceHeaderByIndex(getDeviceCount()-1).at(0);
            emit addDeviceSignal(devNameToForm, true);
        }
    } else {
        qDebug() << "addDevice-" << index.interfaceIndex << devTypeName <<" -ERR";
    }
    return res;
}

void ViewController::setChangedIndexDevice(int devIndex) {
    index.deviceIndex = devIndex;
    connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, index.interfaceIndex)
            ->getDeviceFactory()->addCommandDeviceReadAfterInitByIndex(index.deviceIndex);
}

void ViewController::setChangedIndexInteface(int interfaceIndex) {
    QStringList property;
    index.interfaceIndex = interfaceIndex;
    // add interace command to read current property interface
    //...
    // get interface property
    property = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, index.interfaceIndex)->getInterfaceProperty(index.interfaceIndex);
    if(!property.empty()) {
        emit updatePropertySerialPort_Signal(ret);
    }
}

QString ViewController::getCurrentInterfaceNameToSerial() {
    QString name = connFactory->getInteraceNameFromIndex(index.interfaceIndex);
    return name;
}

QList<int> ViewController::getCurrentDevChart() {
    QList<int> res;
    QString name = connFactory->getInteraceNameFromIndex(currentDeviceIndex);
    res = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name)
            ->getDeviceFactory()->getDeviceChartByIndex(currentDeviceIndex);
    return res;
}

QList<QString> ViewController::getCurrentDevOtherData() {
    QList<QString> res;
    QString name;
    name = connFactory->getInteraceNameFromIndex(currentDeviceIndex);
    if(!name.isEmpty()) {
        res = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name)
                ->getDeviceFactory()->getDeviceCurrentDataByIndex(currentDeviceIndex);
    }
    return res;
}

int ViewController::getDeviceCount() {
    int ret = 0;
    QString name = connFactory->getInteraceNameFromIndex(currentIndexInterface);
    ret = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name)->getDeviceFactory()->getDeviceCount();
    return ret;
}

QStringList ViewController::getDeviceHeaderByIndex(int index) {
    QStringList ret;
    QString name = connFactory->getInteraceNameFromIndex(currentIndexInterface);
    ret = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name)->getDeviceFactory()->getDeviceHeaderByIndex(index);
    return ret;
}

QStringList ViewController::getCurrentDevPropertyByIndex() {
    QStringList ret;
    ret = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, connFactory->getInteraceNameFromIndex(currentIndexInterface))
            ->getDeviceFactory()->getDeviceCurrentPropertyByIndex(currentDeviceIndex);
    ret.push_front(connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, connFactory->getInteraceNameFromIndex(currentIndexInterface))
                   ->getDeviceFactory()->getDeviceTypeByIndex(currentDeviceIndex));
    return ret;
}

void ViewController::updateCurrentDataSlot() {
    QStringList ret;
    if(connFactory->getCountConnection() >0) {
        QString name = connFactory->getInteraceNameFromIndex(currentIndexInterface);
        if(!name.isEmpty()) {
            ret = connFactory->getInterace(interfacesAbstract::InterfaceTypeSerialPort, name)->getDeviceFactory()->getDeviceCurrentPropertyByIndex(currentDeviceIndex);
            emit updateCurrentDataDevTmk24_Signal(ret);
        }
    }
}



void ViewController::connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface) {
    //        connect(connFactory,
    //                SIGNAL(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString)),
    //                SLOT(connectionIsLost(interfacesAbstract::eInterfaceTypes, QString))
    //                );
}
