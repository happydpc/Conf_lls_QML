#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "QSqlError"

Database::Database(QObject *parent) : QObject(parent) {
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName("./db");
    if(!this->database.open()) {
        qDebug() << QString("error open database ") << database.lastError().text();
        throw QString("error open database");
    }
}

Database::~Database() {}

QString query_get_sessions("SELECT * FROM sessions");

//QString query_get_settings("SELECT sets_id, sets_count_digits, sets_used_minus FROM settings");
//QString query_set_settings("UPDATE settings SET sets_count_digits=%1, sets_used_minus = %2");
//QString query_update_statistics("UPDATE statistics SET "
//                                " stats_exercise_all_time='%1', stats_excercise_correct=%2,"
//                                " stats_excercise_wrong=%3, stats_excercise_all='%4'");
//QString query_get_statistics("SELECT "
//                             " user_first_name, user_last_name, stats_exercise_all_time,"
//                             " statistics.stats_excercise_all, statistics.stats_excercise_correct,"
//                             " statistics.stats_excercise_wrong "
//                             " FROM statistics"
//                             " JOIN user ON user.user_id = statistics.stats_user_id");
//QString query_get_version("SELECT * FROM version");

bool Database::getSessionsAll(QStringList &jsonResult) {
    bool res = false;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    query.exec(query_get_sessions);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    while(query.next()) {
        qDebug() << "Query=" << query.value(1).toString();
        jsonResult.push_back(query.value(1).toString());
        res = true;
    }
    return res;
}

//bool Database::getSettings(QString &version,
//                           int &count_digit_max, bool &use_minus,
//                           QString &first_name, QString &last_name,
//                           QString &exercise_all_time,
//                           int &exercise_correct, int &exercise_wrong, int &exercise_passed) {
//    bool res = false;
//    try {
//        QSqlQuery query;
//        // settings
//        query.exec(query_get_settings);
//        qDebug() << "Query=" << query.lastQuery();
//        while(query.next()) {
//            count_digit_max = query.value(1).toInt();
//            use_minus = query.value(2).toBool();
//        }
//        // user and statistics
//        query.exec(query_get_statistics);
//        qDebug() << "Query=" << query.lastQuery();
//        while(query.next()) {
//            first_name = query.value(0).toString();
//            last_name = query.value(1).toString();
//            exercise_all_time = query.value(2).toString();
//            exercise_passed = query.value(3).toInt();
//            exercise_correct = query.value(4).toInt();
//            exercise_wrong = query.value(5).toInt();
//        }
//        // version
//        query.exec(query_get_version);
//        qDebug() << "Query=" << query.lastQuery();
//        while(query.next()) {
//            version = query.value(2).toString();
//        }
//    } catch (...) {
//        throw QString("database: error request get settings!");
//    }
//    return res;
//}

//bool Database::setSettings(int count_digit_max, bool use_minus,
//                           QString first_name, QString last_name) {
//    bool res = false;
//    try {
//        QSqlQuery query;
//        // settings
//        query.exec(QString(query_set_settings)
//                   .arg(count_digit_max)
//                   .arg(use_minus));
//        qDebug() << "Query=" << query.lastQuery();
//        res = query.result();
//    } catch (...) {
//        throw QString("database: error request set settings!");
//    }
//    return res;
//}

//bool Database::getStatistics(QString &exercise_all_time,
//                             int &exercise_correct, int &exercise_wrong, int &exercise_passed) {
//    bool res = false;
//    try {
//        QSqlQuery query;
//        query.exec(query_get_statistics);
//        qDebug() << "Query=" << query.lastQuery();
//        while(query.next()) {
//            exercise_all_time = query.value(2).toString();
//            exercise_passed = query.value(3).toInt();
//            exercise_correct = query.value(4).toInt();
//            exercise_wrong = query.value(5).toInt();
//        }
//    } catch (...) {
//        throw QString("database: error request get statistics!");
//    }
//    return res;
//}

//bool Database::updateStatistics(QString exercise_all_time,
//                                int exercise_correct, int exercise_wrong, int exercise_passed) {
//    bool res = false;
//    try {
//        QSqlQuery query;
//        // settings
//        query.exec(QString(query_update_statistics).arg(exercise_all_time)
//                   .arg(exercise_correct)
//                   .arg(exercise_wrong)
//                   .arg(exercise_passed));
//        qDebug() << "Query=" << query.lastQuery();
//        res = query.result();
//    } catch (...) {
//        throw QString("database: error request update statistics");
//    }
//    return res;
//}
