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
    virtual ~Figure();
    QPointF startPoint() const; //стартовая точка
    QPointF endPoint() const; //конечная точка
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    void setColorFigure(const QColor& color);
    QColor getColorFigure() const;
    int getThicknessFigure() const;
    void setThicknessFigure(const int& thickness);
    virtual QString serialize() const = 0; // чисто виртуальный метод
signals:
    void pointChanged();
private:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QRectF boundingRect() const; //область, в которой содержится фигура
    QColor m_color = Qt::black;
    int m_thickness = 2;
public slots:
    void updateRomb();
};

#endif // FIGURE_H
