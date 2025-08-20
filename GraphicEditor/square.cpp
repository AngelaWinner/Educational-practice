#include "square.h"

#include <QPainter>
Square::Square(QPointF point, QObject *parent) : Figure(point, parent) {
    setEndPoint(point);
    //Q_UNUSED(point);
}
Square::~Square(){}
//реализуем метод отрисовки
void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (fillColorSetted && borderColorSetted) {
        painter->setPen(QPen(getBorderColorFigure(), getThicknessFigure()));
        painter->setBrush(QBrush(getFillColorFigure()));
    } else {
        painter->setPen(QPen(getColorFigure(), getThicknessFigure()));
        painter->setBrush(Qt::NoBrush);
    }
    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));
    painter->drawRect(rect);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QString Square::serializeText() const {
    double width = (endPoint().x() - startPoint().x());
    double height = (endPoint().y() - startPoint().y());

    if(fillColorSetted && borderColorSetted) {
            return QString("Square;%1;%2;%3;%4;%5;%6;%7")
                .arg(startPoint().x())
                .arg(startPoint().y())
                .arg(width)
                .arg(height)
                .arg(getFillColorFigure().name())
                .arg(getBorderColorFigure().name())
                .arg(getThicknessFigure());
    } else
        return QString("Square;%1;%2;%3;%4;%5;%6")
            .arg(startPoint().x())
            .arg(startPoint().y())
            .arg(width)
            .arg(height)
            .arg(getColorFigure().name())
            .arg(getThicknessFigure());
}

void Square::serializeBin(QDataStream& out) const {
    out << QString("Square");
    if (fillColorSetted && borderColorSetted) {
        out << QString("1");
    } else out << QString("0");

    // Записываем начальные координаты
    out << startPoint().x() << startPoint().y();

    // Вычисляем размеры
    double width = (endPoint().x() - startPoint().x());
    double height = (endPoint().y() - startPoint().y());

    // Записываем размеры
    out << width << height;

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


Square* Square::deserialize(const QStringList& parts) {
    if (parts[0] != "Square" || parts.size() < 7 || parts.size() > 8) return nullptr;
    bool ok1, ok2, ok3, ok4;
    double startX = parts[1].toDouble(&ok1);
    double startY = parts[2].toDouble(&ok2);
    double width = parts[3].toDouble(&ok3);
    double height = parts[4].toDouble(&ok4);
    if (!(ok1 && ok2 && ok3 && ok4)) return nullptr;
    QPointF startPoint(startX, startY);
    QPointF endPoint(startX + width, startY + height);
    Square* square = new Square(startPoint);
    square->setEndPoint(endPoint);

    if (parts.size()==8) {
        // Формат: Square;startX;startY;width;height;fillColor;borderColor;Thickness
        QString fillColorStr = parts[5];
        QString borderColorStr = parts[6];
        int thickness = parts[7].toInt();
        square->setFillColorFigure(QColor(fillColorStr));
        square->setBorderColorFigure(QColor(borderColorStr));
        square->setThicknessFigure(thickness);
    }
    if (parts.size()==7) {
        // Формат: Square;startX;startY;width;height;colorHex;Thickness
        QString colorStr = parts[5];
        int thickness = parts[6].toInt();
        square->setColorFigure(QColor(colorStr));
        square->setThicknessFigure(thickness);
    }
    return square;
}


Square* Square::deserializeBin(QDataStream& in) {
    QString value;
    double startX, startY, width, height;
    in>>value>>startX>>startY>>width>>height;
    QPointF startPoint(startX, startY);
    QPointF endPoint(startX + width, startY + height);
    Square* square = new Square(startPoint);
    square->setEndPoint(endPoint);
    if (value == "1") {
        QString fillColorStr, borderColorStr;
        in>>fillColorStr>>borderColorStr;
        square->setFillColorFigure(QColor(fillColorStr));
        square->setBorderColorFigure(QColor(borderColorStr));
    } else {
        QString colorStr;
        in>>colorStr;
        square->setColorFigure(QColor(colorStr));
    }
    int thickness;
    in>>thickness;
    square->setThicknessFigure(thickness);
    if (square) {
        return square;
    } else return nullptr;
}

