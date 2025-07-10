#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workWithFiles.cpp"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cleanOutputFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanOutputFile(){
    QFile outputFile(outputFilename);
    if (!outputFile.open(QIODevice::WriteOnly  | QIODevice::Text)) {
        qDebug() << "Can't open for writing" << outputFilename;
        return;
    }
    outputFile.close();
}

void MainWindow::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"([^0-9\s])");
    QRegularExpressionMatch match = rgx.match(input);
    if (!match.hasMatch() && input!="") {
        myList.clear();
        QList<QString> list = input.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for(auto el : list){
            myList.push_back(el.toInt());
        }
    } else {
        myList.clear();
        myList.readFromFile(inputFilename);
    }
    QWidget* widget = new QWidget;
    widget->setWindowTitle("Новый список");
    widget->setMinimumHeight(100);
    widget->setMinimumWidth(100);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QTextBrowser* textBrowser = new QTextBrowser(widget);
    myList.change();
    textBrowser->setPlainText(myList.join(" "));
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(textBrowser);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
    ui->statusbar->showMessage("Поиск наибольшего четного");
}

void MainWindow::on_pushButton_2_clicked()
{
    if (myList.empty()) {
        myList.readFromFile(inputFilename);
    }
    QWidget* widget = new QWidget;
    widget->setWindowTitle("Просмотр списка");
    widget->setMinimumHeight(100);
    widget->setMinimumWidth(100);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QTextBrowser* textBrowser = new QTextBrowser(widget);
    QString list = myList.print();
    textBrowser->setPlainText(list);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(textBrowser);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
    ui->statusbar->showMessage("Просмотр списка");
}


void MainWindow::on_pushButton_3_clicked()
{
    if (myList.empty()) {
        myList.readFromFile(inputFilename);
    }
    QFile outFile(outputFilename);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }
    QTextStream out(&outFile);
    QString list = myList.print();
    out<<list;
    outFile.close();
    ui->statusbar->showMessage("Запись в файл");
}


void MainWindow::on_pushButton_4_clicked()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"([^0-9\s])");
    QRegularExpressionMatch match = rgx.match(input);
    if (!match.hasMatch() && input!="") {
        myList.clear();
        QList<QString> list = input.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for(auto el : list){
            myList.push_back(el.toInt());
        }
    } else {
        QMessageBox::warning(this, "Некорректный формат", "Строка должна содержать числа, разделенные одним пробелом");
        if (myList.empty()) {
            myList.readFromFile(inputFilename);
        }
    }
    ui->statusbar->showMessage("Заполнение списка");
}


void MainWindow::on_action_triggered()
{
    if (myList.empty()) {
        myList.readFromFile(inputFilename);
    }
    QWidget* widget = new QWidget;
    widget->setWindowTitle("Просмотр списка");
    widget->setMinimumHeight(100);
    widget->setMinimumWidth(100);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QTextBrowser* textBrowser = new QTextBrowser(widget);
    QString list = myList.print();
    textBrowser->setPlainText(list);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(textBrowser);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
    ui->statusbar->showMessage("Просмотр списка");
}


void MainWindow::on_action_2_triggered()
{
    if (myList.empty()) {
        myList.readFromFile(inputFilename);
    }
    QFile outFile(outputFilename);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }
    QTextStream out(&outFile);
    QString list = myList.print();
    out<<list;
    outFile.close();
    ui->statusbar->showMessage("Запись в файл");
}


void MainWindow::on_action_3_triggered()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"([^0-9\s])");
    QRegularExpressionMatch match = rgx.match(input);
    if (!match.hasMatch() && input!="") {
        myList.clear();
        QList<QString> list = input.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for(auto el : list){
            myList.push_back(el.toInt());
        }
    } else {
        QMessageBox::warning(this, "Некорректный формат", "Строка должна содержать числа, разделенные одним пробелом");
        if (myList.empty()) {
            myList.readFromFile(inputFilename);
        }
    }
    ui->statusbar->showMessage("Заполнение списка");
}

