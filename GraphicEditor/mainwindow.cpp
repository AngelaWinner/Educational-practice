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
#include "ellipse.h"
#include <QDebug>
#include <QFileDialog>
#include <QToolBar>
#include "infodialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1100,785);
    this->setFixedSize(1100,785);

    scene = new CustomGraphicsScene(this);
    ui->graphicsView->resize(890,580);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер, чтобы графика была глаже
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона, избежание повторного рендеринга статичных элементов фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); //Устанавливаем режим обновления области просмотра

    ui->graphicsView->setStyleSheet("QGraphicsView { background-color: white; border: 4px solid green }");

    scene->setSceneRect(180,60,800,500);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    currentThickness = 5;

    QMenu* FileMenu = new QMenu("Файл"); //save open exit
    QMenu* EditMenu = new QMenu("Редактирование"); //chooseColor chooseThickness
    QMenu* LineMenu = new QMenu("Линия"); //rude render
    QMenu* InfoMenu = new QMenu("Информация"); //instruction

    QAction* SaveAction = new QAction(QIcon(":/rec/images/save.jpg"),"Сохранить");
    QAction* OpenAction = new QAction(QIcon(":/rec/images/open.jpg"),"Открыть");
    QAction* ExitAction = new QAction(QIcon(":/rec/images/exit.jpg"),"Выход");
    QAction* InfoAction = new QAction(QIcon(":/rec/images/info.jpg"),"Информация");
    QAction* chooseColorAction = new QAction(QIcon(":/rec/images/chooseColor.jpg"),"Выбрать цвет");
    QAction* chooseThicknessAction = new QAction(QIcon(":/rec/images/chooseThickness.jpg"),"Выбрать толщину");
    QAction* RudeLineAction = new QAction(QIcon(":/rec/images/rudeLine.jpg"),"Рисовать кривую");
    QAction* RenderLineAction = new QAction(QIcon(":/rec/images/renderLine.jpg"),"Рисовать мышью");

    SaveAction->setShortcut(tr("Ctrl+S"));
    OpenAction->setShortcut(tr("Ctrl+O"));

    connect(SaveAction,SIGNAL(triggered()),this,SLOT(on_saveButton_clicked()));
    connect(OpenAction,SIGNAL(triggered()),this,SLOT(on_openButton_clicked()));
    connect(ExitAction,SIGNAL(triggered()),this,SLOT(on_exitButton_clicked()));
    connect(InfoAction,SIGNAL(triggered()),this,SLOT(infoActionSlot()));
    connect(chooseColorAction,SIGNAL(triggered()),this,SLOT(on_chooseColorButton_clicked()));
    connect(chooseThicknessAction,SIGNAL(triggered()),this,SLOT(on_chooseThicknessButton_clicked()));
    connect(RudeLineAction,SIGNAL(triggered()),this,SLOT(on_paintRudeByMouseButton_clicked()));
    connect(RenderLineAction,SIGNAL(triggered()),this,SLOT(on_paintRenderByMouseButton_clicked()));

    FileMenu->addAction(SaveAction);
    FileMenu->addAction(OpenAction);
    FileMenu->addAction(ExitAction);
    EditMenu->addAction(chooseColorAction);
    EditMenu->addAction(chooseThicknessAction);
    LineMenu->addAction(RudeLineAction);
    LineMenu->addAction(RenderLineAction);
    InfoMenu->addAction(InfoAction);

    this->menuBar()->addMenu(FileMenu);
    this->menuBar()->addMenu(EditMenu);
    this->menuBar()->addMenu(LineMenu);
    this->menuBar()->addMenu(InfoMenu);

    QToolBar* toolBar = this->addToolBar(tr("Панель инструментов"));
    toolBar->addAction(SaveAction);
    toolBar->addAction(OpenAction);
    toolBar->addAction(ExitAction);
    toolBar->addAction(chooseColorAction);
    toolBar->addAction(chooseThicknessAction);
    toolBar->addAction(RudeLineAction);
    toolBar->addAction(RenderLineAction);
    toolBar->addSeparator();
    toolBar->addAction(InfoAction);
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
    ui->statusbar->showMessage("Рисование прямоугольника");
}
void MainWindow::on_ellipseButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::EllipseType);
    ui->statusbar->showMessage("Рисование эллипса");
}
void MainWindow::on_rombButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::RombType);
    ui->statusbar->showMessage("Рисование ромба");
}

void MainWindow::on_triangleButton_clicked()
{
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(false);
    scene->setTypeFigure(CustomGraphicsScene::TriangleType);
    ui->statusbar->showMessage("Рисование треугольника");
}

void MainWindow::on_paintRenderByMouseButton_clicked() {
    scene->setDrawingRudeMode(false);
    scene->setDrawingRenderMode(true);
    ui->statusbar->showMessage("Рисование мышью");
}
void MainWindow::on_paintRudeByMouseButton_clicked() {
    scene->setDrawingRenderMode(false);
    scene->setDrawingRudeMode(true);
    ui->statusbar->showMessage("Рисование кривой");
}

