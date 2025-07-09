#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setText(QStringList objects);
    void setPlainText(QString str);

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
