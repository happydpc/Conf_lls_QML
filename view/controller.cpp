#include "controller.h"

//// io
//void addIoSucces(QString ioType, QStringList keyProperty, QStringList valueProperty);
//void addIoFail(QString ioType, QString ioName);
//void ioUpdateProperty(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
//void removeIoSucces(int ioIndex);
//void ioActivate(int ioIndex, QStringList keyProperty, QStringList valueProperty);
//void ioTreeIsEmpty();

//// dev
//void addDevSucces(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
//void addDeviceFail(QString devName, QString errorMessage);
//void removeDevSucces(int ioIndex, int devIndex);
//void devExecComamndReady(int ioIndex, int devIndex, QStringList keys, QStringList values);
//void devConnected(int ioIndex, int devIndex, QString typeDev);
//void devReady(int ioIndex, int devIndex, QString typeDev);
//void devDisconnected(int ioIndex, int devIndex, QString typeDev);
//void devActivateProperty(QString devType, int ioIndex, int devIndex);
//void devUpdatePeriodicData(QString devType, int ioIndex, int devIndex, QStringList keys, QStringList values);
//void devUpdateLogMessage(int ioIndex, int devIndex, QString codeMessage, QString message);
//void ioAndDeviceFullFlushData();

Controller::Controller(QObject *parent) : QObject(parent) {
    this->commandController = std::make_shared<CommandController>();
}

ModelDevTree* Controller::getIoTreeModel() {
    return &ioTreeModel;
}

QStringList Controller::getIoAddTypes(QString typeName) {
//    return peripherals->getAvailableIo(typeName);
}

bool Controller::addIo(QString ioTypeName, QString ioName, QStringList keys, QStringList values) {
    Command tcommand;
    tcommand.setDelayRequstMs(0);
//    std::shared_ptr<Command> command = std::make_shared<Command>();
//    command->setCommand("addIo");
//    keys << "ioTypeName" << "ioName";
//    values << ioTypeName << ioName;
//    command->setArgs(keys, values);
//    comma
    return true;
}

void Controller::removeIo(int ioIndex) {
//    peripherals->removeIo(ioIndex);
//    ioTreeModel.removeIo(ioIndex);
    emit removeIoSuccesSignal(ioIndex);
}

bool Controller::addDevToIo(int ioIndex, QString devTypeName, QStringList keys, QStringList param) {
//    bool res = peripherals->addDev(ioIndex, devTypeName, keys, param);
//    if(res) {
//        ioTreeModel.addDevToIo(ioIndex, devTypeName);
//        emit addDevSuccesSignal(ioIndex, devTypeName, keys, param);
//    } else {
//        emit addDevFailSignal(devTypeName, tr("Ошибка добавления устройства"));
//    }
//    return res;
}

void Controller::removeDev(int ioIndex, int devIndex) {
//    peripherals->removeDev(ioIndex, devIndex);
//    ioTreeModel.removeDevToConnection(ioIndex, devIndex);
//    emit removeDevSuccesSignal(ioIndex, devIndex);
}

QStringList Controller::getDevAddTypes() const {
//    return peripherals->getAvailableDev();
}

bool Controller::devExecCommand(int ioIndex, int devIndex, const QString commandType,
                                const QStringList keys, const QStringList params) {
//    return peripherals->devExecCommand(ioIndex, devIndex, commandType, keys, params);
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
