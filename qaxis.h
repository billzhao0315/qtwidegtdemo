#ifndef Curve_H
#define Curve_H


#include <QColor>
#include <QPen>
#include <QTimer>
#include <QGraphicsItem>

#include "curve.h"

class QAxis : public QObject ,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    /**
     * @brief QAxis class
     *
     * Notice: set x and y range before using addData function
     */
    QAxis(double x, double y, double width, double height,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    ~QAxis();
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void clearChart();

    void addCurve(QString title);
    void addData(QString curveName, double tmpX, double tmpY);
    void addVectorData(QString curName, const QVector<QPointF> &data);
    void clearCurveData(QString curveName);

    void setXValueRange(double min, double max);
    void setYValueRange(double min, double max);

    void setXLabels(QString labels);
    void setYLabels(QString labels);

    //QPointF.x(): label, QPointF.y(): label position
    void setXLabels(QString labels, QList<double> pos);
    void setYLabels(QString labels, QList<double> pos);

    void setXTitle(QString title);
    void setYTitle(QString title);
    void setCurveTitleShow(QString curveName, bool f);

    Curve* getCurve(QString name);
    void setCurveLineStyle(QString name, Qt::PenStyle style);
    void setCurvePointSize(QString name, double size);

    //NOTE: Use it after finishing adding data
    void setGridShow(bool f);

    void setDirection(QString d);

    //axis: X or Y
    void setAutoScale(QString axis, bool f);

    void setAxisSize(double width, double height);

    void addTargetLine(QString lineName);

    void upDate();

    inline double getAxisXmin()
    {
        return m_xMin;
    }

    inline double getAxisXmax()
    {
        return m_xMax;
    }

    inline double getAxisYmin()
    {
        return m_yMin;
    }

    inline double getAxisYmax()
    {
        return m_yMax;
    }

private:

    void initXYState();
    void upDateXLabels();
    void upDateYLabels();
    QVector<QPointF> m_data;
    //QList<Curve*> m_curveList;
    QMap<QString, Curve*> m_curveList;

    QPainter *m_painter;

    double m_xMin;
    double m_xMax;

    double m_yMin;
    double m_yMax;

    double m_xPosMin;
    double m_xPosMax;

    double m_yPosMin;
    double m_yPosMax;

    double m_xRange;
    double m_yRange;

    double m_xValueRange;
    double m_yValueRange;

    QString m_direction;

    QString m_xTitle;
    QString m_yTitle;

    QString m_xLabels;
    QString m_yLabels;

    QList<double> m_xLabelsPos;
    QList<double> m_yLabelsPos;

    bool m_xAutoScale;
    bool m_yAutoScale;

    bool m_gridFlag;

    bool m_firstPoint;

    double m_xLabelLinePenSize;
    double m_xLabelTextPenSize;
    double m_yLabelLinePenSize;
    double m_yLabelTextPenSize;

    int m_dataSize;

    QVector<QPointF> m_testData;// for test

    bool m_xExpandFlag;
    bool m_yExpandFlag;
};

#endif
