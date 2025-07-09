#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chisla.h"
#include "dialog.h"
#include <QMainWindow>
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

private slots:
    void on_pushButton_firstNum_clicked();

    void on_pushButton_secondNum_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_autoMorph1_clicked();

    void on_pushButton_autoMorph2_clicked();

    void on_pushButton_elementary1_clicked();

    void on_pushButton_elementary2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    Chisla firstNum, secondNum;
    //int x, y;
};
#endif // MAINWINDOW_H
