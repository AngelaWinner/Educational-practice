#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Paint;
}
QT_END_NAMESPACE

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();

private:
    Ui::Paint *ui;
    QTimer* timer; //для подготовки актуальных размеров сцены
    paintscene* scene; //объяввляем кастомную графическую сцену
    //переопределяем событие изменения размера
    //окна для пересчета размеров графической сцены
    void resizeEvent(QResizeEvent* event);

private slots:
    void slotTimer();
};
#endif // PAINT_H
