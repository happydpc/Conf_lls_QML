#include "model.h"
#include "treeitem.h"

Model::Model(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>()) {
}

TreeItem * Model::createTreeItem(QString nameInterface){
    auto res = new TreeItem(nameInterface, true);
    return res;
}

TreeItem * Model::createTreeSubItem(QString nameDevice) {
    auto res = new TreeItem(nameDevice, false);
    connect(res, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    return res;
}

void Model::addConnection(QString connectionName) {
    TreeItem * titem = createTreeItem(connectionName);
    m_tree.append(std::move(titem));
    connect(titem, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    treeChanged();
}

void Model::removeConnection(int indexConnection) {
    disconnectaFullTree();
    m_tree.removeAt(indexConnection);
    connectFullTree();
    treeChanged();
}

void Model::addDeviceToConnection(QString nameConnection, QString nameDevice, bool deviceStatus) {
    for(auto it: m_tree) {
        if(it->content() == nameConnection) {
            TreeItem * tDevItem = createTreeSubItem(nameDevice);
            it->addChildItem(std::move(tDevItem));
            it->setIsParent(true);
            treeChanged();
        }
    }
}

void Model::removeDeviceToConnection(int indexConnection, int indexDevice) {
    disconnectaFullTree();
    m_tree.at(indexConnection)->removeChildByIndexChild(indexDevice);
    connectFullTree();
    treeChanged();
}

const QList<TreeItem *> &Model::tree() const{
    return m_tree;
}

const QList<QObject *> Model::treeAsQObjects() const{
    QList<QObject *> res;
    res.reserve(m_tree.count());
    for(auto i : m_tree)
        res.append(i);
    return res;
}

void Model::disconnectaFullTree() {
    for(auto it: m_tree) {
        disconnect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            disconnect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }
}

void Model::connectFullTree() {
    for(auto it: m_tree) {
        connect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            connect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }
}

int Model::getDevIndex() {
    return curIndex.devIndex;
}

int Model::getIoIndex() {
    return curIndex.ioIndex;
}

void Model::setDevIndex(int index) {
    curIndex.devIndex = index;
}

void Model::setIoIndex(int index) {
    curIndex.ioIndex = index;
}

void Model::setDevStatusByIndex(int devIndex, int status) {
    TreeItem *pDev = nullptr;
    pDev = m_tree.at(curIndex.ioIndex);
    if(pDev != nullptr) {
         pDev->childItems().at(devIndex)->setConnected((bool)status);
    }
}

void Model::currentIndexIsChanged(bool, TreeItem *pSender) {
    disconnectaFullTree();
    if(pSender->isParent()) {
        int index = 0;
        for(auto it: m_tree) {
            for(auto ch = it->childItems().begin(); ch!= it->childItems().end(); ch++) {
                (*ch)->setIsCurrent(false);
            }
        }
        for(auto it: m_tree) {
            if(it == pSender) {
                it->setIsCurrent(true);
                emit currentIndexIsChangedInteface(index);
            } else {
                it->setIsCurrent(false);
            }
            index++;
        }
    } else {
        int indexParent = 0;
        for(auto it: m_tree) {
            it->setIsCurrent(false);
            int indexChild = 0;
            // находим своего родителя и делаем его активным
            for(auto it2: it->childItems()) {
                if(it2 == pSender) {
                    it2->setIsCurrent(true);
                    emit currentIndexIsChangedDevice(indexParent, indexChild);
                } else {
                    it2->setIsCurrent(false);
                }
                indexChild++;
            }
            indexParent++;
        }
    }
    connectFullTree();
}
