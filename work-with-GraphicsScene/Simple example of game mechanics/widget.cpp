#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->resize(600,750);
    this->setFixedSize(600,750);

    ui->setupUi(this);
    scene = new CustomGraphicScene();


    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0,0,520,520);

    subject = new Subject();
    subject->setPos(260,260);
    scene->addItem(subject);
    QColor colors[] = {
        Qt::red,
        Qt::green,
        Qt::darkGreen,
        Qt::blue,
        Qt::darkBlue,
        Qt::yellow,
        Qt::darkYellow,
        Qt::magenta,
        Qt::darkMagenta,
        Qt::cyan,
        Qt::darkCyan,
        QColor(255, 165, 0),
        QColor(150, 190, 1),
        QColor(255, 192, 203),
        QColor(100, 0, 50)
    };
    QList<ColorCircle*> *circlesList = new QList<ColorCircle*>();
    for (int i = 0; i < 15; ++i) {
        auto circle = new ColorCircle(rand() % 460 + 30, rand() % 460 + 30, 10, colors[i]);
        scene->addItem(circle);
        circlesList->append(circle);
    }
    subject->setCircles(circlesList);

    // Соединяем сигнал о положении курсора со слотом для передвижения фигуры
    connect(scene, &CustomGraphicScene::signalGetCoordinate, subject, &Subject::slotWhereToGo);

    infoLabelPtr = ui->infoLabel;
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Widget::updateInfoLabel);
    updateTimer->start(50);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateInfoLabel()
{
    int currentCounter = subject->getCounter();
    ui->infoLabel->setText(QString::number(currentCounter));

    if (currentCounter == 15) {
        QMessageBox::information(this, "Поздравляем!", "Вы собрали все кружочки");
        updateTimer->stop(); //остановка таймера, чтобы сообщение не показывалось повторно
    }
}
