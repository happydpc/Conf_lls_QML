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
    Q_INVOKABLE void requestAddIo(const QString typeIoName, const QString ioName, const QVector<QString> keys, const QVector<QString> params);
    Q_INVOKABLE void requestRemoveIo(int ioIndex);
    Q_INVOKABLE void requestGetIoAddTypes(const QString typeName);
    // dev
    Q_INVOKABLE void requestAddDevToIo(const int ioIndex, const QString devTypeName, const QVector<QString> keyParam, const QVector<QString> valueParam);
    Q_INVOKABLE void requestRemoveDev(int ioIndex, int devIndex);
    Q_INVOKABLE void requestGetDevAddTypes();
    Q_INVOKABLE void requestDevExecCommand(int ioIndex, int devIndex,
                                    const QString commandType,
                                    QVector<QString> keys,
                                    QVector<QString> params);
    // logo, form
    Q_INVOKABLE QString getTypeLogo() const;
    // io/dev tree
    Q_INVOKABLE ModelDevTree* getIoTreeModel();

signals:

    void signal_get_availableIo(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_add_Io(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_remove_Io(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_add_dev_to_Io(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_get_add_types(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_remove_dev_of_Io(QVector<QString> resultKey, QVector<QString> resultValue);
    void signal_exec_dev_command(QVector<QString> resultKey, QVector<QString> resultValue);

    // io
//    void addIoSuccesSignal(QString ioType, std::vector<QString> keyProperty, std::vector<QString> valueProperty);
//    void addIoFailSignal(QString ioType, QString ioName);
//    void ioUpdatePropertySignal(QString ioType, int ioIndex, std::vector<QString> keyProperty, std::vector<QString> valueProperty);
//    void removeIoSuccesSignal(int ioIndex);
//    void ioActivateSignal(int ioIndex, std::vector<QString> keyProperty, std::vector<QString> valueProperty);
//    void ioTreeIsEmptySignal();

//    // dev
//    void addDevSuccesSignal(int ioIndex, QString devType, std::vector<QString> devKeyProperty, std::vector<QString> devValueProperty);
//    void addDevFailSignal(QString devName, QString errorMessage);
//    void removeDevSuccesSignal(int ioIndex, int devIndex);
//    void devExecComamndReadySignal(int ioIndex, int devIndex, std::vector<QString> keys, std::vector<QString> values);
//    void devConnectedSignal(int ioIndex, int devIndex, QString typeDev);
//    void devReadySignal(int ioIndex, int devIndex, QString typeDev);
//    void devDisconnectedSignal(int ioIndex, int devIndex, QString typeDev);
//    void devActivatePropertySignal(QString devType, int ioIndex, int devIndex);
//    void devUpdatePeriodicDataSignal(QString devType, int ioIndex, int devIndex, std::vector<QString> keys, std::vector<QString> values);
//    void devUpdateLogMessageSignal(int ioIndex, int devIndex, QString codeMessage, QString message);
//    void ioAndDevFlushDataSignal();

    // update
    void isAvailableNewVersionSignal(QString downloadUrl);

private:
    static void ioTreeHandlerFunction(std::shared_ptr<ModelDevTree> ioTreeModel,
        std::shared_ptr<CommandController> commandController);

private:
    std::shared_ptr<ModelDevTree> ioTreeModel;
    std::shared_ptr<CommandController> commandController;
    std::shared_ptr<std::thread> ioTreeThread;
};

#endif // CONTROLLER_H
