#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Square : public Figure
{
    Q_OBJECT
public:
    explicit Square(QPointF point, QObject *parent = 0);
    ~Square();
    static Square* deserialize(const QStringList& parts);
    static Square* deserializeBin(QDataStream& in);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString serializeText() const override;
    void serializeBin(QDataStream& out) const override;
};

#endif // SQUARE_H

