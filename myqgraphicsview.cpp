#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QGraphicsScene *scene, QWidget *parent):QGraphicsView(scene, parent)
{

}

MyQGraphicsView::MyQGraphicsView(QWidget *parent):QGraphicsView(parent)
{

}

void MyQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    this->setToolTip("pos:(" + QString::number(event->x()) + "," + QString::number(event->y()) + ")");
    QGraphicsView::mousePressEvent(event);
}
