#include "mainwindow.h"
#include "filldialog.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QGraphicsEllipseItem>
#include <QVector>
#include "square.h"
#include "triangle.h"
#include "romb.h"
#include <QDebug>
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

    ui->graphicsView->setStyleSheet("QGraphicsView { background-color: white; border: 4px solid green }");

    scene->setSceneRect(180,100,800,500);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    currentThickness = 5;

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
void MainWindow::on_rombButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::RombType);
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
        scene->setColorScene(currentColor);
    }
}
void MainWindow::on_chooseThicknessButton_clicked() {
    ChooseThicknessDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentThickness = dialog.getThickness();
        scene->setThicknessScene(currentThickness);
    }
}
void MainWindow::on_fillButton_clicked() {
    FillDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentFillColor = dialog.getFillColor();
        currentBorderColor = dialog.getBorderColor();
        scene->setFillColorScene(currentFillColor);
        scene->setBorderColorScene(currentBorderColor);
    }
}
void MainWindow::on_noFillButton_clicked() {
        scene->changeFillFlagScene(false);
        scene->changeBorderFlagScene(false);
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
        for (auto path : scene->paths) {
        out << scene->serializePath(path)<<"\n";
        }
        for (auto line : scene->drawRudeLines) {
            out << scene->serializeCurve(line)<<"\n";
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

        if (type == "Square") {
            Square* square = Square::deserialize(parts);
            if (square) {
                itemsToAdd.append(square);
            }
        } else if (type == "Triangle") {
            Triangle* triangle = Triangle::deserialize(line);
            if (triangle) {
                itemsToAdd.append(triangle);
            }
        } else if (type == "Romb") {
                Romb* romb = Romb::deserialize(line);
                if (romb) {
                    itemsToAdd.append(romb);
                }
        } else if (type == "Path" && parts.size() > 3) {
            QString colorStr = parts[1];
            QColor color(colorStr);
            int thickness = parts[2].toInt();
            QVector<QPointF> pathPoints = scene->deserializePath(parts);
            // Создаем список для хранения эллипсов
            QVector<QGraphicsEllipseItem*> ellipses;
            for (auto point : pathPoints) {
                // Создаем эллипс, НЕ добавляем его сразу
                QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(
                    point.x() - thickness/2,
                    point.y() - thickness/2,
                    thickness,
                    thickness
                    );
                // Устанавливаем кисть и перо
                ellipse->setPen(Qt::NoPen);
                ellipse->setBrush(QBrush(color));
                // Не добавляем в сцену тут
                ellipses.append(ellipse);
            }
            for (auto* item : ellipses) {
                itemsToAdd.append(item);
            }
        } else if (type == "Curve" && parts.size() >= 2) {
            QString colorStr = parts[1];
            QColor color(colorStr);
            int thickness = parts[2].toInt();
            QVector<QPointF> pathPoints = scene->deserializeCurve(parts);
            QVector<QGraphicsLineItem*> lines;

            for (int i = 0; i < pathPoints.size() - 1; ++i) {
                QPointF point1 = pathPoints[i];
                QPointF point2 = pathPoints[i + 1];

                QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(point1, point2));
                line->setPen(QPen(color, thickness)); // задаем цвет и толщину линии
                // Можно установить перо и кисть, если нужно
                // line->setPen(QPen(Qt::red, 2));
                // line->setBrush(Qt::NoBrush);

                // Не добавляем в сцену тут, только создаем
                lines.append(line);
            }

            // Теперь добавим эти линии на сцену
            for (auto* lineItem : lines) {
                scene->addItem(lineItem);
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
