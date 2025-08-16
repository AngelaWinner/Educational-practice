#include "romb.h"
#include <QPainter>
Romb::Romb(QPointF point, QObject *parent) : Figure(point, parent) {
    Q_UNUSED(point);
}
Romb::~Romb(){}
//реализуем метод отрисовки
void Romb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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
            <<QPointF(endPoint().x(), startPoint().y() + (endPoint().y() > startPoint().y() ? +1 : -1)*
                                                              abs((endPoint().y()-startPoint().y())/2))
            <<QPointF(startPoint().x()+(endPoint().x() > startPoint().x() ? +1 : -1)*
                                              abs((endPoint().x()-startPoint().x())/2), endPoint().y())
            <<QPointF(startPoint().x(), startPoint().y() + (endPoint().y() > startPoint().y() ? +1 : -1)*
                                                                abs((endPoint().y()-startPoint().y())/2));
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString Romb::serialize() const {
    // Формат: Romb;startX;startY;endX;endY;colorHex;thickness
    if (fillColorSetted && borderColorSetted) {
        //Формат строки: Romb;startX;startY;endX;endY;fillColor;borderColor;thickness
        return QString("Romb;%1;%2;%3;%4;%5;%6;%7")
            .arg(startPoint().x())
            .arg(startPoint().y())
            .arg(endPoint().x())
            .arg(endPoint().y())
            .arg(getFillColorFigure().name())
            .arg(getBorderColorFigure().name())
            .arg(getThicknessFigure());
    }
    // Формат строки: Romb;startX;startY;endX;endY;colorHex;thickness
    return QString("Romb;%1;%2;%3;%4;%5;%6")
        .arg(startPoint().x())
        .arg(startPoint().y())
        .arg(endPoint().x())
        .arg(endPoint().y())
        .arg(getColorFigure().name())
        .arg(getThicknessFigure());
}

Romb* Romb::deserialize(const QString& data) {
    // Формат строки: Triangle;startX;startY;endX;endY;colorHex;thickness
    QStringList parts = data.split(';');
    if (parts.size() <=6 || parts.size() >=9 || parts[0] != "Romb") {
        return nullptr;
    }

    bool ok1, ok2, ok3, ok4;
    double startX = parts[1].toDouble(&ok1);
    double startY = parts[2].toDouble(&ok2);
    double endX = parts[3].toDouble(&ok3);
    double endY = parts[4].toDouble(&ok4);

    if (!(ok1 && ok2 && ok3 && ok4)) return nullptr;
    Romb* romb = new Romb(QPointF(startX, startY));
    romb->setEndPoint(QPointF(endX, endY));
    if (parts.size()==8) {
        QColor fillColor(parts[5]);
        QColor borderColor(parts[6]);
        int thickness = parts[7].toInt();
        romb->setFillColorFigure(fillColor);
        romb->setBorderColorFigure(borderColor);
        romb->setThicknessFigure(thickness);
    }
    if (parts.size()==7) {
        QColor color(parts[5]);
        int thickness = parts[6].toInt();

        romb->setColorFigure(color);
        romb->setThicknessFigure(thickness);
    }
    return romb;
}
