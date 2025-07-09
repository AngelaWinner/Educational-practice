#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setText(QStringList objects) {
    ui->textBrowser->setPlainText(objects.join("\n"));
}
void Dialog::setPlainText(QString str) {
    ui->textBrowser->setPlainText(str);
}
void Dialog::on_pushButton_close_clicked()
{
    hide();
}

