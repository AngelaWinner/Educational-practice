#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QTimer>
#include <QGraphicsObject>

#define GO true
#define STOP false

class Subject : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Subject();
    void setCircles(QList<class ColorCircle*> *circlesList);
    int counter;
    int getCounter() const;
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void slotWhereToGo(QPointF point);
private:
    QTimer *gameTimer;
    QPointF targetWalking; //цель
    bool state;
    QList<ColorCircle*> *circles; //указатель на лист, содержащий указатели
private slots:
    void slotGameTimer();
};

// Класс цветного кружочка
class ColorCircle : public QGraphicsEllipseItem {
public:
    explicit ColorCircle(qreal x, qreal y, qreal radius, QColor color);
};


#endif // SUBJECT_H
