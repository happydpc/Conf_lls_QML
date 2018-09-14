#include "model.h"
#include "treeitem.h"

const int number = 100;

TreeItem * Model::createTreeSubItem(){
    auto res = new TreeItem(QString("PROGRESS TMK24s") +  QString::number(qrand() % number), false);
    connect(res, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
    return res;
}

TreeItem * Model::createTreeItem(QString nameInterface, int subItemCount){
    auto res = new TreeItem(nameInterface, true);
    while(subItemCount) {
        res->addChildItem(createTreeSubItem());
        subItemCount--;
    }
    return res;
}

Model::Model(QObject *parent) :
    QObject(parent),
    m_tree(QList<TreeItem*>()) {
    m_tree.append(createTreeItem("ttyS0", 0));
    m_tree.append(createTreeItem("ttyS1", 0));
    m_tree.append(createTreeItem("ttyS2", 3));
    m_tree.append(createTreeItem("ttyS3", 5));
    m_tree.append(createTreeItem("ttyS4", 0));
    m_tree.append(createTreeItem("ttyS5", 0));
    m_tree.append(createTreeItem("ttyS6", 0));
    m_tree.append(createTreeItem("ttyS7", 7));

    for(auto it: m_tree) {
        connect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
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

void Model::currentIndexIsChanged(bool, TreeItem *pSender) {
    for(auto it: m_tree) {
        disconnect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            disconnect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }

    if(pSender->isParent()) {
        for(auto it: m_tree) {
            if(it != pSender) {
                it->setIsCurrent(false);
            }
        }
    } else {
        for(auto it: m_tree) {
            for(auto it2: it->childItems()) {
                if(it2 != pSender) {
                    it2->setIsCurrent(false);
                }
            }
        }
    }
    for(auto it: m_tree) {
        connect(it, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        for(auto it2:it->childItems()) {
            connect(it2, SIGNAL(currentIndexIsChanged(bool, TreeItem*)), this, SLOT(currentIndexIsChanged(bool, TreeItem*)));
        }
    }
}
