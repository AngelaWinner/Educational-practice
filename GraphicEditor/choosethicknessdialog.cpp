#include "choosethicknessdialog.h"

ChooseThicknessDialog::ChooseThicknessDialog(QWidget *parent) : QDialog(parent), thickness(lowValue)
{
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(lowValue, upValue); // допустимый диапазон толщины
    slider->setValue(lowValue);

    lineEdit = new QLineEdit(QString::number(slider->value()));
    lineEdit->setFixedWidth(50);

    connect(slider, &QSlider::valueChanged, this, &ChooseThicknessDialog::onSliderValueChanged);
    connect(lineEdit, &QLineEdit::editingFinished, this, &ChooseThicknessDialog::on_OkButton_Clicked);

    okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, this, &ChooseThicknessDialog::on_OkButton_Clicked);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);
    hLayout->addWidget(lineEdit);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(okButton);

    setLayout(vLayout);
    setWindowTitle("Выберите толщину");
}

void ChooseThicknessDialog::onSliderValueChanged(int value)
{
    lineEdit->setText(QString::number(value));
}

void ChooseThicknessDialog::on_OkButton_Clicked()
{
    bool ok;
    int value = lineEdit->text().toInt(&ok);
    if (ok && value >= lowValue && value <= upValue) {
        thickness = value;
        accept(); // закрывает диалог
    } else {
        QMessageBox::warning(this, "Ошибка", QString("Введите число от %1 до %2").arg(lowValue).arg(upValue));
        lineEdit->setFocus();
    }
}

int ChooseThicknessDialog::getThickness() const
{
    return thickness;
}
