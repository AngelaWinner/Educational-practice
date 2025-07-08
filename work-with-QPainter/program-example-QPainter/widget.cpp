#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    if(ui->radioButton_red->isChecked()){
        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawEllipse(100, 50, 150, 150);
    } else     if(ui->radioButton_green->isChecked()){
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter.drawEllipse(100, 50, 150, 150);
    } else     if(ui->radioButton_blue->isChecked()){
        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter.drawEllipse(100, 50, 150, 150);
    } else {
        painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        painter.drawEllipse(100, 50, 150, 150);
    }
}
void Widget::on_radioButton_red_clicked()
{
    repaint();
}


void Widget::on_radioButton_green_clicked()
{
    repaint();
}


void Widget::on_radioButton_blue_clicked()
{
    repaint();
}

