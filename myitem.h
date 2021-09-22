#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsSceneDragDropEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QRectF>
#include <QPen>


class MyItem :public QObject ,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    MyItem(double radius, double Radius, int index);
    ~MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void setIndex(int index);
    void updateRadius(double radius);
    signals:
    void posChanged(int index);


protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    double m_radius;
    double m_Radius;

    bool m_colorFlag;//true:red, flase:black
    int m_index;

};

#endif // MYITEM_H
