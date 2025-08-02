#include "widget.h"
#include "ui_widget.h"
#include <QRandomGenerator>

static int randomBetween(int low, int high)
{
    return QRandomGenerator::global()->bounded(low, high + 1); // Возвращает случайное число в диапазоне [low, high], используя глобальный генератор
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(930,850);
    this->setFixedSize(930,850);

    scene = new QGraphicsScene(this);
    ui->graphicsView->resize(900,650);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер, чтобы графика была глаже
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона, избежание повторного рендеринга статичных элементов фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); //Устанавливаем режим обновления области просмотра

    scene->setSceneRect(0,0,500,500);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    MoveItem *item = new MoveItem("romb");
    item->setPos(randomBetween(30, 470),
                 randomBetween(40, 460));
    scene->addItem(item);
}
void Widget::on_pushButton_2_clicked()
{
    MoveItem *item = new MoveItem("figure");
    item->setPos(randomBetween(40, 460),
                 randomBetween(40, 460));
    scene->addItem(item);
}
void Widget::on_pushButton_3_clicked()
{
    MoveItem *item = new MoveItem("star");
    item->setPos(randomBetween(40, 460),
                 randomBetween(40, 460));
    scene->addItem(item);
}
