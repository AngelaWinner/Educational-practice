// filldialog.h
#ifndef FILLDIALOG_H
#define FILLDIALOG_H

#include <QDialog>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FillDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FillDialog(QWidget *parent = nullptr);

    QColor getFillColor() const;
    QColor getBorderColor() const;

private slots:
    void chooseFillColor();
    void chooseBorderColor();
    void okButtonSlot();

private:
    QLabel *fillColorLabel;
    QLabel *borderColorLabel;

    QLabel *fillColorPreview;
    QLabel *borderColorPreview;

    QPushButton *chooseFillColorButton;
    QPushButton *chooseBorderColorButton;
    QPushButton *okButton;

    QColor fillColor;
    QColor borderColor;

    bool fillColorChosen = false;
    bool borderColorChosen = false;
};

#endif // FILLDIALOG_H
