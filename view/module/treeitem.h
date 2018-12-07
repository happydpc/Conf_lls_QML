#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TreeItem(std::string content, bool isParent, QObject *parent = 0);

    Q_PROPERTY(std::string content READ content NOTIFY contentChanged)
    const std::string & content() const;
    void setContent(const std::string & content);

    Q_PROPERTY(std::string header READ header NOTIFY headerChanged)
    const std::string & header() const;
    void setHeader(const std::string & header);

    Q_PROPERTY(QList<QObject*> childItems READ childItemsAsQObject NOTIFY childItemsChanged)
    const QList<TreeItem *> &childItems() const;
    const QList<QObject *> childItemsAsQObject() const;
    void addChildItem(TreeItem * childItem);

    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    bool isOpen() const;
    void setIsOpen(bool isOpen);

    Q_PROPERTY(bool isConnected READ isConnected WRITE setConnected NOTIFY isConnectedChanged)
    bool isConnected();
    void setConnected(bool isConnected);

    Q_PROPERTY(bool isCurrent READ isCurrent WRITE setIsCurrent NOTIFY isCurrentChanged)
    bool isCurrent() const;
    void setIsCurrent(bool isCurrent);

    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    bool hasChild() const;

    void setIsParent(bool parent);
    bool isParent() const;

    void removeChildByIndexChild(int index);

signals:
    void contentChanged();
    void headerChanged();
    void currentIndexIsChanged(bool isParent, TreeItem *pSender);

    void childItemsChanged();

    void isOpenChanged();
    void isCurrentChanged();
    void isConnectedChanged();

    void hasChildChanged();
public slots:
private:
    std::string m_content;
    std::string m_header;
    QList<TreeItem *> m_childItems;

    bool m_isParent;
    bool m_isOpen;
    bool m_isCurrent;
    bool m_isConnected;
};

#endif // TREEITEM_H
