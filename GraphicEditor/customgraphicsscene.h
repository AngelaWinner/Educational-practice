#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include "pathelement.h"

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
        SquareType, TriangleType, RombType
    };

    void setDrawingRenderMode(bool enabled); // включение/выключение режима плавного рисования
    bool isDrawingRenderMode() const;
    void setDrawingRudeMode(bool enabled); // включение/выключение режима жесткого рисования
    bool isDrawingRudeMode() const;

    void setColorScene(const QColor& color);
    QColor сolorScene = Qt::red;

    QVector<QPointF> currentPath;
    QVector<PathElement> paths; // все сохранённые пути
    QString serializePath(const PathElement& path); //PathElement = QPair<QVector<QPointF>, QColor, int>
    QVector<QPointF> deserializePath(QStringList parts);

    QVector<QPointF> rudeLinePointVector;
    //QVector<QVector<QPointF>> drawRudeLines;
    QVector<PathElement> drawRudeLines;
    //QString serializeCurve (const QVector<QPointF>& curve);
    QString serializeCurve (const PathElement& curve);
    QVector<QPointF> deserializeCurve(QStringList parts);

    void setThicknessScene(int thickness);
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
    int thicknessScene;
};

#endif // CUSTOMGRAPHICSSCENE_H
