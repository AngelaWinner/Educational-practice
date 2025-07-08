#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "PaintScene.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintScene* scene;
    QTimer* timer;
    void resizeEvent(QResizeEvent* event);
private slots:
    void slotTimer();

    void on_pushButton_romb_clicked(); //метод отрисовки ромба
    void on_pushButton_kvad_clicked();
    void on_pushButton_tria_clicked();
};
#endif // MAINWINDOW_H
