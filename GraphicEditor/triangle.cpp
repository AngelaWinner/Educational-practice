#include "triangle.h"
#include <QPainter>
Triangle::Triangle(QPointF point, QObject *parent) : Figure(point, parent) {
    Q_UNUSED(point);
}
Triangle::~Triangle(){}
//реализуем метод отрисовки
void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (fillColorSetted && borderColorSetted) {
        painter->setPen(QPen(getBorderColorFigure(), getThicknessFigure()));
        painter->setBrush(QBrush(getFillColorFigure()));
    } else {
        painter->setPen(QPen(getColorFigure(), getThicknessFigure()));
        painter->setBrush(Qt::NoBrush);
    }
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
    if (fillColorSetted && borderColorSetted) {
        //Формат строки: Triangle;startX;startY;endX;endY;fillColor;borderColor;thickness
        return QString("Triangle;%1;%2;%3;%4;%5;%6;%7")
            .arg(startPoint().x())
            .arg(startPoint().y())
            .arg(endPoint().x())
            .arg(endPoint().y())
            .arg(getFillColorFigure().name())
            .arg(getBorderColorFigure().name())
            .arg(getThicknessFigure());
    }
    // Формат строки: Triangle;startX;startY;endX;endY;colorHex;thickness
    return QString("Triangle;%1;%2;%3;%4;%5;%6")
        .arg(startPoint().x())
        .arg(startPoint().y())
        .arg(endPoint().x())
        .arg(endPoint().y())
        .arg(getColorFigure().name())
        .arg(getThicknessFigure());
}

Triangle* Triangle::deserialize(const QString& data) {
    // Формат строки: Triangle;startX;startY;endX;endY;colorHex;thickness
    QStringList parts = data.split(';');
    if (parts.size() <=6 || parts.size() >=9 || parts[0] != "Triangle") {
        return nullptr;
    }

    bool ok1, ok2, ok3, ok4;
    double startX = parts[1].toDouble(&ok1);
    double startY = parts[2].toDouble(&ok2);
    double endX = parts[3].toDouble(&ok3);
    double endY = parts[4].toDouble(&ok4);
    if (!(ok1 && ok2 && ok3 && ok4)) return nullptr;
    Triangle* triangle = new Triangle(QPointF(startX, startY));
    triangle->setEndPoint(QPointF(endX, endY));
    if (parts.size()==8) {
        //Формат строки: Triangle;startX;startY;endX;endY;fillColor;borderColor;thickness
        QColor fillColor(parts[5]);
        QColor borderColor(parts[6]);
        int thickness = parts[7].toInt();
        triangle->setFillColorFigure(fillColor);
        triangle->setBorderColorFigure(borderColor);
        triangle->setThicknessFigure(thickness);
    }
    if (parts.size()==7) {
        QColor color(parts[5]);
        int thickness = parts[6].toInt();

        triangle->setColorFigure(color);
        triangle->setThicknessFigure(thickness);
    }
    return triangle;
}
