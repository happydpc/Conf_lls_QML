#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <memory>
#include "view/module/modelDevTree.h"
#include "command/commandController.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    // io
    Q_INVOKABLE bool addIo(const QString typeIoName, const QString ioName, const QStringList keys, const QStringList params);
    Q_INVOKABLE void removeIo(int ioIndex);
    Q_INVOKABLE QStringList getIoAddTypes(const QString typeName);
    // dev
    Q_INVOKABLE bool addDevToIo(const int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    Q_INVOKABLE void removeDev(int ioIndex, int devIndex);
    Q_INVOKABLE QStringList getDevAddTypes() const;
    Q_INVOKABLE bool devExecCommand(int ioIndex, int devIndex, const QString commandType,
                                    const QStringList keys, const QStringList params);
    // logo, form
    Q_INVOKABLE QString getTypeLogo() const;

    // io/dev tree
    Q_INVOKABLE ModelDevTree* getIoTreeModel();

signals:
    // io
    void addIoSuccesSignal(QString ioType, QStringList keyProperty, QStringList valueProperty);
    void addIoFailSignal(QString ioType, QString ioName);
    void ioUpdatePropertySignal(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void removeIoSuccesSignal(int ioIndex);
    void ioActivateSignal(int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void ioTreeIsEmptySignal();

    // dev
    void addDevSuccesSignal(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
    void addDevFailSignal(QString devName, QString errorMessage);
    void removeDevSuccesSignal(int ioIndex, int devIndex);
    void devExecComamndReadySignal(int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devConnectedSignal(int ioIndex, int devIndex, QString typeDev);
    void devReadySignal(int ioIndex, int devIndex, QString typeDev);
    void devDisconnectedSignal(int ioIndex, int devIndex, QString typeDev);
    void devActivatePropertySignal(QString devType, int ioIndex, int devIndex);
    void devUpdatePeriodicDataSignal(QString devType, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devUpdateLogMessageSignal(int ioIndex, int devIndex, QString codeMessage, QString message);
    void ioAndDevFullFlushDataSignal();

    // update
    void isAvailableNewVersionSignal(QString downloadUrl);

private:
    ModelDevTree ioTreeModel;
    std::shared_ptr<CommandController> commandController;
};

#endif // CONTROLLER_H
