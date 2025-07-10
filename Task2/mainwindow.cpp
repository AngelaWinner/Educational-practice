#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Lab2.cpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cleanOutputFile();
    readFromFile(inputFilename, list);
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
    ui->textBrowser_2->setPlainText(list.join(" "));
    ui->statusbar->showMessage("Рассмотрение обработанного входного файла");

    QWidget* widget = new QWidget;
    QString header = "Просмотр чистого inputFile";
    widget->setWindowTitle(header);
    widget->setMinimumHeight(200);
    widget->setMinimumWidth(200);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QTextBrowser* textBrowser = new QTextBrowser(widget);
    textBrowser->setPlainText(list.join(" "));
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(textBrowser);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"(\s*([+-]?\d+)\s*)");
    QRegularExpressionMatch match = rgx.match(input);
    if (match.hasMatch()) {
        int n = match.captured(1).toInt();
        if(n<=0) {
            QString str = "Число меньше или равно нулю";
            ui->textBrowser_2->setPlainText(str);
        } else {
            QStringList lengList = findWord(list, n);
            if(lengList.isEmpty()) {
                QString str = "Не найдено";
                ui->textBrowser_2->setPlainText(str);
            } else {
                ui->textBrowser_2->setPlainText(lengList.join(" "));
            }
        }
    } else {
        QString str = "Вы ввели неверную строку :(";
        ui->textBrowser_2->setPlainText(str);
    }
    ui->statusbar->showMessage("Поиск слова по заданной длине");
}


void MainWindow::on_pushButton_3_clicked()
{
    std::sort(list.begin(), list.end(), [](const QString &a, const QString &b) {
        return QString::compare(a, b, Qt::CaseInsensitive) < 0;
    });
    //ui->textBrowser_2->setPlainText(list.join(" "));
    ui->statusbar->showMessage("Сортировка обработанного входного файла");
}


void MainWindow::on_pushButton_4_clicked()
{
    writeToFile(outputFilename, list);
    ui->statusbar->showMessage("Запись в выходной файл");
}


void MainWindow::on_action_inputFile_triggered()
{
    ui->textBrowser_2->setPlainText(list.join(" "));
    ui->statusbar->showMessage("Рассмотрение обработанного входного файла");
}


void MainWindow::on_action_inputFile_2_triggered()
{
    std::sort(list.begin(), list.end(), [](const QString &a, const QString &b) {
        return QString::compare(a, b, Qt::CaseInsensitive) < 0;
    });
    //ui->textBrowser_2->setPlainText(list.join(" "));
    ui->statusbar->showMessage("Сортировка обработанного входного файла");
}


void MainWindow::on_action_triggered()
{
    writeToFile(outputFilename, list);
    ui->statusbar->showMessage("Запись в выходной файл");
}


void MainWindow::on_pushButton_5_clicked()
{
    QString input = ui->lineEdit_2->text();
    if(isPassWord(input)) {
        ui->label_2->setText("Пароль правильный!");
    } else {
        ui->label_2->setText("Пароль неверный");
    }
    ui->statusbar->showMessage("Проверка пароля");
}

