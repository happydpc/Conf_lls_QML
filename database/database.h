#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <memory>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    ~Database();

    bool getSessionsAll(QStringList &jsonResult);

//    bool getSettings(QString &version,
//                     int &count_digit_max, bool &use_minus,
//                     QString &first_name, QString &last_name,
//                     QString &exercise_all_time,
//                     int &exercise_correct, int &exercise_wrong, int &exercise_passed);

//    bool setSettings(int count_digit_max, bool use_minus,
//                     QString first_name, QString last_name);

//    bool getStatistics(QString &exercise_all_time,
//                               int &exercise_correct, int &exercise_wrong, int &exercise_passed);
//    bool updateStatistics(QString exercise_all_time,
//                           int exercise_correct, int exercise_wrong, int exercise_passed);

private:

    QSqlDatabase database;

signals:

public slots:
};

#endif // DATABASE_H
