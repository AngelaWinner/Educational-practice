#include "pathelement.h"

//PathElement::PathElement() {}
PathElement::PathElement(QVector<QPointF> pathPointsParameter, QColor colorParameter, int thicknessParameter, int layerZParameter)
    : pathPoints(pathPointsParameter), color(colorParameter), thickness(thicknessParameter), layerZ(layerZParameter) {}
