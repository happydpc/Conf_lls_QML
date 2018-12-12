#include "commandController.h"
#include "commandinterpretator.h"
#include <iostream>
#include <stdio.h>

CommandController::CommandController(QObject *parent) : QObject(parent) {
    this->lock = std::make_shared<std::mutex>();
    this->commandQueue = std::make_shared<std::vector<Command>>();
    this->handlerThread = std::make_shared<std::thread>(handlerFunction, lock.get(), commandQueue);
    this->handlerThread->detach();
}

CommandController::~CommandController() {
    handlerThread.reset();
}

/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *
 *  returns: future
 */
std::future<Command*> CommandController::addCommandToStack(Command commandData) {
    lock->lock();
    commandQueue->push_back(std::move(commandData));
    auto replyHandle = [&]() {
        bool commandIsExecuted = false;
        Command *p = &commandQueue->back();
        while(!commandIsExecuted) {
            if(lock->try_lock()) {
                commandIsExecuted = p->getIsExecuted();
                lock->unlock();
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        return p;
    };
    lock->unlock();
    std::packaged_task<Command*()> task(replyHandle);
    auto future = task.get_future();
    std::thread thread(std::move(task));
    thread.detach();
    return std::move(future);
}

/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *
 *  returns: future
 */
Command* CommandController::getFirstCommand() const {
    std::lock_guard<std::mutex> guard(*lock.get());
    if(!commandQueue->empty()) {
        return &commandQueue->front();
    }
    return nullptr;
}

/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *
 *  returns: future
 */
void CommandController::removeFirstCommand() {
    std::lock_guard<std::mutex> guard(*lock.get());
    if(!commandQueue->empty()) {
        commandQueue->pop_back();
    }
}

/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *
 *  returns: future
 */
bool CommandController::getIsEmpty() {
    return commandQueue->empty();
}

/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *
 *  returns: future
 */
void CommandController::handlerFunction(std::mutex* pMutex, std::shared_ptr<std::vector<Command>> queue) {
    std::shared_ptr<Peripherals> peripherals = std::make_shared<Peripherals>();
    while(1) {
        if(pMutex->try_lock()) {
            if(!queue->empty()) {
                for(auto queItem = queue->begin(); queItem != queue->end(); queItem++) {
                    if(!(queItem)->getIsExecuted()) {
                        commandInterprerator(&(*queItem), peripherals.get());
                        (*queItem).setIsExecuted();
                    }
                }
            }
            pMutex->unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


/*
 * Function:  addCommandToStack
 * --------------------
 * add command to stack
 * and and wait while executed
 *
 *  commandData: command struct
 *      requestGetIoAddTypes
 *      1) ioTypeName
 *
 *  returns: non
 */
void CommandController::commandInterprerator(Command* command, Peripherals* peripherals) {
    CommandInterpretator interperator(peripherals);
    if(command->getCommand() == "requestGetIoAddTypes") {
        interperator.requestGetIoAddTypes(*command);
    }
    if(command->getCommand() == "addIo") {
        interperator.requestAddIo(*command);
    }
    if(command->getCommand() == "removeIo") {
        interperator.requestRemoveIo(*command);
    }
    if(command->getCommand() == "addDevToIo") {
        interperator.requestAddDevToIo(*command);
    }
    if(command->getCommand() == "removeDev") {
        interperator.requestRemoveDevFromIo(*command);
    }
    if(command->getCommand() == "getDevAddTypes") {
        interperator.requestGetDevAddTypes(*command);
    }
    if(command->getCommand() == "devExecCommand") {
        interperator.requestExecCommand(*command);
    }

    if(command->getCommand() == "getIoStatus") {
        interperator.requestRemoveIo(*command);
    }
    if(command->getCommand() == "getDevStatus") {
        interperator.requestRemoveIo(*command);
    }
}

