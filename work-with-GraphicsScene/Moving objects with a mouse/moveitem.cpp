#include "moveitem.h"

MoveItem::MoveItem(QString string, QObject *parent) :
    QObject(parent), QGraphicsItem(), name(string)
{

}

MoveItem::~MoveItem()
{

}
QRectF MoveItem::boundingRect() const
{
    if (name=="romb") return QRect (-30,-40,60,80);
    if (name=="figure") return QRect (-40,-40,80,80);
    //if (name=="star") return QRect (-40,-40,80,80);
    else return QRect (-40,-40,80,80);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    if (name=="romb") {
        painter->setBrush(Qt::cyan);
        QPolygonF romb;
        romb << QPointF(0, -40)
             << QPointF(30, 0)
             << QPointF(0, 40)
             << QPointF(-30, 0);
        painter->drawPolygon(romb);
    }   if (name=="star") {
        painter->setBrush(Qt::blue);
        QPolygonF star;
        star << QPointF(-10, 0)
               << QPointF(-40, 40)
               << QPointF(0, 10)
               << QPointF(40, 40)
               << QPointF(10, 0)
               << QPointF(40, -40)
               << QPointF(0, -10)
               << QPointF(-40, -40);
        painter->drawPolygon(star);
    } if (name=="figure") {
        painter->setBrush(Qt::magenta);
        QPolygonF figure;

        figure << QPointF(-40, 0)
               << QPointF(-30, 30)
               << QPointF(0, 40)
               << QPointF(30, 30)
               << QPointF(40, 0)
               << QPointF(30, -30)
               << QPointF(0, -40)
               << QPointF(-30, -30);
        painter->drawPolygon(figure);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
