#ifndef PROGRESS_BASEDATA_H
#define PROGRESS_BASEDATA_H

#include <QObject>

class Progress_BaseData : public QObject
{
    Q_OBJECT
public:
    explicit Progress_BaseData(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PROGRESS_BASEDATA_H