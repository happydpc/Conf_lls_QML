#ifndef TIMEGAME_H
#define TIMEGAME_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class TimeGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getDateTime NOTIFY updateTime)

public:
    explicit TimeGame(QObject *parent = nullptr);

signals:
    void updateTime(QString dateTime);

private slots:
    void updateSecondTimer();

private:
    QTimer *secondTimer;
};

#endif // TIMEGAME_H
