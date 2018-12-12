#include "controller.h"
#include "other/convert.h"
#include <stdio.h>
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent) {
    this->ioTreeModel = std::make_shared<ModelDevTree>();
    this->commandController = std::make_shared<CommandController>();
    this->ioTreeThread = std::make_shared<std::thread>(
                Controller::ioTreeHandlerFunction, ioTreeModel, commandController);
}

/*
 * Function:  requestGetIoAddTypes
 * --------------------
 * send request to command hanbler:
 * as reply get signal
 * why give list available ioTypes
 *
 *  ioTypeName: type interfaces (for instance - serial)
 *
 *  returns: non
 */
void Controller::ioTreeHandlerFunction(std::shared_ptr<ModelDevTree> ioTreeModel,
            std::shared_ptr<CommandController> commandController) {
    QVector<QString> keys, values;
    Command command;
    Convert convert;
    while(1) {
        command.setCommand("getIoStatus");
        keys.push_back("ioIndex");
        values.push_back(ioTypeName);
        command.setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
        auto handler = commandController->addCommandToStack(std::move(command));
        auto p = handler.get();
        if(p != nullptr) {
            emit signal_get_availableIo(convert.convertStdVectorToQt(p->getResult().first),
                                        convert.convertStdVectorToQt(p->getResult().second));
        }

        commandController->addCommandToStack()
        if(ioTreeModel->)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

/*
 * Function:  requestGetIoAddTypes
 * --------------------
 * send request to command hanbler:
 * as reply get signal
 * why give list available ioTypes
 *
 *  ioTypeName: type interfaces (for instance - serial)
 *
 *  returns: non
 */
void Controller::requestGetIoAddTypes(QString ioTypeName) {
    QVector<QString> keys, values;
    Command command;
    Convert convert;
    command.setCommand("requestGetIoAddTypes");
    keys.push_back("ioTypeName");
    values.push_back(ioTypeName);
    command.setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    auto handler = commandController->addCommandToStack(std::move(command));
    auto p = handler.get();
    if(p != nullptr) {
        emit signal_get_availableIo(convert.convertStdVectorToQt(p->getResult().first),
                                    convert.convertStdVectorToQt(p->getResult().second));
    }
}

/*
 * Function:  requestAddIo
 * --------------------
 * send request to command hanbler:
 * create interface
 *
 *  ioTypeName: type interfaces (for instance - serial)
 *  ioName (name interface, for instane - COM1)
 *  keys, values - parameters
 *
 *  returns: non
 */
void Controller::requestAddIo(QString ioTypeName, QString ioName, QVector<QString> keys, QVector<QString> values) {
    Command command;
    Convert convert;
    command.setCommand("addIo");
    keys.push_front("ioTypeName");
    keys.push_front("ioName");
    values.push_front(ioTypeName);
    values.push_front(ioName);
    command.setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    auto handler = commandController->addCommandToStack(std::move(command));
    auto p = handler.get();
    if(p != nullptr) {
        ioTreeModel->addIo(ioName);
        emit signal_add_Io(convert.convertStdVectorToQt(p->getResult().first),
                           convert.convertStdVectorToQt(p->getResult().second));
    }
}

/*
 * Function:  requestRemoveIo
 * --------------------
 * send request to command hanbler:
 * remove interface
 *
 *  ioIndex: index interfaces, from ioTree (for instance - 0-1-9)
 *
 *  returns: non
 */
void Controller::requestRemoveIo(int ioIndex) {
//    Command command;
//    std::vector<QString> keys, values;
//    command.setCommand("removeIo");
//    keys.push_back("ioIndex");
//    values.push_back(QString::number(ioIndex));
//    command.setArgs(keys, values);
//    auto handler = commandController->addCommandToStack(std::move(command));
//    auto p = handler.get();
//    if(p != nullptr) {
//        ioTreeModel.addIo(ioName);
//        peripherals->removeIo(ioIndex);
//        ioTreeModel.removeIo(ioIndex);
//        emit removeIoSuccesSignal(ioIndex);
//        emit signal_add_Io(QVector<QString>::fromStdVector(p->getResult().first),
//                           QVector<QString>::fromStdVector(p->getResult().second));
//    }
}

/*
 * Function:  requestAddDevToIo
 * --------------------
 * send request to command hanbler:
 * create interface
 *
 *  ioIndex: index interfaces, from ioTree (for instance - 0-1-9)
 *  devTypeName: type dev name (for instance - PROGRESS TMK24)
 *  keys, values: - parameters
 *
 *  returns: non
 */
void Controller::requestAddDevToIo(int ioIndex, QString devTypeName, QVector<QString> keys, QVector<QString> values) {
    Command command;
    Convert convert;
    command.setCommand("requestAddDevToIo");
    keys.push_back("ioIndex");
    keys.push_back("devTypeName");
    values.push_back(QString::number(ioIndex));
    values.push_back(devTypeName);
    command.setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    auto handler = commandController->addCommandToStack(std::move(command));
    auto p = handler.get();
    if(p != nullptr) {
        ioTreeModel->addDevToIo(ioIndex, QString::fromStdString(p->getResult().first.front()));
        emit signal_add_dev_to_Io(convert.convertStdVectorToQt(p->getResult().first),
                           convert.convertStdVectorToQt(p->getResult().second));
    }
}

/*
 * Function:  requestRemoveDev
 * --------------------
 * send request to command hanbler:
 * create interface
 *
 *  ioIndex: index interfaces, from ioTree (for instance - 0-1-9)
 *  devIndex: index device from tree
 *
 *  returns: non
 */
void Controller::requestRemoveDev(int ioIndex, int devIndex) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    Convert convert;
    QVector<QString> keys, values;
    command->setCommand("addDevToIo");
    keys.push_back("ioIndex");
    keys.push_back("devIndex");
    values.push_back(QString::number(ioIndex));
    values.push_back(QString::number(devIndex));
    command->setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    commandController->addCommandToStack(*command.get());
}

/*
 * Function:  requestRemoveDev
 * --------------------
 * send request to command hanbler:
 * get available types device
 *
 *  returns: non
 */
void Controller::requestGetDevAddTypes() {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    QVector<QString> keys, values;
    Convert convert;
    command->setCommand("getDevAddTypes");
    keys.push_back("getDevAddTypes");
    values.push_back("getDevAddTypes");
    command->setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    commandController->addCommandToStack(*command.get());
}

/*
 * Function:  requestRemoveDev
 * --------------------
 * send request to command hanbler:
 * send custom command to device
 *
 *  ioIndex: index interfaces, from ioTree (for instance - 0-1-9)
 *  devIndex: index device from tree
 *  commandType: type device comand
 *  keys, values: - parameters
 *
 *  returns: non
 */
void Controller::requestDevExecCommand(int ioIndex, int devIndex, const QString commandType,
                                       QVector<QString> keys, QVector<QString> values) {
    std::shared_ptr<Command> command = std::make_shared<Command>();
    Convert convert;
    command->setCommand("devExecCommand");
    keys.push_back("ioIndex");
    keys.push_back("devIndex");
    keys.push_back("commandType");
    values.push_back(QString::number(ioIndex));
    values.push_back(QString::number(devIndex));
    values.push_back(commandType);
    command->setArgs(convert.convertQtToStd(keys), convert.convertQtToStd(values));
    commandController->addCommandToStack(*command.get());
}

/*
 * Function:  requestRemoveDev
 * --------------------
 * give current logo path
 *
 *  returns: logo path
 */
QString Controller::getTypeLogo() const {
#ifdef PROGRESS
    return "progress";
#endif
#ifdef GLOSSAV
    return("gs");
#endif
    return QString();
}

/*
 * Function:  requestRemoveDev
 * --------------------
 * give model ioTree for qml
 *
 *  returns: point model
 */
ModelDevTree* Controller::getIoTreeModel() {
    return ioTreeModel.get();
}
