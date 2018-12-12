#ifndef CONVERT_H
#define CONVERT_H

#include <QObject>

class Convert : public QObject
{
    Q_OBJECT
public:
    explicit Convert(QObject *parent = nullptr);

public:
    QVector<QString> convertStdVectorToQt(std::vector<std::string> converted);
    std::vector<std::string> convertQtToStd(QVector<QString> converted);
};

#endif // CONVERT_H
