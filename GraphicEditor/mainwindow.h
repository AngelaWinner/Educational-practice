#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "customgraphicsscene.h"
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
    CustomGraphicsScene *scene;
    QTimer* timer;
    void resizeEvent(QResizeEvent* event);
    QColor currentColor = Qt::red;
private slots:
    void slotTimer();

    void on_squareButton_clicked();
    void on_triangleButton_clicked();
    void on_paintRudeByMouseButton_clicked();
    void on_paintRenderByMouseButton_clicked();
    void on_chooseColorButton_clicked();
    void on_saveButton_clicked();
    void on_openButton_clicked();
};
#endif // MAINWINDOW_H
