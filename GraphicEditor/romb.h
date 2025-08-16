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
    static Romb* deserialize(const QStringList &parts);
    static Romb* deserializeBin(QDataStream& in);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString serializeText() const override;
    void serializeBin(QDataStream& out) const override;
};

#endif // ROMB_H
