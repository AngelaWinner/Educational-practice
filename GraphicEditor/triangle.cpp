#include "triangle.h"
#include <QPainter>
Triangle::Triangle(QPointF point, QObject *parent) : Figure(point, parent) {
    Q_UNUSED(point);
}
Triangle::~Triangle(){}
//реализуем метод отрисовки
void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(getColor(), 2));
    QPolygonF polygon;
    polygon<<QPointF(startPoint().x()+(endPoint().x() > startPoint().x() ? +1 : -1)*
                                              abs((endPoint().x()-startPoint().x())/2), startPoint().y())
            <<QPointF((endPoint().x() > startPoint().x() ? endPoint().x() : startPoint().x()), endPoint().y())
            <<QPointF((endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x()), endPoint().y());
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString Triangle::serialize() const {
    // Формат: Triangle;startX;startY;endX;endY;colorHex
    return QString("Triangle;%1;%2;%3;%4;%5")
        .arg(startPoint().x())
        .arg(startPoint().y())
        .arg(endPoint().x())
        .arg(endPoint().y())
        .arg(getColor().name());
}

Triangle* Triangle::deserialize(const QString& data) {
    // Формат строки: Triangle;startX;startY;endX;endY;colorHex
    QStringList parts = data.split(';');
    if (parts.size() != 6 || parts[0] != "Triangle")
        return nullptr;

    bool ok1, ok2, ok3, ok4;
    double startX = parts[1].toDouble(&ok1);
    double startY = parts[2].toDouble(&ok2);
    double endX = parts[3].toDouble(&ok3);
    double endY = parts[4].toDouble(&ok4);
    QColor color(parts[5]);

    if (!(ok1 && ok2 && ok3 && ok4))
        return nullptr;

    Triangle* triangle = new Triangle(QPointF(startX, startY));
    triangle->setEndPoint(QPointF(endX, endY));
    triangle->setColor(color);
    return triangle;
}
