#include "pathelement.h"

//PathElement::PathElement() {}
PathElement::PathElement(QVector<QPointF> pathPointsParameter, QColor colorParameter, int thicknessParameter)
    : pathPoints(pathPointsParameter), color(colorParameter), thickness(thicknessParameter) {}
