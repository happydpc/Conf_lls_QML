#ifndef BATTLERESULT_H
#define BATTLERESULT_H

#include <QObject>

class BattleResult : public QObject
{
    Q_OBJECT
public:
    explicit BattleResult(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BATTLERESULT_H