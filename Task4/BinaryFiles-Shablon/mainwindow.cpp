#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shablon.cpp"
#include <QStandardItemModel>
#include <QTableView>
using namespace Qt;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , outFile("output.txt")
    , out(&outFile)
{
    ui->setupUi(this);
    cleanOutputFile();
    studs1.readFromFile(inputFilename1);
    studs2.readFromFile(inputFilename2);
    studs1Bin.readFromFileBin(inputFilename1Bin);
    studs2Bin.readFromFileBin(inputFilename1Bin);
    takenBooks.ReadFromBinFile(inputFilenameShab1);
    returnedBooks.ReadFromBinFile(inputFilenameShab2);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::printTextPersons);
    connect(ui->action, &QAction::triggered, this, &MainWindow::printTextPersons);
    connect(ui->action_2, &QAction::triggered, this, &MainWindow::printTextPersons);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::printTextPersons);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::printTextPersons);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::printTextPersons);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->action_3, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_4, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::printOperations);
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_6, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_1_2, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_2_1, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_1, &QAction::triggered, this, &MainWindow::printOperations);
    connect(ui->action_7, &QAction::triggered, this, &MainWindow::printOperations);

    connect(ui->action_8, &QAction::triggered, this, &MainWindow::on_pushButton_13_clicked);
    connect(ui->action_9, &QAction::triggered, this, &MainWindow::on_pushButton_14_clicked);
    connect(ui->action_10, &QAction::triggered, this, &MainWindow::on_pushButton_15_clicked);
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
void MainWindow :: printTextPersons(){
    QPushButton *button = (QPushButton*)(sender());
    QAction *act = (QAction*)(sender());
    Students*stud;
    if(button->text()=="1 т" || act->text()=="Посмотреть первый файл") {
        stud = &studs1;
        out<<"Студенты из 1го текстового файла : "<<endl;
        studs1.printAll(out);
    } else     if(button->text()=="2 т" || act->text()=="Посмотреть второй файл") {
        stud = &studs2;
        out<<"Студенты из 2го текстового файла : "<<endl;
        studs2.printAll(out);
    } else     if(button->text()=="1 б") {
        stud = &studs1Bin;
        out<<"Студенты из 1го бинарного файла : "<<endl;
        studs1Bin.printAll(out);
    } else     if(button->text()=="2 б") {
        stud = &studs2Bin;
        out<<"Студенты из 2го бинарного файла : "<<endl;
        studs2Bin.printAll(out);
    }
    QString header = "Получение записей из файлов";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(350);
    widget->setMinimumWidth(500);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(stud->count(), 4);
    for(int i=0; i< stud->count(); ++i){
        /*qDebug() << "Student" << i << ":"
                 << stud->GetStudents()[i].GetName()
                 << stud->GetStudents()[i].GetNum()
                 << stud->GetStudents()[i].GetGroup()
                 << stud->GetStudents()[i].GetGrade();*/
        model->setItem(i, 0, new QStandardItem(stud->GetStudents()[i].GetName()));
        model->setItem(i, 1, new QStandardItem(stud->GetStudents()[i].GetNum()));
        model->setItem(i, 2, new QStandardItem(stud->GetStudents()[i].GetGroup()));
        model->setItem(i, 3, new QStandardItem(stud->GetStudents()[i].GetGrade()));
    }
    model->setHeaderData(0, Qt::Horizontal, "Имя");
    model->setHeaderData(1, Qt::Horizontal, "Номер");
    model->setHeaderData(2, Qt::Horizontal, "Группа");
    model->setHeaderData(3, Qt::Horizontal, "Оценка");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(250);
    view->setMinimumWidth(250);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}

