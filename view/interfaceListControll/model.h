#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class TreeItem;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);

    Q_PROPERTY(QList<QObject*> tree READ treeAsQObjects NOTIFY treeChanged)
    const QList<TreeItem*> &tree() const;
    const QList<QObject*> treeAsQObjects() const;


    void addConnection(QString name);
    void removeConnection(int index);

    void addDeviceToConnection(QString nameConnection, QString nameDevice, bool deviceStatus);
    void removeDeviceToConnection(int indexConnection, int indexDevice);

signals:
    void treeChanged();

    void currentIndexIsChangedDevice(int interfaceIndex, int deviceIndex);
    void currentIndexIsChangedInteface(int index);


private slots:

    TreeItem *createTreeItem(QString nameInterface);
    TreeItem *createTreeSubItem(QString nameDevice);

    void currentIndexIsChanged(bool isParent, TreeItem *pSender);

    void disconnectaFullTree();
    void connectFullTree();

private:
    QList<TreeItem*> m_tree;
};

#endif // MODEL_H
