#include "customgraphicsscene.h"
#include "triangle.h"
#include "square.h"

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent) {}
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
                QPen(drawingColor, 10, Qt::SolidLine, Qt::RoundCap));
        previousPoint=event->scenePos();

        currentPath.append(event->scenePos());

        return;
    }
    if (tempFigure) {
        tempFigure->setColor(drawingColor);
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
        QPen pen(drawingColor, 2);
        currentLineDrawingRude->setPen(pen);
        addItem(currentLineDrawingRude);
        return; // не передаем дальше
    }

    if (m_isDrawingRender) {
        addEllipse(event->scenePos().x()-5,
                   event->scenePos().y()-5,
                   10,10,
                   QPen(Qt::NoPen), QBrush(drawingColor));
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
        return; // не передаем дальше
    }

    if (m_isDrawingRender) {
        paths.append(QPair(currentPath, drawingColor));
        currentPath.clear();
    }

    // Остальной код (если нужен)
    QGraphicsScene::mouseReleaseEvent(event);
}

void CustomGraphicsScene::setDrawingColor(const QColor& color) {
    drawingColor = color;
}

QString CustomGraphicsScene::serializePath(const QPair<QVector<QPointF>, QColor>& path) {
    //QString result;
    //for (const auto& path : paths) {
    QStringList pointStrings;
    pointStrings << "Path";
    pointStrings << path.second.name(); // цвет в HEX
    for (const QPointF& pt : path.first) {
        pointStrings << QString("%1,%2").arg(pt.x()).arg(pt.y());
    }
    //result += pointStrings.join(";") + "\n"; // разделяем точки запятой, а пути — новой строкой
    //}
    return pointStrings.join(";");
}

QVector<QPointF> CustomGraphicsScene::deserializePath(QStringList parts) {
    QVector<QPointF> pathPoints;
    // parts[0] = "Path"
    // parts[1] = цвет
    // остальные = точки
    for (int i = 2; i < parts.size(); ++i) {
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
