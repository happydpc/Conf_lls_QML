#include "convert.h"
#include <QVector>

Convert::Convert(QObject *parent) : QObject(parent) {
}

QVector<QString> Convert::convertStdVectorToQt(std::vector<std::string> converted) {
    QVector<QString> res;
    for(auto item: converted) {
        res.push_back(QString::fromStdString(item));
    }
    return res;
}

std::vector<std::string> Convert::convertQtToStd(QVector<QString> converted) {
    std::vector<std::string> res;
    for(auto item: converted) {
        res.push_back(item.toStdString());
    }
    return res;
}
