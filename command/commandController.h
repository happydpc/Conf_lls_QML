#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include "command.h"
#include <future>
#include "../view/peripherals.h"

class CommandController : public QObject
{
    Q_OBJECT
public:
    explicit CommandController(QObject *parent = nullptr);
    ~CommandController();

    std::future<Command*> addCommandToStack(Command command);
    // bool addCommandToStack(std::vector<Command*> command); // TODO:
    Command* getFirstCommand() const;
    void removeFirstCommand();
    bool getIsEmpty();

signals:
    commandExecuted(Command *command);

private:
    static void handlerFunction(std::mutex* pMutex, std::shared_ptr<std::vector<Command>> commandQueue);
    static void commandInterprerator(Command *command, Peripherals *peripherals);
private:
    std::shared_ptr<std::vector<Command>> commandQueue;
    std::shared_ptr<std::thread> handlerThread;
    std::shared_ptr<std::mutex> lock;
};

#endif // COMMANDCONTROLLER_H
