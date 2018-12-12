#include "modelDevTree.h"
#include "treeitem.h"

ModelDevTree::ModelDevTree(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>()) {
}

TreeItem * ModelDevTree::createTreeItem(QString nameInterface) {
    auto res = new TreeItem(nameInterface, true);
    res->setIsCurrent(true);
    return res;
}

TreeItem * ModelDevTree::createTreeSubItem(QString nameDevice) {
    auto res = new TreeItem(nameDevice, false);
    connect(res, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    return res;
}

void ModelDevTree::addIo(QString connectionName) {
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

void ModelDevTree::removeIo(int indexConnection) {
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

void ModelDevTree::removeAll() {
    disconnectaFullTree();
    m_tree.clear();
    setIoIndex(0);
    setDevIndex(0);
    connectFullTree();
    treeChanged();
}

void ModelDevTree::addDevToIo(int ioIndex, QString devName) {
    if(!m_tree.empty()) {
        if(ioIndex < (m_tree.size()-1)) {
            TreeItem * tDevItem = createTreeSubItem(devName);
            tDevItem->setIsCurrent(true);
            m_tree[ioIndex]->addChildItem(std::move(tDevItem));
            m_tree[ioIndex]->setIsParent(true);
            m_tree[ioIndex]->setIsOpen(true);
            setDevIndex(m_tree[ioIndex]->childItems().size()-1);
            treeChanged();
        }
    }
}

bool ModelDevTree::changeDevName(QString nameConnection, QString devName, QString devNewName) {
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

bool ModelDevTree::changeDevHeader(QString nameConnection, QString devName, QString devNewHeader) {
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

void ModelDevTree::removeDevToConnection(int indexConnection, int indexDevice) {
    disconnectaFullTree();
    m_tree.at(indexConnection)->removeChildByIndexChild(indexDevice);
    connectFullTree();
    if(!m_tree.at(indexConnection)->childItems().isEmpty()) {
        setDevIndex(m_tree.at(indexConnection)->childItems().size()-1);
    } else {
        for(auto it:m_tree) {
            it->setIsCurrent(false);
        }
        m_tree[indexConnection]->setIsCurrent(true);
        setDevIndex(0);
    }
    treeChanged();
}

const QList<TreeItem *> &ModelDevTree::tree() const {
    return m_tree;
}

const QList<QObject *> ModelDevTree::treeAsQObjects() const {
    QList<QObject *> res;
    res.reserve(m_tree.count());
    for(auto i : m_tree)
        res.append(i);
    return res;
}

void ModelDevTree::disconnectaFullTree() {
    for(auto it: m_tree) {
        disconnect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            disconnect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }
}

void ModelDevTree::connectFullTree() {
    for(auto it: m_tree) {
        connect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            connect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }
}

int ModelDevTree::getDevIndex() {
    return curIndex.devIndex;
}

int ModelDevTree::getIoIndex() {
    return curIndex.ioIndex;
}

void ModelDevTree::setDevIndex(int index) {
    curIndex.devIndex = index;
}

void ModelDevTree::setIoIndex(int index) {
    curIndex.ioIndex = index;
}

void ModelDevTree::setIoStatus(int ioIndex, int status) {
    TreeItem *p_io = nullptr;
    if(m_tree.size() >= ioIndex+1) {
        p_io = m_tree.at(ioIndex);
        if(p_io != nullptr) {
            p_io->setConnected((bool)status);
        }
    }
}

void ModelDevTree::setDevStatus(int devIndex, int status) {
    TreeItem *p_dev = nullptr;
    p_dev = m_tree.at(curIndex.ioIndex);
    if(p_dev != nullptr) {
        if(!p_dev->childItems().isEmpty()) {
            p_dev->childItems().at(devIndex)->setConnected((bool)status);
        }
    }
}

void ModelDevTree::currentIndexIsChanged(bool, TreeItem *pSender) {
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
                emit indexIoIsChanged(index, 0);
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
                    setIoIndex(indexParent);
                    emit indexDevIsChanged(indexParent, indexChild);
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
