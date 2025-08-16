#include "customgraphicsscene.h"
#include "triangle.h"
#include "square.h"
#include "romb.h"

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent) {
    thicknessScene = 2;
}
CustomGraphicsScene::~CustomGraphicsScene(){}
int CustomGraphicsScene::typeFigure() const{
    return m_typeFigure;
}
void CustomGraphicsScene::setTypeFigure(const int type){
    m_typeFigure = type;
}
void CustomGraphicsScene::setDrawingRenderMode(bool enabled) {
    m_isDrawingRender = enabled;
}
bool CustomGraphicsScene::isDrawingRenderMode() const {
    return m_isDrawingRender;
}
void CustomGraphicsScene::setDrawingRudeMode(bool enabled) {
    m_isDrawingRude = enabled;
}
bool CustomGraphicsScene::isDrawingRudeMode() const {
    return m_isDrawingRude;
}
void CustomGraphicsScene::setFillColorScene(QColor fillColor) {
    fillColorScene = fillColor;
    fillColorFlagScene = true;
}
void CustomGraphicsScene::setBorderColorScene(QColor borderColor) {
    borderColorScene = borderColor;
    borderColorFlagScene = true;
}
void CustomGraphicsScene::changeFillFlagScene(bool TF) {
    fillColorFlagScene = TF;
}
void CustomGraphicsScene::changeBorderFlagScene(bool TF) {
    borderColorFlagScene = TF;
}
void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if (m_isDrawingRude && currentLineDrawingRude) {
        // Обновляем конечную точку линии
        QLineF newLine(currentLineDrawingRude->line().p1(), event->scenePos());
        currentLineDrawingRude->setLine(newLine);

        return; // не передаем дальше
    }
    if (m_isDrawingRender) {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(сolorScene, thicknessScene, Qt::SolidLine, Qt::RoundCap));
        previousPoint=event->scenePos();

        currentPath.append(event->scenePos());

        return;
    }
    if (tempFigure) {
        tempFigure->setColorFigure(сolorScene);
        tempFigure->setThicknessFigure(thicknessScene);

        if (fillColorFlagScene && borderColorFlagScene) {
            tempFigure->setFillColorFigure(fillColorScene);
            tempFigure->setBorderColorFigure(borderColorScene);
        }

        //устанавливаем конечную координату положения мыши в текущую отрисовываемую фигуру
        tempFigure->setEndPoint(event->scenePos());
        //обновляем содержимое сцены
        this->update(QRectF(0,0, this->width(), this->height()));
    }
}
void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event){

    if (m_isDrawingRude) {
        // Начинаем рисовать линию
        currentLineDrawingRude = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
        QPen pen(сolorScene, thicknessScene);
        currentLineDrawingRude->setPen(pen);
        addItem(currentLineDrawingRude);

        rudeLinePointVector.append(event->scenePos());
        return; // не передаем дальше
    }

    if (m_isDrawingRender) {
        addEllipse(event->scenePos().x()-thicknessScene/2,
                   event->scenePos().y()-thicknessScene/2,
                   thicknessScene,thicknessScene,
                   QPen(Qt::NoPen), QBrush(сolorScene));
        previousPoint=event->scenePos();

        currentPath.append(event->scenePos()); //заполняю массив точек

        return;
    }

    switch(m_typeFigure){
    case SquareType: {
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case TriangleType: {
        Triangle *item = new Triangle(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case RombType: {
        Romb *item = new Romb(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    default:{
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    }
    this->addItem(tempFigure);
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (m_isDrawingRude && currentLineDrawingRude) {
        // Завершаем рисование линии
        currentLineDrawingRude = nullptr;

        rudeLinePointVector.append(event->scenePos());
        PathElement line(rudeLinePointVector, сolorScene, thicknessScene);
        drawRudeLines.append(line);
        rudeLinePointVector.clear();
        return; // не передаем дальше
    }

    if (m_isDrawingRender) {
        PathElement path(currentPath, сolorScene, thicknessScene);
        paths.append(path);
        currentPath.clear();
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void CustomGraphicsScene::setColorScene(const QColor& color) {
    сolorScene = color;
}
void CustomGraphicsScene::setThicknessScene(int thickness) {
    thicknessScene = thickness;
}
QString CustomGraphicsScene::serializePath(const PathElement& path) {
    QStringList pointStrings;
    pointStrings << "Path";
    pointStrings << path.color.name(); // цвет в HEX
    pointStrings << QString::number(path.thickness);
    for (const QPointF& pt : path.pathPoints) {
        pointStrings << QString("%1,%2").arg(pt.x()).arg(pt.y());
    }
    return pointStrings.join(";");
}

QVector<QPointF> CustomGraphicsScene::deserializePath(QStringList parts) {
    QVector<QPointF> pathPoints;
    // parts[0] = "Path"
    // parts[1] = цвет
    // parts[2] = толщина
    // остальные = точки
    for (int i = 3; i < parts.size(); ++i) {
        QStringList coords = parts[i].split(',', Qt::SkipEmptyParts);
        if (coords.size() == 2) {
            bool okX, okY;
            double x = coords[0].toDouble(&okX);
            double y = coords[1].toDouble(&okY);
            if (okX && okY) {
                pathPoints.append(QPointF(x, y));
            }
        }
    }
    return pathPoints;
}

QString CustomGraphicsScene::serializeCurve (const PathElement& line) { //метод сериализации кривой
    QStringList linesList;
    // linesList[0] = "Curve"
    // linesList[1] = color
    // linesList[2] = thickness
    linesList << "Curve";
    linesList << line.color.name(); // цвет в HEX
    linesList << QString::number(line.thickness);
    // Для каждой линии в QVector, хранящем точки
    for (const QPointF& pt : line.pathPoints) {
        linesList << QString("%1,%2").arg(pt.x()).arg(pt.y());
    }
    return linesList.join(";");
}

QVector<QPointF> CustomGraphicsScene::deserializeCurve(QStringList parts) {
    QVector<QPointF> pathPoints;
    // parts[0] = "Curve"
    // остальные = точки
    for (int i = 1; i < parts.size(); ++i) {
        QStringList coords = parts[i].split(',', Qt::SkipEmptyParts);
        if (coords.size() == 2) {
            bool okX, okY;
            double x = coords[0].toDouble(&okX);
            double y = coords[1].toDouble(&okY);
            if (okX && okY) {
                pathPoints.append(QPointF(x, y));
            }
        }
    }
    return pathPoints;
}
