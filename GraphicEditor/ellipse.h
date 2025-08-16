#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Ellipse : public Figure
{
    Q_OBJECT
public:
    explicit Ellipse(QPointF point, QObject *parent = 0);
    ~Ellipse();

    static Ellipse* deserialize(const QStringList &parts);
    static Ellipse* deserializeBin(QDataStream& in);
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString serializeText() const override;
    void serializeBin(QDataStream& out) const override;
};

#endif // ELLIPSE_H
