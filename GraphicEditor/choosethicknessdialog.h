#ifndef THICKNESSDIALOG_H
#define THICKNESSDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class ChooseThicknessDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseThicknessDialog(QWidget *parent = nullptr);

    int getThickness() const;

private slots:
    void onSliderValueChanged(int value);
    void on_OkButton_Clicked();

private:
    QSlider *slider;
    QLineEdit *lineEdit;
    QPushButton *okButton;
    int thickness;
    const int lowValue = 2;
    const int upValue = 20;
};

#endif // THICKNESSDIALOG_H
