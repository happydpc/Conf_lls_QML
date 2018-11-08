#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QQueue>
#include <QPair>

class CommandController : public QObject
{
    Q_OBJECT
public:
    explicit CommandController(QObject *parent = nullptr);

    typedef enum {
        E_CommandType_send_typical_request,
        E_CommandType_send_security_request,
        E_CommandType_command_without_request
    }eCommandType;

    typedef struct {
        eCommandType commandType;
        // uniqual ident device
        QString deviceIdent;
        QString deviceTypeName;
        // dev command
        int devCommand;
        // need ack what command executed?
        bool isNeedAckMessage;
        // bytearray for command buf
        QByteArray commandOptionData;
        // buffer for transmit settings, firmware and other data
        struct {
            QList<QString>key;
            QList<QString>value;
        }args;
        bool isNeedIncreasedDelay;
        QString operationHeader;
    }sCommandData;

    bool addCommandToStack(sCommandData commandData);
    QPair<bool, CommandController::sCommandData> getCommandFirstCommand();
    void removeFirstCommand();
    bool commandsIsEmpty();

private:

    QQueue<sCommandData> commandQueue;
};

#endif // COMMANDCONTROLLER_H

//typedef enum {
//    E_CommandType_send_typical_request,
//    E_CommandType_send_security_request,
//    E_CommandType_command_without_request
//}eCommandType;

//typedef struct {
//    // executed status
//    bool isNoExecuted;
//    bool isExecutedNormal;
//    bool isExecutedError;
//    // bytearray for command buf
//    QByteArray commandOptionData;
//    // buffer for transmit settings, firmware and other data
//    struct {
//        QList<QString>key;
//        QList<QString>value;
//    }args;
//    bool isNeedIncreasedDelay;
//    QString operationHeader;
//}sData;

//typedef struct {
//    // type command (typical request, sequrity, quite request)
//    eCommandType commandTypes;
//    // dev command
//    QList<int> devCommands;
//    QList<sData>data;

//    int countRepeatIfErrorExec;

//    // type signal affter it exec
//    int typeResultSignal;
//    QString typeResultMessage;

//    // uniqual ident device
//    QString deviceIdent;
//    QString deviceTypeName;

//    // need ack what command executed?
//    bool isNeedAckMessage;
//    QString exectAckMessage;
//}sCommandData;
