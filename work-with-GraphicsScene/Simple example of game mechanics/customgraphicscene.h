#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomGraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomGraphicScene(QObject *parent = 0);
    ~CustomGraphicScene();

signals:
    // Сигнал для передачи координат положения курсора мыши
    void signalGetCoordinate(QPointF point);

public slots:

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
