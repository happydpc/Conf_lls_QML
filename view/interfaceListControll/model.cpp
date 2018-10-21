#include "model.h"
#include "treeitem.h"

Model::Model(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>()) {
}

TreeItem * Model::createTreeItem(QString nameInterface){
    auto res = new TreeItem(nameInterface, true);
    res->setIsCurrent(true);
    return res;
}

TreeItem * Model::createTreeSubItem(QString nameDevice) {
    auto res = new TreeItem(nameDevice, false);
    connect(res, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    return res;
}

void Model::addConnection(QString connectionName) {
    if(!m_tree.empty()) {
        for(auto it:m_tree) {
            it->setIsCurrent(false);
        }
    }
    TreeItem * titem = createTreeItem(connectionName);
    m_tree.append(std::move(titem));
    connect(titem, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    treeChanged();
    emit currentIndexIsChanged(false, titem);
    setIoIndex(m_tree.size()-1);
}

void Model::removeConnection(int indexConnection) {
    disconnectaFullTree();
    m_tree.removeAt(indexConnection);
    if(!m_tree.empty()) {
        m_tree.first()->setIsCurrent(true);
        setIoIndex(m_tree.size()-1);
    } else {
        setIoIndex(0);
    }
    connectFullTree();
    treeChanged();
}

void Model::addDeviceToConnection(QString connName, QString devName) {
    for(auto it: m_tree) {
        if(it->content() == connName) {
            TreeItem * tDevItem = createTreeSubItem(devName);
            it->addChildItem(std::move(tDevItem));
            it->setIsParent(true);
            setDevIndex(it->childItems().size()-1);
            treeChanged();
        }
    }
}

bool Model::changeDeviceName(QString nameConnection, QString devName, QString devNewName) {
    bool res = false;
    for(auto it: m_tree) {
        if(it->content() == nameConnection) {
            for(auto devs:it->childItems()) {
                if(devs->content() == devName) {
                    devs->setContent(devNewName);
                    res = true;
                }
            }
            treeChanged();
        }
    }
    return res;
}

bool Model::changeDeviceHeader(QString nameConnection, QString devName, QString devNewHeader) {
    bool res = false;
    for(auto it: m_tree) {
        if(it->content() == nameConnection) {
            for(auto devs:it->childItems()) {
                if(devs->content() == devName) {
                    devs->setHeader(devNewHeader);
                    res = true;
                }
            }
            treeChanged();
        }
    }
    return res;
}

void Model::removeDeviceToConnection(int indexConnection, int indexDevice) {
    disconnectaFullTree();
    m_tree.at(indexConnection)->removeChildByIndexChild(indexDevice);
    connectFullTree();
    treeChanged();
    if(!m_tree.at(indexConnection)->childItems().isEmpty()) {
        setDevIndex(m_tree.at(indexConnection)->childItems().size()-1);
    } else {
        setDevIndex(0);
    }
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
        if(!pDev->childItems().isEmpty()) {
            pDev->childItems().at(devIndex)->setConnected((bool)status);
        }
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
                setIoIndex(index);
                setDevIndex(0);
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
                    setDevIndex(indexChild);
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
