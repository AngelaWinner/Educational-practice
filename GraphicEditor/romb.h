#ifndef ROMB_H
#define ROMB_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Romb : public Figure
{
    Q_OBJECT
public:
    explicit Romb(QPointF point, QObject *parent = 0);
    ~Romb();
    static Romb* deserialize(const QString &data);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString serialize() const override;
};

#endif // ROMB_H
