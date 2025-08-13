#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include "square.h"
#include "triangle.h"
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
void MainWindow::on_saveButton_clicked() {
    QList<QGraphicsItem*> items = scene->items();
    QList<Figure*> figures;

    // фильтруем только фигуры (Square, Triangle и др.)
    for (auto item : items) {
        Figure* fig = dynamic_cast<Figure*>(item);
        if (fig) {
            figures.append(fig);
        }
    }

    QFile file("save.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (auto fig : figures) {
            out << fig->serialize() << "\n"; // сохраняем сериализованную строку
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
    }
}


void MainWindow::on_openButton_clicked() {
    QFile file("save.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open save.txt");
        return;
    }

    QTextStream in(&file);
    // Очистим сцену перед загрузкой
    scene->clear();
    QVector<QGraphicsItem*> itemsToAdd; // контейнер для объектов
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) continue; // пропускаем пустые строки

        QStringList parts = line.split(';');

        if (parts.isEmpty()) continue;

        QString type = parts[0];

        if (type == "Square" && parts.size() == 6) {
        // Формат: Square;startX;startY;width;height;colorHex
        bool ok1, ok2, ok3, ok4;
        double startX = parts[1].toDouble(&ok1);
        double startY = parts[2].toDouble(&ok2);
        double width = parts[3].toDouble(&ok3);
        double height = parts[4].toDouble(&ok4);
        QString colorStr = parts[5];

        if (ok1 && ok2 && ok3 && ok4) {
            QPointF startPoint(startX, startY);
            QPointF endPoint(startX + width, startY + height);

            // Создаем фигуру
            Square* square = new Square(startPoint); // инициализация
            // Устанавливаем точки явно, если нужно
            square->setStartPoint(startPoint);
            square->setEndPoint(endPoint);
            square->setColor(QColor(colorStr));
            //scene->addItem(square);
            itemsToAdd.append(square);
        }
        } else if (type == "Triangle") {
            Triangle* triangle = Triangle::deserialize(line);
            if (triangle) {
                //scene->addItem(triangle);
                itemsToAdd.append(triangle);
            }
        }
        // Аналогично для других фигур
    }

    // Теперь добавляем их на сцену в обратном порядке, чтобы сохранить слои
    for (int i = itemsToAdd.size() - 1; i >= 0; --i) {
        scene->addItem(itemsToAdd[i]);
    }

    file.close();
}
