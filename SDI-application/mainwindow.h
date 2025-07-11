#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTextEdit *textEdit;
    QString currentFileName;
    bool TextChanged;
    QFile* file;

public:
    MainWindow(QString currentFileName,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *);
    bool isSafeToClose();
private slots:
    void NewFileActionSlot();
    void OpenFileActionSlot();
    void SaveFileActionSlot();
    void SaveAsFileActionSlot();
    void SetFontTriggered();
    void aboutActionSlot();
    void exitTriggered();
    void textChanged();
};
#endif // MAINWINDOW_H
