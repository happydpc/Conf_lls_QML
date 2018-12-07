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
    Q_INVOKABLE void requestAddIo(const std::string typeIoName, const std::string ioName, const std::list<std::string> keys, const std::list<std::string> params);
    Q_INVOKABLE void requestRemoveIo(int ioIndex);
    Q_INVOKABLE void requestGetIoAddTypes(const std::string typeName);
    // dev
    Q_INVOKABLE void requestAddDevToIo(const int ioIndex, const std::string devTypeName, const std::list<std::string> keyParam, const std::list<std::string> valueParam);
    Q_INVOKABLE void requestRemoveDev(int ioIndex, int devIndex);
    Q_INVOKABLE void requestGetDevAddTypes();
    Q_INVOKABLE void requestDevExecCommand(int ioIndex, int devIndex,
                                    const std::string commandType,
                                    std::list<std::string> keys,
                                    std::list<std::string> params);
    // logo, form
    Q_INVOKABLE std::string getTypeLogo() const;
    // io/dev tree
    Q_INVOKABLE ModelDevTree* getIoTreeModel();

signals:
    // io
    void addIoSuccesSignal(std::string ioType, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
    void addIoFailSignal(std::string ioType, std::string ioName);
    void ioUpdatePropertySignal(std::string ioType, int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
    void removeIoSuccesSignal(int ioIndex);
    void ioActivateSignal(int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
    void ioTreeIsEmptySignal();

    // dev
    void addDevSuccesSignal(int ioIndex, std::string devType, std::list<std::string> devKeyProperty, std::list<std::string> devValueProperty);
    void addDevFailSignal(std::string devName, std::string errorMessage);
    void removeDevSuccesSignal(int ioIndex, int devIndex);
    void devExecComamndReadySignal(int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
    void devConnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devReadySignal(int ioIndex, int devIndex, std::string typeDev);
    void devDisconnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devActivatePropertySignal(std::string devType, int ioIndex, int devIndex);
    void devUpdatePeriodicDataSignal(std::string devType, int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
    void devUpdateLogMessageSignal(int ioIndex, int devIndex, std::string codeMessage, std::string message);
    void ioAndDevFullFlushDataSignal();

    // update
    void isAvailableNewVersionSignal(std::string downloadUrl);

private:
    ModelDevTree ioTreeModel;
    std::shared_ptr<CommandController> commandController;
};

#endif // CONTROLLER_H
