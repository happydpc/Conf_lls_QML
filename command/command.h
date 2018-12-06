#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);

    void setCommand(QString command);
    void setArgs(QStringList keys, QStringList values);
    void setDelayRequstMs(int delay_ms);
    QString getCommand();
    QPair<QStringList,QStringList> getArgs();
    int getDelayRequstMs();
private:
    QString command;

    // buffer for transmit settings, firmware and other data
    struct {
        QStringList key;
        QStringList value;
    }args;

    int delay_request_ms;
};

#endif // COMMAND_H
