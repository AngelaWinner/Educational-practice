#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
protected :
    void paintEvent(QPaintEvent* event);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_radioButton_red_clicked();

    void on_radioButton_green_clicked();

    void on_radioButton_blue_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
