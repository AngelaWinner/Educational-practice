#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_saveButton_clicked();
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QString path;
};

#endif // MAINWINDOW_H
