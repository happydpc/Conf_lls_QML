#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {
    this->peripherals = std::make_shared<Peripherals>();
    connect(&ioTreeModel, &ModelDevTree::indexIoIsChanged, peripherals.get(), &Peripherals::indexIoIsChanged);
    connect(&ioTreeModel, &ModelDevTree::indexDevIsChanged, peripherals.get(), &Peripherals::indexDevIsChanged);
}

ModelDevTree* Controller::getIoTreeModel() {
    return &ioTreeModel;
}

QStringList Controller::getIoAddTypes(QString typeName) {
    return peripherals->getAvailableIo(typeName);
}

bool Controller::addIo(QString ioTypeName, QString ioName, QStringList keys, QStringList params) {
    bool res = peripherals->addIo(ioTypeName, ioName, keys, params);
    if(res) {
        ioTreeModel.addConnection(ioName);
        auto property = peripherals->getIoProperty(ioTreeModel.getIoIndex());
        emit addIoSucces(ioTypeName, property.first, property.second);
    } else {
        emit addIoFail(ioTypeName, ioName);
    }
    return res;
}

void Controller::removeIo(int ioIndex) {
    peripherals->removeIo(ioIndex);
    ioTreeModel.removeConnection(ioIndex);
}

bool Controller::addDevToIo(int ioIndex, QString devTypeName, QStringList keys, QStringList param) {
    bool res = peripherals->addDev(ioIndex, devTypeName, keys, param);
    if(res) {
//        ioTreeModel.addDeviceToConnection(ioIndex);
    }
    return res;
}

void Controller::removeDev(int ioIndex, int devIndex) {
    peripherals->removeDev(ioIndex, devIndex);
//    ioTreeModel.removeDeviceToConnection()
}

QStringList Controller::getDevAddTypes() const {
//    return peripherals->getDevType();
}

bool Controller::devExecCommand(int ioIndex, int devIndex, const QString commandType,
                                const QStringList keys, const QStringList params) {
    return peripherals->devExecCommand(ioIndex, devIndex, commandType, keys, params);
}

QString Controller::getTypeLogo() const {
#ifdef PROGRESS
    return "progress";
#endif
#ifdef GLOSSAV
    return("gs");
#endif
    return QString();
}
