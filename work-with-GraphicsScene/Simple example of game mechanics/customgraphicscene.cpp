#include "customgraphicscene.h"
#include <QApplication>
#include <QBrush>
#include <QColor>

CustomGraphicScene::CustomGraphicScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

CustomGraphicScene::~CustomGraphicScene()
{

}
void CustomGraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    if(QApplication::mouseButtons() == Qt::LeftButton){
        emit signalGetCoordinate(event->scenePos());
    }
}

void CustomGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::LeftButton){
        emit signalGetCoordinate(event->scenePos());
    }
}
