#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <deque>
#include <thread>
#include <mutex>
#include <memory>
#include "command.h"
#include "../view/peripherals.h"

class CommandController : public QObject
{
    Q_OBJECT
public:
    explicit CommandController(QObject *parent = nullptr);
    ~CommandController();

    bool addCommandToStack(const QList<Command*> command);
    Command* getFirstCommand() const;
    void removeFirstCommand();
    bool getIsEmpty();

    static void handlerFunction(std::mutex* pMutex, std::deque<Command*>* commandQueue);
    static void commandInterprerator(Command* command, Peripherals* peripherals);
private:
    std::shared_ptr<std::deque<Command*>> commandQueue;
    std::shared_ptr<std::thread> handlerThread;
    std::shared_ptr<std::mutex> lock;
};

#endif // COMMANDCONTROLLER_H
