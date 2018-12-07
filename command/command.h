#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);

    void setCommand(std::string command);
    void setArgs(std::list<std::string> keys, std::list<std::string> values);
    void setDelayRequstMs(int delay_ms);
    std::string getCommand();
    std::pair<std::vector<std::string>,std::vector<std::string>> getArgs();
    int getDelayRequstMs();
private:
    std::string command;

    // buffer for transmit settings, firmware and other data
    struct {
        std::vector<std::string> key;
        std::vector<std::string> value;
    }args;

    int delay_request_ms;
};

#endif // COMMAND_H
