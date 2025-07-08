#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <QCursor>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    /*QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QIcon buttonIcon(":/rec/img/sort.jpg");
    QPushButton *button2 = new QPushButton();
    QPushButton *button3 = new QPushButton(buttonIcon, "button", this);
    QPushButton *button4 = new QPushButton("Закрыть", this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    centralWidget->setLayout(layout);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QPushButton *pushButton = new QPushButton("Простая кнопка");
    pushButton->setStyleSheet("background-color: blue; font-weight: bold;");
    layout->addWidget(pushButton);
    QRadioButton *radio1 = new QRadioButton("Опция 1");
    QRadioButton *radio2 = new QRadioButton("Опция 2");
    layout->addWidget(radio1);
    layout->addWidget(radio2);
    QCheckBox *checkBox = new QCheckBox("Выбрать функцию");
    layout->addWidget(checkBox);
    QToolButton *toolButton = new QToolButton;
    toolButton->setText("Меню");
    QMenu *menu = new QMenu;
    QAction *action1 = new QAction("Действие 1", this);
    QAction *action2 = new QAction("Действие 2", this);
    connect(action1, &QAction::triggered, this, &MainWindow::action1Triggered);
    connect(action2, &QAction::triggered, this, &MainWindow::action2Triggered);
    menu->addAction(action1);
    menu->addAction(action2);
    toolButton->setMenu(menu);
    //это свойтсво определяет, как будет отображаться меню при взаимодействии с кнопкой.
    toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    layout->addWidget(toolButton);


    QPixmap cursorPixmap(":/rec/img/sort.jpg");
    QCursor customCursor(cursorPixmap);
    pushButton->setCursor(customCursor);*/
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *label = new QLabel("Введите текст и нажмите кнопку", centralWidget);
    lineEdit = new QLineEdit(centralWidget);
    lineEdit->setPlaceholderText("Здесь вводите текст");
    lineEdit->setMaxLength(20); // Ограничение длины
    button = new QPushButton("Показать введенный текст", centralWidget);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    centralWidget->setLayout(layout);
}
void MainWindow::onButtonClicked()
{
    QString text = lineEdit->text();
    qDebug() << "Текущий текст:" << text;
    //Установка текста
    lineEdit->setText("Новый текст");
    qDebug() << "После setText:" << lineEdit->text();

    // Очистка поля ввода
    lineEdit->clear();
    qDebug() << "Поле очищено";
}
void MainWindow::action1Triggered()
{
    QMessageBox::information(nullptr, "Меню", "Действие 1 выполнено");
}

void MainWindow::action2Triggered()
{
    QMessageBox::information(nullptr, "Меню", "Действие 2 выполнено");
}
MainWindow::~MainWindow()
{
    //delete ui;
}
