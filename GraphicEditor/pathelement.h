#ifndef PATHELEMENT_H
#define PATHELEMENT_H
#include <QPointF>
#include <QVector>
#include <QColor>
struct PathElement
{
    QVector<QPointF> pathPoints;
    QColor color;
    int thickness;
    PathElement(QVector<QPointF> pathPointsParameter, QColor colorParameter, int thicknessParameter);
};

#endif // PATHELEMENT_H
