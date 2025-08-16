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
        SquareType, TriangleType, RombType, EllipseType
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
    QVector<PathElement> drawRudeLines;
    QString serializeCurve (const PathElement& curve);
    QVector<QPointF> deserializeCurve(QStringList parts);

    //тут должен быть массив, в котором будут храниться все фигуры (square, triangle, romb, ellipse), как это сделать?
    //Ведь вся реализация в сцене это создание tempFigure и указание свойств, таких ка цвета, толщина и слой???
    QVector<Figure*> allFigureObjects; // или QList<QGraphicsItem*>

    void setThicknessScene(int thickness);

    void setFillColorScene(QColor fillColor);
    void setBorderColorScene(QColor borderColor);
    void changeFillFlagScene(bool TF);
    void changeBorderFlagScene(bool TF);

    int getZCounter() const;
    void setZCounter(int counter);
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
    QColor fillColorScene;
    QColor borderColorScene;

    bool fillColorFlagScene = false;
    bool borderColorFlagScene = true;

    int zCounter = 0;
};

#endif // CUSTOMGRAPHICSSCENE_H
