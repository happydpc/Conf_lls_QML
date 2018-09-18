#ifndef PROGRESS_BASE_DATA_H
#define PROGRESS_BASE_DATA_H

#include <QObject>

class Progress_Base_data : public QObject
{
    Q_OBJECT
public:
    explicit Progress_Base_data(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PROGRESS_BASE_DATA_H