void MainWindow::on_chooseColorButton_clicked() {
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid()) {
        currentColor = color;
        // Передавайте цвет сцене или фигурам
        scene->setColorScene(currentColor);
    }
    ui->statusbar->showMessage("Выбор цвета");
}
void MainWindow::on_chooseThicknessButton_clicked() {
    ChooseThicknessDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentThickness = dialog.getThickness();
        scene->setThicknessScene(currentThickness);
    }
    ui->statusbar->showMessage("Выбор толщины");
}
void MainWindow::on_fillButton_clicked() {
    FillDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentFillColor = dialog.getFillColor();
        currentBorderColor = dialog.getBorderColor();
        scene->setFillColorScene(currentFillColor);
        scene->setBorderColorScene(currentBorderColor);
    }
    ui->statusbar->showMessage("Заливка фигуры");
}
void MainWindow::on_noFillButton_clicked() {
    scene->changeFillFlagScene(false);
    scene->changeBorderFlagScene(false);
    ui->statusbar->showMessage("Отмена заливки");
}

void MainWindow::on_exitButton_clicked()
{
    if (wasSavedFlag) {
        this->close();
    } else {
        // Спрашиваем пользователя
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Выход",
                                      "Есть несохранённые изменения. Хотите сохранить перед выходом?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            // Вызов функции сохранения
            on_saveButton_clicked();
            this->close();
        } else if (reply == QMessageBox::No) {
            // Просто закрываемся без сохранения
            this->close();
        }
    }
}
void MainWindow::infoActionSlot()
{
    InfoDialog *dialog = new InfoDialog(this);
    dialog->exec(); // Открывает модальное окно
    ui->statusbar->showMessage("Получение информации о проекте");
}

void MainWindow::on_saveButton_clicked() {

    QMessageBox messageBox;
    messageBox.setText("Выберите формат сохранения:");
    QPushButton *textButton = messageBox.addButton(tr("Текстовый"), QMessageBox::YesRole);
    QPushButton *binaryButton = messageBox.addButton(tr("Бинарный"), QMessageBox::NoRole);
    messageBox.exec();

    QString filter, format;
    if (messageBox.clickedButton() == textButton) {
        filter = "Text Files (*.txt);;All Files (*)";
        format = "text";
    } else if (messageBox.clickedButton() == binaryButton) {
        filter = "Binary Files (*.bin);;All Files (*)";
        format = "binary";
    }

    QString defaultFileName = "untitled"; // Можно указать по умолчанию
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", defaultFileName, filter);

    if (fileName.isEmpty()) return; // Пользователь отменил

    // Проверяем, есть ли расширение
    if (format == "text" && !fileName.endsWith(".txt", Qt::CaseInsensitive)) fileName += ".txt";

    if (format == "binary" && !fileName.endsWith(".bin", Qt::CaseInsensitive)) fileName += ".bin";

    if (format == "text") {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int layer = 0; layer <= scene->getZCounter(); ++layer) {
                for (auto figure : scene->allFigureObjects) {
                    if (figure && figure->getZLayer() == layer) {
                        out << figure->serializeText() << "\n";
                        //out<<layer<< "\n";
                    }
                }
                // Аналогично для линий/кривых
                for (auto path : scene->paths) {
                    // если PathElement содержит слой, сравниваем его
                    if (path.layerZ == layer) {
                        out << scene->serializePath(path) << "\n";
                        //out<<layer<< "\n";
                    }
                }
                for (auto line : scene->drawRudeLines) {
                    if (line.layerZ == layer) {
                        out << scene->serializeCurve(line) << "\n";
                        //out<<layer<< "\n";
                    }
                }
            }
            file.close();
            wasSavedFlag = true;
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        }
    } else {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);

            for (int layer = 0; layer <= scene->getZCounter(); ++layer) {
                for (auto figure : scene->allFigureObjects) {
                    if (figure && figure->getZLayer() == layer) {
                        figure->serializeBin(out);
                    }
                }
                for (auto path : scene->paths) {
                    if (path.layerZ == layer) {
                        scene->serializePathBin(path, out);
                    }
                }
                for (auto line : scene->drawRudeLines) {
                    if (line.layerZ == layer) {
                        scene->serializeCurveBin(line, out);
                    }
                }
            }
            file.close();
            wasSavedFlag = true;
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        }
    }
    ui->statusbar->showMessage("Сохранение");
}

