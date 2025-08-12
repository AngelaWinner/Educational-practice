#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    //свойство текущего типа используемой фигуры
    Q_PROPERTY(int typeFigure
                   READ typeFigure WRITE setTypeFigure
                       NOTIFY typeFigureChanged)
public:
    explicit CustomGraphicsScene(QObject* parent = 0);
    ~CustomGraphicsScene();
    int typeFigure() const; //возвращение текущего типа
    void setTypeFigure(const int type); //установка текущего типа
    enum FigureTypes{
        SquareType, TriangleType
    };

    void setDrawingRenderMode(bool enabled); // включение/выключение режима плавного рисования
    bool isDrawingRenderMode() const;
    void setDrawingRudeMode(bool enabled); // включение/выключение режима жесткого рисования
    bool isDrawingRudeMode() const;

    void setDrawingColor(const QColor& color);
    QColor drawingColor = Qt::red;
signals:
    void typeFigureChanged(); //сигнал об изменении типа текущей фигуры
private:
    Figure* tempFigure;
    int m_typeFigure; //текущий тип фигуры
    bool m_isDrawingRender = false; //флыг, отвечающий за плавное рисование
    bool m_isDrawingRude = false; //флаг, отвечающий за жесткое рисование
    QGraphicsLineItem* currentLineDrawingRude = nullptr; // текущая жесткая линия для рисования
    QPointF previousPoint; //координаты предыдущей точки
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

#endif // CUSTOMGRAPHICSSCENE_H
