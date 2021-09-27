#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

class MyQGraphicsView : public QGraphicsView
{
public:
    MyQGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    MyQGraphicsView(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYQGRAPHICSVIEW_H
