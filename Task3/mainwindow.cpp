#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Polymor.cpp"
#include <QStandardItemModel>
#include <QTableView>
#include <QMessageBox>
#include <QSet>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString* name = new QString{};
    *name = "Aleksandr";
    person1 =  OldPerson(name, "12345");
    *name = "Sonya";
    person2 =  OldPerson(name);
    *name = "Aliya";
    person3 =  OldPerson(name, "10010", 19);
    *name = "Stephan";
    person4 =  OldPerson(name, "10201", 21, 75.3);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::printPersonAllInfo);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::printPersonAllInfo);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::printPersonAllInfo);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::changePassportNumber);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::changePassportNumber);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::changePassportNumber);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::changePassportNumber);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::changeAge);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::changeAge);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::changeAge);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::changeAge);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString header = "Получение полной информации о человеке";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(400);
    widget->setMinimumWidth(400);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(4, 2);
    model->setItem(0, 0, new QStandardItem("Имя"));
    model->setItem(0, 1, new QStandardItem(person1.getName()));
    model->setItem(1, 0, new QStandardItem("Возраст"));
    model->setItem(1, 1, new QStandardItem(person1.getAgeStr()));
    model->setItem(2, 0, new QStandardItem("Вес"));
    model->setItem(2, 1, new QStandardItem(person1.getWeightStr()));
    model->setItem(3, 0, new QStandardItem("Номер паспорта"));
    model->setItem(3, 1, new QStandardItem(person1.getNumber()));
    model->setHeaderData(0, Qt::Horizontal, "Информация");
    model->setHeaderData(1, Qt::Horizontal, "Данные");
    QTableView *view = new QTableView(widget);
    view->setMinimumHeight(100);
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
void MainWindow :: printPersonAllInfo(){
    QPushButton *button = (QPushButton*)(sender());
    OldPerson* person = &person2;
    if(button->text()=="Aleksandr") {
        person = &person1;
    } else     if(button->text()=="Sonya") {
        person = &person2;
    } else if(button->text()=="Aliya") {
        person = &person3;
    } else if(button->text()=="Stephan") {
        person = &person4;
    }
    QString header = "Получение информации о человеке";
    ui->statusbar->showMessage(header);
    QWidget* widget = new QWidget;
    widget->setWindowTitle(header);
    widget->setMinimumHeight(400);
    widget->setMinimumWidth(400);
    QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
    QStandardItemModel* model=  new QStandardItemModel(4, 2);
    model->setItem(0, 0, new QStandardItem("Имя"));
    model->setItem(0, 1, new QStandardItem(person->getName()));
    model->setItem(1, 0, new QStandardItem("Возраст"));
    model->setItem(1, 1, new QStandardItem(person->getAgeStr()));
    model->setItem(2, 0, new QStandardItem("Вес"));
    model->setItem(2, 1, new QStandardItem(person->getWeightStr()));
    model->setItem(3, 0, new QStandardItem("Номер паспорта"));
    model->setItem(3, 1, new QStandardItem(person->getNumber()));
    model->setHeaderData(0, Qt::Horizontal, "Информация");
    model->setHeaderData(1, Qt::Horizontal, "Данные");
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
    ui->statusbar->showMessage("Получение информации");
}

