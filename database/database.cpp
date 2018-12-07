#include "database.h"
#include <stdio.h>
#include <iostream>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "QSqlError"
#include <QSqlResult>

Database::Database(QObject *parent) : QObject(parent) {
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->database.setDatabaseName("./db");
    if(!this->database.open()) {
        std::cout << "error open database " << database.lastError().text().toStdString();
        throw std::string("error open database");
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

std::list<std::string> Database::getSessionsCountAvailable() const {
    std::list<std::string> res;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    query.exec(query_get_sessions_count);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    while(query.next()) {
        res.push_back(std::string(query.value(2).toString().toLocal8Bit()));
        qDebug() << "Query=" << query.value(2).toString();
    }
    return res;
}

std::list<std::string> Database::getSessionsAll() const {
    std::list<std::string> res;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    query.exec(query_get_sessions_all);
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    while(query.next()) {
        qDebug() << "Query=" << query.value(1).toString();
        res.push_back(std::string(query.value(1).toString().toLocal8Bit()));
    }
    return res;
}

bool Database::sendRemoveSession(const std::string sessionName) {
    bool res = false;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    res = query.exec(query_send_remove_session_by_name.arg(QString(sessionName.c_str())));
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    return res;
}

bool Database::sendSaveSession(const std::string sessionName, const std::string jsonData) {
    bool res = false;
    QSqlQuery query(database);
    qDebug() << "Query=" << (database.isOpen() == true ? "open" : "closed");
    res = query.exec(query_insert_sessions_new_session.arg(QString(jsonData.c_str()), QString(sessionName.c_str())));
    qDebug() << "Query=" << query.lastQuery();
    qDebug() << "Query=" << query.lastError().text();
    return res;
}
