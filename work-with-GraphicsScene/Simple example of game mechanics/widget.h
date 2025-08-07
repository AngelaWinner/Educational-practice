#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

#include "customgraphicscene.h"
#include "subject.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CustomGraphicScene *scene;
    QTimer *updateTimer; // Таймер для обновления информации на infoLabel
    QLabel *infoLabelPtr;
    Subject* subject;
private slots:
    void updateInfoLabel();
};

#endif // WIDGET_H
