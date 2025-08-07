#include "subject.h"
#include <math.h>

#include <QPainter>
#include <QGraphicsScene>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Subject::Subject()
    : QGraphicsObject()
{
    setRotation(0);
    state = STOP;
    gameTimer = new QTimer();
    connect(gameTimer, &QTimer::timeout, this, &Subject::slotGameTimer);
    gameTimer->start(5);
    counter = 0;
}

QRectF Subject::boundingRect() const
{
    return QRectF(-20,-25,40,50);
}

void Subject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(0,-25) << QPoint(20,25) << QPoint(-20,25);
    QColor saladColor(144, 238, 144);
    painter->setBrush(saladColor);
    painter->setPen(QPen(Qt::darkGreen, 1));
    painter->drawPolygon(polygon);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Subject::slotGameTimer()
{
    //Проверка выхода за границы поля
    if(state){
        QLineF lineToTarget(QPoint(0,0), mapFromScene(targetWalking));
        if(lineToTarget.length() > 2){
            setPos(mapToParent(0, -2));
        }
        if(this->x() - 30 < 0){
            this->setX(30);
            state = STOP;
        }
        if(this->x() + 30 > 520){
            this->setX(520 - 30);
            state = STOP;
        }

        if(this->y() - 30 < 0){
            this->setY(30);
            state = STOP;
        }
        if(this->y() + 30 > 520){
            this->setY(520 - 30);
            state = STOP;
        }
    }
    if (circles) {
        for (int i = circles->size() - 1; i >= 0; --i) {
            if (circles->at(i)->collidesWithItem(this)) {
                QGraphicsScene *thisScene = this->scene();
                if (thisScene) {
                    thisScene->removeItem(circles->at(i));
                }
                delete circles->at(i); //освободила память
                circles->removeAt(i); //удалила из листа
                counter++;
            }
        }
    }
}

void Subject::setCircles(QList<ColorCircle*> *circlesList) {
    circles = circlesList;
}
int Subject::getCounter() const {
    return counter;
}

void Subject::slotWhereToGo(QPointF point)
{
    targetWalking = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(targetWalking));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    // Поворачиваем фигуру к цели
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }

    state = GO;
}

ColorCircle::ColorCircle(qreal x, qreal y, qreal radius, QColor color) {
    setRect(x - radius, y - radius, 2*radius, 2*radius);
    setBrush(color);
    setPen(Qt::NoPen);
    setFlag(QGraphicsItem::ItemIsSelectable, false); //можно ли выделить? нет
    setFlag(QGraphicsItem::ItemIsMovable, false); //можно ли сдвинуть? нет
}
