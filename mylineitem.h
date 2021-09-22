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

class MyLineItem : public QGraphicsLineItem
{
public:
    MyLineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);
    MyLineItem(const QLineF &line, QGraphicsItem *parent = nullptr);
    MyLineItem(QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    bool m_colorFlag;//true:red, flase:black
};

#endif // MYLINEITEM_H
