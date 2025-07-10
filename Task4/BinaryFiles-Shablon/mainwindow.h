#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shablon.h"
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
    void printTextPersons();
    void printOperations();
    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
    void cleanOutputFile();
    QString inputFilename1 = "Input1.txt";
    QString inputFilename2 = "Input2.txt";
    QString inputFilename1Bin = "Input1.bin";
    QString inputFilename2Bin = "Input2.bin";
    QString inputFilenameShab1 = "Ob1.bin";
    QString inputFilenameShab2 = "Nob1.bin";
    QString outputFilename = "Output.txt";
    QFile outFile;
    QTextStream out;
    Students studs1, studs2, studs1Bin, studs2Bin;
    STUD<Stud1> takenBooks;
    STUD<Stud2> returnedBooks;
};
#endif // MAINWINDOW_H
