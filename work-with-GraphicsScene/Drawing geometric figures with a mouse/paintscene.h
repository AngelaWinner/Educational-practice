#ifndef PAINTSCENE_H
#define PAINTSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    //свойство текущего типа используемой фигуры
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)
public:
    explicit PaintScene(QObject* parent = 0);
    ~PaintScene();
    int typeFigure() const; //возвращение текущего типа
    void setTypeFigure(const int type); //установка текущего типа
    enum FigureTypes{
        SquareType, RombType, TriangleType
    };
signals:
    void typeFigureChanged(); //сигнал об изменении типа текущей фигуры
private:
    Figure* tempFigure;
    int m_typeFigure; //текущий тип фигуры
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PAINTSCENE_H
