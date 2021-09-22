#ifndef MYLINEITEM_H
#define MYLINEITEM_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QRectF>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <QFocusEvent>

class MyLineItem :public QObject , public QGraphicsLineItem
{
    Q_OBJECT
    //Q_INTERFACES(QGraphicsLineItem)
public:
    MyLineItem(qreal x1, qreal y1, qreal x2, qreal y2,int index, QGraphicsItem *parent = nullptr);
    MyLineItem(const QLineF &line, int index,QGraphicsItem *parent = nullptr);
    MyLineItem(int index, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void setIndex(int index);
signals:
    void addNodeItem(int index);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void focusInEvent(QFocusEvent *event);
private:
    bool m_colorFlag;//true:red, flase:black
    int m_index;
};

#endif // MYLINEITEM_H
