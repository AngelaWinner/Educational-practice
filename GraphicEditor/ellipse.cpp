#include "ellipse.h"
#include <QPainter>

Ellipse::Ellipse(QPointF point, QObject *parent) : Figure(point, parent) {
    // Можно оставить пустым или инициализировать что-то
}

Ellipse::~Ellipse() {}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (fillColorSetted && borderColorSetted) {
        painter->setPen(QPen(getBorderColorFigure(), getThicknessFigure()));
        painter->setBrush(QBrush(getFillColorFigure()));
    } else {
        painter->setPen(QPen(getColorFigure(), getThicknessFigure()));
        painter->setBrush(Qt::NoBrush);
    }

    // Вычисляем прямоугольник для эллипса
    qreal x1 = startPoint().x();
    qreal y1 = startPoint().y();
    qreal x2 = endPoint().x();
    qreal y2 = endPoint().y();

    qreal left = qMin(x1, x2);
    qreal top = qMin(y1, y2);
    qreal width = qAbs(x2 - x1);
    qreal height = qAbs(y2 - y1);

    QRectF rect(left, top, width, height);
    painter->drawEllipse(rect);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString Ellipse::serializeText() const {
    if (fillColorSetted && borderColorSetted) {
        // Формат: Ellipse;startX;startY;endX;endY;fillColor;borderColor;thickness
        return QString("Ellipse;%1;%2;%3;%4;%5;%6;%7")
            .arg(startPoint().x())
            .arg(startPoint().y())
            .arg(endPoint().x())
            .arg(endPoint().y())
            .arg(getFillColorFigure().name())
            .arg(getBorderColorFigure().name())
            .arg(getThicknessFigure());
    }
    // Формат: Ellipse;startX;startY;endX;endY;colorHex;thickness
    return QString("Ellipse;%1;%2;%3;%4;%5;%6")
        .arg(startPoint().x())
        .arg(startPoint().y())
        .arg(endPoint().x())
        .arg(endPoint().y())
        .arg(getColorFigure().name())
        .arg(getThicknessFigure());
}

void Ellipse::serializeBin(QDataStream& out) const {
    out << QString("Ellipse");
    if (fillColorSetted && borderColorSetted) {
        out << QString("1"); //1 если два цвета, 0  если один
    } else out << QString("0");

    // Записываем начальные координаты
    out << startPoint().x() << startPoint().y();
    out << endPoint().x() << endPoint().y();
    // Записываем цветовые параметры
    if (fillColorSetted && borderColorSetted) {
        out << getFillColorFigure().name()
        << getBorderColorFigure().name();
    } else {
        out << getColorFigure().name();
    }
    // Записываем толщину линии
    out << getThicknessFigure();
}

Ellipse* Ellipse::deserialize(const QStringList &parts) {
    // Проверка формата
    if (parts.size() != 8 && parts.size() != 7) {
        return nullptr;
    }
    if (parts[0] != "Ellipse") {
        return nullptr;
    }

    bool ok1, ok2, ok3, ok4;
    double startX = parts[1].toDouble(&ok1);
    double startY = parts[2].toDouble(&ok2);
    double endX = parts[3].toDouble(&ok3);
    double endY = parts[4].toDouble(&ok4);

    if (!(ok1 && ok2 && ok3 && ok4))
        return nullptr;

    Ellipse* ellipse = new Ellipse(QPointF(startX, startY));
    ellipse->setEndPoint(QPointF(endX, endY));

    if (parts.size() == 8) {
        // fillColor и borderColor заданы
        QColor fillColor(parts[5]);
        QColor borderColor(parts[6]);
        int thickness = parts[7].toInt();
        ellipse->setFillColorFigure(fillColor);
        ellipse->setBorderColorFigure(borderColor);
        ellipse->setThicknessFigure(thickness);
    } else {
        // Только основной цвет
        QColor color(parts[5]);
        int thickness = parts[6].toInt();
        ellipse->setColorFigure(color);
        ellipse->setThicknessFigure(thickness);
    }

    return ellipse;
}


Ellipse* Ellipse::deserializeBin(QDataStream& in) {
    QString value;
    double startX, startY, endX, endY;
    in>>value>>startX>>startY>>endX>>endY;

    Ellipse* ellipse = new Ellipse(QPointF(startX, startY));
    ellipse->setEndPoint(QPointF(endX, endY));
    if (value == "1") {
        QString fillColorStr, borderColorStr;
        in>>fillColorStr>>borderColorStr;
        ellipse->setFillColorFigure(QColor(fillColorStr));
        ellipse->setBorderColorFigure(QColor(borderColorStr));
    } else {
        QString colorStr;
        in>>colorStr;
        ellipse->setColorFigure(QColor(colorStr));
    }
    int thickness;
    in>>thickness;
    ellipse->setThicknessFigure(thickness);
    if (ellipse) {
        return ellipse;
    } else return nullptr;
}
