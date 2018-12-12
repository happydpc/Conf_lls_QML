#ifndef COMMANDINTERPRETATOR_H
#define COMMANDINTERPRETATOR_H

#include <QObject>
#include "view/peripherals.h"
#include "command/command.h"

class CommandInterpretator : public QObject
{
    Q_OBJECT
public:
    explicit CommandInterpretator(Peripherals* peripherals);

    Command & requestAddIo(Command & command);
    Command & requestRemoveIo(Command & command);
    Command & requestGetIoAddTypes(Command & command);
    Command & requestGetDevAddTypes(Command & command);
    Command & requestAddDevToIo(Command & command);
    Command & requestRemoveDevFromIo(Command & command);
    Command & requestExecCommand(Command & command);
    Command & requestGetIoStatus(Command & command);
    Command & requestGetDevStatus(Command & command);
    Command & requestGetIoCount(Command & command);

private:
    Peripherals* peripherals;
};

#endif // COMMANDINTERPRETATOR_H
