#include "paintscene.h"

paintscene::paintscene(QObject* parent) : QGraphicsScene(parent) {

}
paintscene::~paintscene(){

}
void paintscene::mousePressEvent(QGraphicsSceneMouseEvent* event){
    addEllipse(event->scenePos().x()-5,
               event->scenePos().y()-5,
               10,10,
               QPen(Qt::NoPen), QBrush(Qt::red));
    previousPoint=event->scenePos();
    //сохранили данные о прошлой координате
}
void paintscene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
    previousPoint=event->scenePos();
    //сохранили данные о прошлой координате
}
