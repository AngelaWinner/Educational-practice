// filldialog.cpp
#include "filldialog.h"
#include <QColorDialog>
#include <QMessageBox>
FillDialog::FillDialog(QWidget *parent)
    : QDialog(parent),
    fillColor(Qt::white),
    borderColor(Qt::black)
{
    // Создаем метки
    fillColorLabel = new QLabel("Цвет заливки: ", this);
    borderColorLabel = new QLabel("Цвет границы: ", this);

    // Создаем кнопки
    chooseFillColorButton = new QPushButton("Выбрать цвет заливки", this);
    chooseBorderColorButton = new QPushButton("Выбрать цвет границы", this);
    okButton = new QPushButton("Готово", this);

    // Связываем сигналы с слотами
    connect(chooseFillColorButton, &QPushButton::clicked, this, &FillDialog::chooseFillColor);
    connect(chooseBorderColorButton, &QPushButton::clicked, this, &FillDialog::chooseBorderColor);
    connect(okButton, &QPushButton::clicked, this, &FillDialog::okButtonSlot);

    fillColorPreview = new QLabel(this);
    fillColorPreview->setFixedSize(40, 40); // размер квадратика
    fillColorPreview->setFrameStyle(QFrame::Box | QFrame::Plain);
    fillColorPreview->setLineWidth(1);
    fillColorPreview->setStyleSheet(QString("background-color: %1").arg(fillColor.name()));

    borderColorPreview = new QLabel(this);
    borderColorPreview->setFixedSize(40, 40);
    borderColorPreview->setFrameStyle(QFrame::Box | QFrame::Plain);
    borderColorPreview->setLineWidth(1);
    borderColorPreview->setStyleSheet(QString("background-color: %1").arg(borderColor.name()));

    QHBoxLayout *fillColorLayout = new QHBoxLayout;
    fillColorLayout->addWidget(fillColorLabel);
    fillColorLayout->addWidget(fillColorPreview);
    fillColorLayout->addWidget(chooseFillColorButton);

    QHBoxLayout *borderColorLayout = new QHBoxLayout;
    borderColorLayout->addWidget(borderColorLabel);
    borderColorLayout->addWidget(borderColorPreview);
    borderColorLayout->addWidget(chooseBorderColorButton);

    // Основной макет
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fillColorLayout);
    mainLayout->addLayout(borderColorLayout);
    mainLayout->addWidget(okButton);
    setLayout(mainLayout);

    setLayout(mainLayout);
    setWindowTitle("Выбор цветов");
}

QColor FillDialog::getFillColor() const { return fillColor; }
QColor FillDialog::getBorderColor() const { return borderColor; }

void FillDialog::okButtonSlot()
{
    if (fillColorChosen && borderColorChosen)
        accept();
    else
        QMessageBox::warning(this, "Выбор цвета", "Пожалуйста, выберите оба цвета.");
}

void FillDialog::chooseFillColor()
{
    QColor color = QColorDialog::getColor(fillColor, this, "Выберите цвет заливки");
    if (color.isValid()) {
        fillColor = color;
        fillColorLabel->setText(QString("Цвет заливки: %1").arg(fillColor.name()));
        fillColorPreview->setStyleSheet(QString("background-color: %1").arg(fillColor.name()));
        fillColorChosen = true;
    }
}

void FillDialog::chooseBorderColor()
{
    QColor color = QColorDialog::getColor(borderColor, this, "Выберите цвет границы");
    if (color.isValid()) {
        borderColor = color;
        borderColorLabel->setText(QString("Цвет границы: %1").arg(borderColor.name()));
        borderColorPreview->setStyleSheet(QString("background-color: %1").arg(borderColor.name()));
        borderColorChosen = true;
    }
}
