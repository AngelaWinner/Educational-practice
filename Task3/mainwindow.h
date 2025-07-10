#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Polymor.h"
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
    void on_pushButton_clicked();
    void printPersonAllInfo();
    void changePassportNumber();
    void changeAge();

private:
    Ui::MainWindow *ui;
    OldPerson person1;
    OldPerson person2;
    OldPerson person3;
    OldPerson person4;
};
#endif // MAINWINDOW_H