void MainWindow :: printOperations(){
    QPushButton *button = (QPushButton*)(sender());
    Students stud;
    QAction *act = (QAction*)(sender());
    if(button->text()=="Объединение" || act->text()=="Объединение") {
        out << "Объединение студентов из текстового файла : " << endl;
        stud = studs1.studUnion(studs2, out);
        ui->statusbar->showMessage("Выполнение операции объединение");
    } else     if(button->text()=="Пересечение" || act->text()=="Пересечение") {
        out << "Пересечение студентов из текстового файла : " << endl;
        stud = studs1.studPeresechenie(studs2, out);
        ui->statusbar->showMessage("Выполнение операции пересечение");
    } else     if(button->text()=="Разность 1 и 2файлов" || act->text()=="Разность 1 и 2") {
        out << "Разность студентов 1 и 2 текстовых файлов : " << endl;
        stud = studs1.studDiffer(studs2, out);
        ui->statusbar->showMessage("Выполнение операции разности");
    } else     if(button->text()=="Разность 2 и 1файлов" || act->text()=="Разность 2 и 1") {
        out << "Разность студентов 2 и 1 текстовых файлов : " << endl;
        stud = studs2.studDiffer(studs1, out);
        ui->statusbar->showMessage("Выполнение операции разности");
    } else     if(button->text()=="Сортировать 1 файл по номерам зачеток" || act->text()=="Сортировать файл 1 по номерам зачеток") {
        out << "Отсортированный 1 файл по номерам зачеток : " << endl;
        studs1.numSort();
        stud = studs1;
        stud.printAll(out);
        ui->statusbar->showMessage("Сортировка по номерам зачеток");
    } else     if(button->text()=="Сортировать 2 файл  по номерам зачеток" || act->text()=="Сортировать файл 2 по номерам зачеток") {
        out << "Отсортированный 2 файл по номерам зачеток : " << endl;
        studs2.numSort();
        stud = studs2;
        stud.printAll(out);
        ui->statusbar->showMessage("Сортировка по номерам зачеток");
    } else     if(button->text()=="Сортировать 1 файл по номерам групп" || act->text()=="Сортировать файл 1 по номерам групп") {
        out << "Отсортированный 1 файл по номерам групп : " << endl;
        studs1.groupSort();
        stud = studs1;
        stud.printAll(out);
        ui->statusbar->showMessage("Сортировка по номерам групп");
    } else     if(button->text()=="Сортировать 2 файл  по номерам групп" || act->text()=="Сортировать файл 2 по номерам групп") {
        out << "Отсортированный 2 файл по номерам групп : " << endl;
        studs2.groupSort();
        stud = studs2;
        stud.printAll(out);
        ui->statusbar->showMessage("Сортировка по номерам групп");
    }
    QString header = "Получение записей из файлов";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(350);
    widget->setMinimumWidth(500);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(stud.count(), 4);
    for(int i=0; i< stud.count(); ++i){
        /*qDebug() << "Student" << i << ":"
                 << stud->GetStudents()[i].GetName()
                 << stud->GetStudents()[i].GetNum()
                 << stud->GetStudents()[i].GetGroup()
                 << stud->GetStudents()[i].GetGrade();*/
        model->setItem(i, 0, new QStandardItem(stud.GetStudents()[i].GetName()));
        model->setItem(i, 1, new QStandardItem(stud.GetStudents()[i].GetNum()));
        model->setItem(i, 2, new QStandardItem(stud.GetStudents()[i].GetGroup()));
        model->setItem(i, 3, new QStandardItem(stud.GetStudents()[i].GetGrade()));
    }
    model->setHeaderData(0, Qt::Horizontal, "Имя");
    model->setHeaderData(1, Qt::Horizontal, "Номер");
    model->setHeaderData(2, Qt::Horizontal, "Группа");
    model->setHeaderData(3, Qt::Horizontal, "Оценка");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(250);
    view->setMinimumWidth(250);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}

void MainWindow::on_pushButton_13_clicked()
{
    out<<"Читатели, взявшие книги в библиотеке : "<<endl;
    takenBooks.WriteToTextFile(out);
    QString header = "Получение записей из файлов";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(350);
    widget->setMinimumWidth(500);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(takenBooks.getCount(), 3);
    for(int i=0; i< takenBooks.getCount(); ++i){
        /*qDebug() << "Student" << i << ":"
                 << takenBooks.GetM()[i].GetName()
                 << takenBooks.GetM()[i].GetAddr()
                 << takenBooks.GetM()[i].GetPrice();*/
        model->setItem(i, 0, new QStandardItem(takenBooks.GetM()[i].GetName()));
        model->setItem(i, 1, new QStandardItem(takenBooks.GetM()[i].GetAddr()));
        model->setItem(i, 2, new QStandardItem(takenBooks.GetM()[i].GetPriceStr()));
    }
    model->setHeaderData(0, Qt::Horizontal, "Имя");
    model->setHeaderData(1, Qt::Horizontal, "Адрес");
    model->setHeaderData(2, Qt::Horizontal, "Цена");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(250);
    view->setMinimumWidth(250);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}


void MainWindow::on_pushButton_14_clicked()
{
    out<<"Читатели, вернувшие книги в библиотеку : "<<endl;
    returnedBooks.WriteToTextFile(out);
    QString header = "Получение записей из файлов";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(500);
    widget->setMinimumWidth(100);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(returnedBooks.getCount()-1, 1);
    for(int i=0; i< returnedBooks.getCount()-1; ++i){
        model->setItem(i, 0, new QStandardItem(returnedBooks.GetM()[i].GetName()));
    }
    model->setHeaderData(0, Qt::Horizontal, "Имя");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(250);
    view->setMinimumWidth(250);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}


void MainWindow::on_pushButton_15_clicked()
{
    STUD<Stud3> debtors = findDebtors(takenBooks, returnedBooks);
    out<<"Читатели, не вернувшие книги в библиотеку : "<<endl;
    debtors.WriteToTextFile(out);
    QString header = "Получение информации о должниках";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(350);
    widget->setMinimumWidth(500);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(debtors.getCount(), 4);
    for(int i=0; i< debtors.getCount(); ++i){
        model->setItem(i, 0, new QStandardItem(debtors.GetM()[i].GetName()));
        model->setItem(i, 1, new QStandardItem(debtors.GetM()[i].GetAddr()));
        model->setItem(i, 2, new QStandardItem(debtors.GetM()[i].GetPriceStr()));
        model->setItem(i, 3, new QStandardItem(debtors.GetM()[i].GetControlDate()));
    }
    model->setHeaderData(0, Qt::Horizontal, "Имя");
    model->setHeaderData(1, Qt::Horizontal, "Адрес");
    model->setHeaderData(2, Qt::Horizontal, "Цена");
    model->setHeaderData(3, Qt::Horizontal, "Дата");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(250);
    view->setMinimumWidth(250);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    layout->addWidget(closeButton);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
    widget->setLayout(layout);
    widget->show();
}


void MainWindow::on_pushButton_16_clicked()
{
    outFile.close();
    QApplication::quit();
}

