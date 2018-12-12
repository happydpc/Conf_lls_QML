#include "commandinterpretator.h"
#include "view/peripherals.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

CommandInterpretator::CommandInterpretator(Peripherals* peripherals) {
    this->peripherals = peripherals;
}

Command& CommandInterpretator::requestGetIoAddTypes(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue = peripherals->getAvailableIo(command.getArgs().second.front());
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

Command& CommandInterpretator::requestAddIo(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    resKey.push_back(command.getCommand());
    bool resBool = peripherals->addIo(command.getArgs().first, command.getArgs().second);
    resValue.push_back(std::to_string(resBool ? 1 : 0));
    resKey.push_back("ioTypeName");
    resValue.push_back(command.getArgs().second.at(1));
    command.setResult(resKey, resValue);
    return command;
}

Command & CommandInterpretator::requestRemoveIo(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    resKey.push_back(command.getCommand());
    if(command.getArgs().first.at(0) == "ioIndex") {
        peripherals->removeIo(std::stoi(command.getArgs().second.at(0)));
    }
    resValue.push_back(std::to_string(true));
    command.setResult(resKey, resValue);
    return command;
}

Command& CommandInterpretator::requestGetDevAddTypes(Command &command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    resValue = peripherals->getAvailableDev();
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

Command & CommandInterpretator::requestAddDevToIo(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    if(command.getArgs().first.at(0) == "ioIndex") {
        if(peripherals->addDev(std::stoi(command.getArgs().second.at(0)),
                               command.getArgs().first,
                               command.getArgs().second)) {
            resValue.push_back("true");
        } else {
            resValue.push_back("false");
        }
    }
    resValue = peripherals->getAvailableDev();
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

Command & CommandInterpretator::requestRemoveDevFromIo(Command & command) {
    //    if(command->getCommand() == "removeDev") {
    //        //void Controller::removeDev(int ioIndex, int devIndex) {
    //        ////    peripherals->removeDev(ioIndex, devIndex);
    //        ////    ioTreeModel.removeDevToConnection(ioIndex, devIndex);
    //        ////    emit removeDevSuccesSignal(ioIndex, devIndex);
    //        //}
    //        return;
    //    }
}

Command & CommandInterpretator::requestExecCommand(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    if((command.getArgs().first.at(0) == "ioIndex")
                && (command.getArgs().first.at(1) == "devIndex")
                && (command.getArgs().first.at(2) == "commandType")) {
            bool resBool = peripherals->devExecCommand(std::stoi(command.getArgs().second.at(0)),
                                                   std::stoi(command.getArgs().second.at(1)),
                                                   command.getArgs().second.at(2),
                                                   command.getArgs().first,
                                                   command.getArgs().second);
            resKey.push_back(command.getCommand());
            resValue.push_back(std::to_string(resBool));
            command.setResult(resKey, resValue);
        } else {
            std::cout << "commandInterprerator -" << command.getCommand() << " - bad arguments!" << std::endl;
    }
}

Command & CommandInterpretator::requestGetIoStatus(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    if(command.getArgs().first.at(0) == "ioIndex") {
        auto status = peripherals->getIoStatus(std::stoi(command.getArgs().second.at(0)));
        resValue.push_back(status.second.front());
    }
    resValue = peripherals->getAvailableDev();
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

Command & CommandInterpretator::requestGetDevStatus(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    std::string status;
    if(command.getArgs().first.at(0) == "ioIndex") {
        status = peripherals->getDevStatus(std::stoi(command.getArgs().second.at(0)));
    }
    resValue.push_back(resValue.push_back(resBool));
    resValue = peripherals->getAvailableDev();
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

Command & CommandInterpretator::requestGetIoCount(Command & command) {
    std::vector<std::string> resKey;
    std::vector<std::string> resValue;
    int resInt = false;
    if(command.getArgs().first.at(0) == "ioIndex") {
        resInt = peripherals->getIoCount(std::stoi(command.getArgs().second.at(0)));
    }
    resValue.push_back(resValue.push_back(resInt));
    resValue = peripherals->getAvailableDev();
    resKey.push_back(command.getCommand());
    command.setResult(resKey, resValue);
    return command;
}

