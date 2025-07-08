#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); //устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //отсключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //отсключаем скроллбар по горизонтали
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
void MainWindow::on_pushButton_romb_clicked()
{
    scene->setTypeFigure(PaintScene::RombType);
}


void MainWindow::on_pushButton_kvad_clicked()
{
    scene->setTypeFigure(PaintScene::SquareType);
}


void MainWindow::on_pushButton_tria_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}

