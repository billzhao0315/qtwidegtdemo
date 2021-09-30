#ifndef CURVE_H
#define CURVE_H

#include <QPen>
#include <QString>
#include "myitem.h"
#include "mylineitem.h"
#include <mutex>
class QGraphicsScene;
class Curve: public QObject
{
    Q_OBJECT
public:
    Curve(QString title, QGraphicsScene *scene);

    void setTitle(QString title);
    void setTitleShow(bool flag);
    void setLinePen(QPen pen);
    void setPointSize(double size);
    void setPointPen(QPen pen);
    void setPointColor(const QColor color);
    void setCurveColor(const QColor color);
    void setCurveStyle(Qt::PenStyle style);
    void addData(QPointF d);
    void addPosData(QPointF p);
    void setRawData(const QVector<QPointF>& data, int size);
    void resetPosData(int index, QPointF p);

    QString getTitle();
    bool getTitleShow();
    QPointF getData(int index);
    QPointF getPosData(int index);
    QPen getLinePen();
    QPen getPointPen();
    int getDataSize();

    void clearData();
    int  getRadius();
    void setOriginPoint(double x, double y);
    QVector<MyItem*> getPosPointData();
    QVector<MyLineItem*> getPosSegmentData();
public slots:
    void posChanged(int index);
    void addNodeItem(int index);

private:
    QString m_title;
    bool m_titleShow;
    QPen m_linePen;
    QPen m_pointPen;
    int m_penStyle;
    QVector<QPointF> m_data;
    QVector<MyItem*> m_posPointData;
    QVector<MyLineItem*> m_posSegmentData;
    QGraphicsScene *m_scene;
    double m_xOrigin;
    double m_yOrigin;

    std::mutex m_mutex;
    int m_dataSize;
};

#endif