void MainWindow :: changePassportNumber(){
    QPushButton *button = (QPushButton*)(sender());
    QString input = ui->lineEdit->text();
    QRegularExpression rgx(R"(\s*(\d+)\s*)");
    QRegularExpressionMatch match = rgx.match(input);
    if (match.hasMatch()) {
        QString number = match.captured(1);
        if(number.size()<=4 || number.size()>5) {
            QMessageBox::warning(this, "Некорректный формат", "Номер паспорта не соответствует образцу (длина должна быть 5 символов).");
        } else {
            QSet<QString> set;
            set.insert(person1.getNumber());
            set.insert(person2.getNumber());
            set.insert(person3.getNumber());
            set.insert(person4.getNumber());
            if (set.contains(number)) {
                QMessageBox::warning(this, "Отсутствие уникальности", "Номер паспорта должен быть уникальным");
            } else {
            OldPerson* person;
            if(button->text()=="Aleksandr") {
                set.remove(person1.getNumber());
                person = &person1;
                person->changeNumber(number);
            } else     if(button->text()=="Sonya") {
                set.remove(person2.getNumber());
                person = &person2;
                person->changeNumber(number);
            } else if(button->text()=="Aliya") {
                set.remove(person3.getNumber());
                person = &person3;
                person->changeNumber(number);
            } else if(button->text()=="Stephan") {
                set.remove(person4.getNumber());
                person = &person4;
                person->changeNumber(number);
            }
            set.insert(number);
            QString header = "Изменение номера паспорта";
            ui->statusbar->showMessage(header);
            QWidget* widget = new QWidget;
            widget->setWindowTitle(header);
            widget->setMinimumHeight(400);
            widget->setMinimumWidth(400);
            QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
            QStandardItemModel* model=  new QStandardItemModel(1, 2);
            model->setItem(0, 0, new QStandardItem("Имя"));
            model->setItem(0, 1, new QStandardItem(person->getName()));
            model->setItem(1, 0, new QStandardItem("Номер паспорта"));
            model->setItem(1, 1, new QStandardItem(person->getNumber()));
            model->setHeaderData(0, Qt::Horizontal, "Имя");
            model->setHeaderData(1, Qt::Horizontal, "Паспорт");
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
        }
    } else {
        QMessageBox::warning(this, "Некорректный формат", "Номер паспорта не соответствует образцу (длина должна быть 5 символов).");
    }
    ui->statusbar->showMessage("Изменение номера паспорта");
}
void MainWindow :: changeAge(){
    QPushButton *button = (QPushButton*)(sender());
    QString input = ui->lineEdit_2->text();
    QRegularExpression rgx(R"(\s*(\d+)\s*)");
    QRegularExpressionMatch match = rgx.match(input);
    if (match.hasMatch()) {
        int number = match.captured(1).toInt();
        if(number<=0 || number>=150) {
            QMessageBox::warning(this, "Некорректный формат", "возраст не соответствует заданному условием");
        } else {
            OldPerson* person;
            if(button->text()=="Aleksandr") {
                person = &person1;
                if(number<person->getAge()) {
                    QMessageBox::warning(this, "Некорректный формат", "возраст человека не может быть меньше его настоящего возраста");
                } else person->changeAge(number);
            } else     if(button->text()=="Sonya") {
                person = &person2;
                if(number<person->getAge()) {
                    QMessageBox::warning(this, "Некорректный формат", "возраст человека не может быть меньше его настоящего возраста");
                } else person->changeAge(number);
            } else if(button->text()=="Aliya") {
                person = &person3;
                if(number<person->getAge()) {
                    QMessageBox::warning(this, "Некорректный формат", "возраст человека не может быть меньше его настоящего возраста");
                } else person->changeAge(number);
            } else if(button->text()=="Stephan") {
                person = &person4;
                if(number<person->getAge()) {
                    QMessageBox::warning(this, "Некорректный формат", "возраст человека не может быть меньше его настоящего возраста");
                } else person->changeAge(number);
            }
            QString header = "Изменение возраста";
            ui->statusbar->showMessage(header);
            QWidget* widget = new QWidget;
            widget->setWindowTitle(header);
            widget->setMinimumHeight(100);
            widget->setMinimumWidth(100);
            QPushButton* closeButton = new QPushButton("Закрыть вылетевшее окно", widget);
            QStandardItemModel* model=  new QStandardItemModel(1, 2);
            model->setItem(0, 0, new QStandardItem("Имя"));
            model->setItem(0, 1, new QStandardItem(person->getName()));
            model->setItem(1, 0, new QStandardItem("Возраст"));
            model->setItem(1, 1, new QStandardItem(person->getAgeStr()));
            model->setHeaderData(0, Qt::Horizontal, "Имя");
            model->setHeaderData(1, Qt::Horizontal, "Возраст");
            QTableView *view = new QTableView(widget);
            view->setMinimumHeight(100);
            view->setMinimumWidth(100);
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);
            view->setModel(model);
            QVBoxLayout* layout = new QVBoxLayout(widget);
            layout->addWidget(view);
            layout->addWidget(closeButton);
            QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);
            widget->setLayout(layout);
            widget->show();

        }
    } else {
        QMessageBox::warning(this, "Некорректный формат", "Введенная строка не соответствует образцу");
    }
    ui->statusbar->showMessage("Изменение возраста");
}
