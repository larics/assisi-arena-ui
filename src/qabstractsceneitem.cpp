#include "qabstractsceneitem.h"
#include "qabstracttreeitem.h"

using namespace zmqData;

void QAbstractSceneItem::recursiveSetHidden(bool state)
{
    if (isGroup())
        for(auto& item : childItems())
            sCast(item)->recursiveSetHidden(state);
    else {
        _treeItem->setHidden(state);
        if(state) tCast(_treeItem)->resetSelection();
    }
}

QVariant QAbstractSceneItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value){
    if(change == QGraphicsItem::ItemSelectedHasChanged){
        recursiveSetHidden(!value.toBool());
        _treeItem->setHidden(!value.toBool());
        if(!value.toBool()) tCast(_treeItem)->resetSelection();
    }
    return QGraphicsItem::itemChange(change, value);
}

QAbstractSceneItem::QAbstractSceneItem() :
    _inGroup(false),
    _groupColor(Qt::black)
{
    this->setFlag(GraphicsItemFlag::ItemIsSelectable);
}

void QAbstractSceneItem::setInGroup(bool state){
    _inGroup = state;
}

void QAbstractSceneItem::setTreeItem(QTreeWidgetItem *treeItem)
{
    _treeItem = treeItem;
}

void QAbstractSceneItem::deleteTreeItem()
{
    delete _treeItem;
}

void QAbstractSceneItem::setGroupColor(const QColor &color){
    _groupColor = color;
}

QPainterPath QAbstractSceneItem::shape() const
{
    QPainterPath out;
    out.addRect(boundingRect());
    return out;
}

QPainterPath QAbstractSceneItem::completeShape() const
{
    return shape();
}
