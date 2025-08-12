#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1100,755);
    this->setFixedSize(1100,755);

    scene = new CustomGraphicsScene(this);
    ui->graphicsView->resize(890,580);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер, чтобы графика была глаже
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона, избежание повторного рендеринга статичных элементов фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); //Устанавливаем режим обновления области просмотра

    ui->graphicsView->setStyleSheet("QGraphicsView { border: 4px solid green }");

    scene->setSceneRect(180,100,800,500);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer(){
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}
void MainWindow::resizeEvent(QResizeEvent* event){
    timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_squareButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::SquareType);
}


void MainWindow::on_triangleButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::TriangleType);
}

void MainWindow::on_paintRenderByMouseButton_clicked() {
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(true);
}
void MainWindow::on_paintRudeByMouseButton_clicked() {
    scene->setDrawingRenderMode(false);
    scene->setDrawingRudeMode(true);
}

void MainWindow::on_chooseColorButton_clicked() {
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid()) {
        currentColor = color;
        // Передавайте цвет сцене или фигурам
        scene->setDrawingColor(currentColor);
    }
}
