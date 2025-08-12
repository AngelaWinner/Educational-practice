#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    //свойство стартовой точки, относительно которой отрисовываем фигуру
    Q_PROPERTY(QPointF startPoint
                   READ startPoint WRITE setStartPoint
                       NOTIFY pointChanged)
    //свойство конечной точки, до куда отрисовываем фигуру
    Q_PROPERTY(QPointF endPoint
                   READ endPoint WRITE setEndPoint
                       NOTIFY pointChanged)
public:
    explicit Figure(QPointF point, QObject *parent = 0);
    ~Figure();
    QPointF startPoint() const; //стартовая точка
    QPointF endPoint() const; //конечная точка
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    void setColor(const QColor& color);
    QColor getColor() const;
    QColor m_color = Qt::black;
signals:
    void pointChanged();
private:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QRectF boundingRect() const; //область, в которой содержится фигура
public slots:
    void updateRomb();
};

#endif // FIGURE_H
