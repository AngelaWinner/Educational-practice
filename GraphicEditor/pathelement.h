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
    int layerZ; // добавляем слой
    PathElement(QVector<QPointF> pathPointsParameter, QColor colorParameter, int thicknessParameter, int layerZParameter = 0);
};

#endif // PATHELEMENT_H
