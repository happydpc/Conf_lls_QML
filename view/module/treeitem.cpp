#include "treeitem.h"

TreeItem::TreeItem(std::string content, bool isParent, QObject *parent) :
    QObject(parent),
    m_content(content),
    m_childItems(QList<TreeItem*>()),
    m_isOpen(false),
    m_isCurrent(false),
    m_isConnected(false)
{
    this->m_isParent = isParent;
}

const std::string &TreeItem::content() const{
    return m_content;
}

void TreeItem::setContent(const std::string &content) {
    if(content != m_content){
        m_content = content;
        emit contentChanged();
    }
}

void TreeItem::setHeader(const std::string &header) {
    if(header != m_header){
        m_header = header;
        emit headerChanged();
    }
}

const std::string &TreeItem::header() const{
    return m_header;
}

const QList<TreeItem *> &TreeItem::childItems() const{
    return m_childItems;
}

const QList<QObject *> TreeItem::childItemsAsQObject() const{
    QList<QObject *> res;
    res.reserve(m_childItems.count());
    for(auto i : m_childItems)
        res.append(i);
    return res;
}

void TreeItem::addChildItem(TreeItem *childItem){
    m_childItems.append(childItem);
    emit childItemsChanged();
    if(m_childItems.count() == 1)
        emit hasChildChanged();
}

void TreeItem::removeChildByIndexChild(int index) {
    m_childItems.removeAt(index);
    if(!m_childItems.empty()) {
        m_childItems.first()->setIsCurrent(true);
    }
    emit contentChanged();
    emit childItemsChanged();
    emit hasChildChanged();
}

bool TreeItem::isOpen() const{
    return m_isOpen;
}

void TreeItem::setIsOpen(bool isOpen){
    if(isOpen != m_isOpen){
        m_isOpen = isOpen;
        emit isOpenChanged();
    }
}

bool TreeItem::isCurrent() const {
    return m_isCurrent;
}

bool TreeItem::isParent() const {
    return m_isParent;
}

void TreeItem::setIsParent(bool parent) {
    m_isParent = parent;
}

void TreeItem::setIsCurrent(bool isCurrent) {
    m_isCurrent = isCurrent;
    emit currentIndexIsChanged(m_isParent, this);
    emit isCurrentChanged();
}

bool TreeItem::hasChild() const{
    return !m_childItems.isEmpty();
}

bool TreeItem::isConnected() {
    return m_isConnected;
}

void TreeItem::setConnected(bool isConnected) {
    m_isConnected = isConnected;
    emit isConnectedChanged();
}
