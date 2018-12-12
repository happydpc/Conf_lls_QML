#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    Command(const Command & command);

    void setCommand(std::string command);
    std::string getCommand();

    void setIsExecuted();
    bool getIsExecuted();

    void setArgs(std::vector<std::string> keys, std::vector<std::string> values);
    std::pair<std::vector<std::string>,std::vector<std::string>> getArgs();
    void setResult(std::vector<std::string> keys, std::vector<std::string> values);
    std::pair<std::vector<std::string>,std::vector<std::string>> getResult();
    void setDelayRequstMs(int delay_ms);
    int getDelayRequstMs();

private:

    bool isExecuted;

    std::string command;

    // buffer for transmit settings, firmware and other data
    struct {
        std::vector<std::string> key;
        std::vector<std::string> value;
    }args;

    // buffer for result data
    struct {
        std::vector<std::string> key;
        std::vector<std::string> value;
    }result;

    int delay_request_ms;
};

#endif // COMMAND_H
