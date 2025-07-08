#ifndef PAINTSCENE_H
#define PAINTSCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
class paintscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit paintscene(QObject* parent = 0);
    ~paintscene();
private:
    QPointF previousPoint; //координаты предыдущей точки
private:
    //для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PAINTSCENE_H
