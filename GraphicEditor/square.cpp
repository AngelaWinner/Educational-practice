#include "square.h"

#include <QPainter>
Square::Square(QPointF point, QObject *parent) : Figure(point, parent) {
    setEndPoint(point);
    //Q_UNUSED(point);
}
/*Square::Square(QPointF point, double size, QObject *parent)
    : Figure(point, parent)
{
    // устанавливаем endPoint, чтобы квадрат был со стороной size
    setEndPoint(QPointF(point.x() + size, point.y() + size));
}*/
Square::~Square(){}
//реализуем метод отрисовки
void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(getColorFigure(), getThicknessFigure()));
    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));
    painter->drawRect(rect);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString Square::serialize() const {
    double width = qAbs(endPoint().x() - startPoint().x());
    double height = qAbs(endPoint().y() - startPoint().y());
    return QString("Square;%1;%2;%3;%4;%5;%6")
        .arg(startPoint().x())
        .arg(startPoint().y())
        .arg(width)
        .arg(height)
        .arg(getColorFigure().name())
        .arg(getThicknessFigure());
}
