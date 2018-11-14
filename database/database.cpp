#include "database.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "QSqlError"
#include <QSqlResult>

Database::Database(QObject *parent) : QObject(parent) {
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName("./db");
    if(!this->database.open()) {
        qDebug() << QString("error open database ") << database.lastError().text();
        throw QString("error open database");
    }
}

Database::~Database() {}

QString query_get_sessions_count("SELECT * FROM sessions");
QString query_get_sessions_all("SELECT * FROM sessions");
QString query_send_remove_session_by_name("DELETE FROM sessions "
                                          " WHERE session_name = '%1';");
QString query_insert_sessions_new_session("INSERT INTO sessions ([values], session_name) "
                                          "VALUES ('%1','%2');"
                                          );


QStringList Database::getSessionsCountAvailable() const {
    QStringList res;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    query.exec(query_get_sessions_count);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    while(query.next()) {
        res.push_back(query.value(2).toString());
        qDebug() << "Query=" << query.value(2).toString();
    }
    return res;
}

QStringList Database::getSessionsAll() const {
    QStringList jsonRes;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    query.exec(query_get_sessions_all);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    while(query.next()) {
        qDebug() << "Query=" << query.value(1).toString();
        jsonRes.push_back(query.value(1).toString());
    }
    return jsonRes;
}

bool Database::sendRemoveSession(const QString sessionName) {
    bool res = false;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    QString t_query = query_send_remove_session_by_name.arg(sessionName);
    res = query.exec(t_query);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    return res;
}

bool Database::sendSaveSession(const QString sessionName, const QString jsonData) {
    bool res = false;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    QString t_query = query_insert_sessions_new_session.arg(jsonData, sessionName);
    res = query.exec(t_query);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    return res;
}
