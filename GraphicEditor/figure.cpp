#include "figure.h"
#include <QPainter>
Figure::Figure(QPointF point, QObject *parent) :
    QObject(parent), QGraphicsItem() {
    //устанавливаем стартовую координату для отрисовки фигуры
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    connect(this, &Figure::pointChanged, this, &Figure::updateRomb);
}
Figure::~Figure() {}
QRectF Figure :: boundingRect() const{
    //возвращаем область, в которой лежит фигура
    return QRectF(((endPoint().x()>startPoint().x() ? startPoint().x() : endPoint().x())-5),
                  ((endPoint().y()>startPoint().y() ? startPoint().y() : endPoint().y())-5),
                  qAbs(endPoint().x()-startPoint().x())+10,
                  qAbs(endPoint().y()-startPoint().y())+10);

}
void Figure::updateRomb(){
    this->update(((endPoint().x()>startPoint().x() ? startPoint().x() : endPoint().x())-5),
                 ((endPoint().y()>startPoint().y() ? startPoint().y() : endPoint().y())-5),
                 qAbs(endPoint().x()-startPoint().x())+10,
                 qAbs(endPoint().y()-startPoint().y())+10);
}
void Figure::setStartPoint(const QPointF point) {
    m_startPoint = mapFromScene(point);
    emit pointChanged();
}
void Figure::setEndPoint(const QPointF point) {
    m_endPoint = mapFromScene(point);
    emit pointChanged();
}
QPointF Figure:: startPoint() const{
    return m_startPoint;
}
QPointF Figure:: endPoint() const{
    return m_endPoint;
}

void Figure::setColorFigure(const QColor& color) {
    m_color = color;
    update(); // перерисовать
}

QColor Figure::getColorFigure() const {
    return m_color;
}

int Figure::getThicknessFigure() const {
    return m_thickness;
}
void Figure::setThicknessFigure(const int& thickness) {
    m_thickness = thickness;
    update(); // перерисовать
}

void Figure::setFillColorFigure(QColor fillColor) {
    m_fillColor = fillColor;
    fillColorSetted = true;
}
void Figure::setBorderColorFigure(QColor borderColor) {
    m_borderColor = borderColor;
    borderColorSetted = true;
}

QColor Figure::getFillColorFigure() const {
    return m_fillColor;
}
QColor Figure::getBorderColorFigure() const {
    return m_borderColor;
}