void MainWindow::on_openButton_clicked() {
    QString filter = "Все файлы (*)";
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл для открытия", "", filter);

    if (fileName.isEmpty()) {
        return; // Пользователь отменил
    }

    // Определяем формат по расширению файла
    bool isBinary = false;
    if (fileName.endsWith(".bin", Qt::CaseInsensitive))
        isBinary = true;
    else if (fileName.endsWith(".txt", Qt::CaseInsensitive))
        isBinary = false;
    else {
        QMessageBox::warning(this, "Ошибка", "Не подходящий формат файла");
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть выбранный файл");
        return;
    }
    // Очистим сцену перед загрузкой
    scene->clear();
    scene->allFigureObjects.clear();
    scene->paths.clear();
    scene->drawRudeLines.clear();
    scene->setZCounter(0); //обнулила счетчик
    QVector<QGraphicsItem*> itemsToAdd; // контейнер для объектов
    if (!isBinary){
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue; // пропускаем пустые строки
            QStringList parts = line.split(';');
            if (parts.isEmpty()) continue;
            QString type = parts[0];

            if (type == "Square") {
                Square* square = Square::deserialize(parts);
                square->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (square) {
                    itemsToAdd.append(square);
                    scene->allFigureObjects.append(square);
                }
            } else if (type == "Triangle") {
                Triangle* triangle = Triangle::deserialize(parts);
                triangle->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (triangle) {
                    itemsToAdd.append(triangle);
                    scene->allFigureObjects.append(triangle);
                }
            } else if (type == "Romb") {
                Romb* romb = Romb::deserialize(parts);
                romb->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (romb) {
                    itemsToAdd.append(romb);
                    scene->allFigureObjects.append(romb);
                }
            } else if (type == "Ellipse") {
                Ellipse* ellipse = Ellipse::deserialize(parts);
                ellipse->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (ellipse) {
                    itemsToAdd.append(ellipse);
                    scene->allFigureObjects.append(ellipse);
                }
            } else if (type == "Path" && parts.size() > 3) {
                QString colorStr = parts[1];
                QColor color(colorStr);
                int thickness = parts[2].toInt();
                QVector<QPointF> pathPoints = scene->deserializePath(parts);
                scene->paths.append(PathElement(pathPoints, color, thickness, scene->getZCounter()+1));
                scene->setZCounter(scene->getZCounter()+1);
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
                scene->drawRudeLines.append(PathElement(pathPoints, color, thickness, scene->getZCounter()+1));
                scene->setZCounter(scene->getZCounter()+1);

                for (int i = 0; i < pathPoints.size() - 1; ++i) {
                    QPointF point1 = pathPoints[i];
                    QPointF point2 = pathPoints[i + 1];

                    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(point1, point2));
                    line->setPen(QPen(color, thickness)); // задаем цвет и толщину линии
                    lines.append(line);
                }

                // Теперь добавим эти линии на сцену
                for (auto* lineItem : lines) {
                    itemsToAdd.append(lineItem);
                }
            }
            // Аналогично для других фигур
        }

        // Теперь добавляем их на сцену в обратном порядке, чтобы сохранить слои
        for (int i =0; i< itemsToAdd.size(); ++i) {
            scene->addItem(itemsToAdd[i]);
        }

    }  else if (isBinary) {
        //бинарный файл
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString type;
            in >> type;
            if (type.isEmpty()) continue; // пропускаем пустые строки
            if (type == "Square") {
                Square* square = Square :: deserializeBin(in);
                square->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (square) {
                    itemsToAdd.append(square);
                    scene->allFigureObjects.append(square);
                }
            } else if (type == "Ellipse") {
                Ellipse* ellipse = Ellipse :: deserializeBin(in);
                ellipse->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (ellipse) {
                    itemsToAdd.append(ellipse);
                    scene->allFigureObjects.append(ellipse);
                }
            } else if (type == "Romb") {
                Romb* romb = Romb :: deserializeBin(in);
                romb->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (romb) {
                    itemsToAdd.append(romb);
                    scene->allFigureObjects.append(romb);
                }
            }
            else if (type == "Triangle") {
                Triangle* triangle = Triangle :: deserializeBin(in);
                triangle->setZLayer(scene->getZCounter());
                scene->setZCounter(scene->getZCounter()+1);
                if (triangle) {
                    itemsToAdd.append(triangle);
                    scene->allFigureObjects.append(triangle);
                }
            } else if (type == "Path") {
                QColor color;
                int thickness;
                QVector<QPointF> pathPoints = scene->deserializePathBin(in, color, thickness);
                scene->paths.append(PathElement(pathPoints, color, thickness, scene->getZCounter()+1));
                scene->setZCounter(scene->getZCounter()+1);
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
            } else if (type == "Curve") {
                QColor color;
                int thickness;
                QVector<QPointF> pathPoints = scene->deserializeCurveBin(in, color, thickness);
                QVector<QGraphicsLineItem*> lines;
                scene->drawRudeLines.append(PathElement(pathPoints, color, thickness, scene->getZCounter()+1));
                scene->setZCounter(scene->getZCounter()+1);
                for (int i = 0; i < pathPoints.size() - 1; ++i) {
                    QPointF point1 = pathPoints[i];
                    QPointF point2 = pathPoints[i + 1];

                    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(point1, point2));
                    line->setPen(QPen(color, thickness)); // задаем цвет и толщину линии
                    lines.append(line);
                }
                for (auto* lineItem : lines) {
                    itemsToAdd.append(lineItem);
                }
            }
            // Аналогично для других фигур
        }

        // Теперь добавляем их на сцену в обратном порядке, чтобы сохранить слои
        for (int i =0; i< itemsToAdd.size(); ++i) {
            scene->addItem(itemsToAdd[i]);
        }
    }
    file.close();
    ui->statusbar->showMessage("Открытие файла");

}
