#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chisla.cpp"
#include <QRegularExpression>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog = new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_firstNum_clicked()
{
    QStringList list = firstNum.getList();
    dialog->setText(list);
    dialog->show();
    ui->statusbar->showMessage("first number");
}


void MainWindow::on_pushButton_secondNum_clicked()
{
    QStringList list = secondNum.getList();
    dialog->setText(list);
    dialog->show();
    ui->statusbar->showMessage("second number");
}


void MainWindow::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"(\s*([+-]?\d+)\s+([+-]?\d+)\s*)");
    QRegularExpressionMatch match = rgx.match(input);
    if (match.hasMatch()) {
        int x = match.captured(1).toInt();
        int y = match.captured(2).toInt();
        firstNum.SetA(x);
        firstNum.SetB(y);
        QStringList list = firstNum.getList();
        dialog->setText(list);
    } else {
        firstNum.SetA(0);
        firstNum.SetB(0);
        QString str = "you entered wrong string";
        dialog->setPlainText(str);
    }
    dialog->show();
    ui->statusbar->showMessage("changing koordinates");
}


void MainWindow::on_pushButton_2_clicked()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"(\s*([+-]?\d+)\s+([+-]?\d+)\s*)");
    QRegularExpressionMatch match = rgx.match(input);
    if (match.hasMatch()) {
        int x = match.captured(1).toInt();
        int y = match.captured(2).toInt();
        secondNum.SetA(x);
        secondNum.SetB(y);
        QStringList list = secondNum.getList();
        dialog->setText(list);
    } else {
        secondNum.SetA(0);
        secondNum.SetB(0);
        QString str = "you entered wrong string";
        dialog->setPlainText(str);
    }
    dialog->show();
    ui->statusbar->showMessage("changing koordinates");
}


void MainWindow::on_pushButton_3_clicked()
{
    int factorial = firstNum.Fact();
    QString str = QString :: number(factorial);
    ui->label_result->setText(str);
    ui->statusbar->showMessage("factorial...");
}


void MainWindow::on_pushButton_4_clicked()
{
    int factorial = secondNum.Fact();
    QString str = QString :: number(factorial);
    ui->label_result->setText(str);
    ui->statusbar->showMessage("factorial...");
}


void MainWindow::on_pushButton_autoMorph1_clicked()
{
    QStringList list = firstNum.taskB7();

    if (firstNum.GetA() <= 0) {
        QString str;
        if (firstNum.GetA() == 0)
            str = "Can't find automorphic numbers because their count is 0.";
        else if (firstNum.GetA() < 0)
            str = "Can't find automorphic numbers because their count is less than 0.";
        dialog->setPlainText(str);
    } else {
        if (!list.isEmpty()) {
            dialog->setPlainText(list.join(", "));
        } else {
            dialog->setPlainText("No automorphic numbers found for the given count.");
        }
    }
    dialog->show();
    ui->statusbar->showMessage("automorphic numbers");
}


void MainWindow::on_pushButton_autoMorph2_clicked()
{
    QStringList list = secondNum.taskB7();

    if (secondNum.GetA() <= 0) {
        QString str;
        if (secondNum.GetA() == 0)
            str = "Can't find automorphic numbers because their count is 0.";
        else if (secondNum.GetA() < 0)
            str = "Can't find automorphic numbers because their count is less than 0.";
        dialog->setPlainText(str);
    } else {
        if (!list.isEmpty()) {
            dialog->setPlainText(list.join(", "));
        } else {
            dialog->setPlainText("No automorphic numbers found for the given count.");
        }
    }
    dialog->show();
    ui->statusbar->showMessage("automorphic numbers");
}


void MainWindow::on_pushButton_elementary1_clicked()
{
    if (firstNum.GetA() <= 0) {
        dialog->setPlainText("Некорректное значение: число должно быть больше 0.");
    } else {
        QStringList list = firstNum.taskB8();
        if (!list.isEmpty()) {
            dialog->setPlainText(list.join(", "));
        } else {
            dialog->setPlainText("Нет подходящих чисел для заданного условия.");
        }
    }
    dialog->show();
    ui->statusbar->showMessage("автоматические числа");
}


void MainWindow::on_pushButton_elementary2_clicked()
{
    if (secondNum.GetA() <= 0) {
        dialog->setPlainText("Некорректное значение: число должно быть больше 0.");
    } else {
        QStringList list = secondNum.taskB8();
        if (!list.isEmpty()) {
            dialog->setPlainText(list.join(", "));
        } else {
            dialog->setPlainText("Нет подходящих чисел для заданного условия.");
        }
    }
    dialog->show();
    ui->statusbar->showMessage("автоматические числа");
}


void MainWindow::on_pushButton_5_clicked()
{
    QStringList results = firstNum.taskC7();
    dialog->setPlainText(results.join("\n"));
    dialog->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    QStringList results = secondNum.taskC7();
    dialog->setPlainText(results.join("\n"));
    dialog->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    QStringList results = firstNum.taskC8();
    dialog->setPlainText(results.join("\n"));
    dialog->show();
}


void MainWindow::on_pushButton_8_clicked()
{
    QStringList results = secondNum.taskC8();
    dialog->setPlainText(results.join("\n"));
    dialog->show();
}

