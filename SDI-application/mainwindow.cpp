#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QFontDialog>
#include <QLabel>
#include <QLayout>
#include <QToolBar>
#include <QTextBrowser>
#include <QPushButton>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
MainWindow::MainWindow(QString currentFileName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->TextChanged = false;
    QMenu* FileMenu = new QMenu("File");
    QMenu* EditMenu = new QMenu("Edit");
    QMenu* ViewMenu = new QMenu("View");
    QMenu* HelpMenu = new QMenu("Help");

    QAction* NewAction = new QAction(QIcon(":/rec/img/newFile.jpg"), "New");
    QAction* OpenAction = new QAction(QIcon(":/rec/img/open.jpg"),"Open");
    QAction* SetFontAction = new QAction(QIcon(":/rec/img/setFont.jpg"),"Font");
    QAction* AboutAction = new QAction(QIcon(":/rec/img/info.jpg"),"About");
    QAction* ExitAction = new QAction(QIcon(":/rec/img/exit.jpg"),"Exit");
    QAction* SaveAction = new QAction(QIcon(":/rec/img/save.jpg"),"Save");
    QAction* SaveAsAction = new QAction(QIcon(":/rec/img/saveAs.jpg"),"Save As");

    NewAction->setShortcut(tr("Ctrl+N"));
    OpenAction->setShortcut(tr("Ctrl+O"));

    QObject::connect(NewAction,SIGNAL(triggered()),this,SLOT(NewFileActionSlot()));
    QObject::connect(OpenAction,SIGNAL(triggered()),this,SLOT(OpenFileActionSlot()));
    QObject::connect(SetFontAction,SIGNAL(triggered()),this,SLOT(SetFontTriggered()));
    QObject::connect(AboutAction,SIGNAL(triggered()),this,SLOT(aboutActionSlot()));
    QObject::connect(ExitAction,SIGNAL(triggered()),this,SLOT(exitTriggered()));
    QObject::connect(SaveAction,SIGNAL(triggered()),this,SLOT(SaveFileActionSlot()));
    QObject::connect(SaveAsAction,SIGNAL(triggered()),this,SLOT(SaveAsFileActionSlot()));

    FileMenu->addAction(NewAction);
    FileMenu->addAction(OpenAction);
    FileMenu->addAction(SaveAction);
    FileMenu->addAction(SaveAsAction);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAction);
    ViewMenu->addAction(SetFontAction);
    HelpMenu->addAction(AboutAction);

    this->menuBar()->addMenu(FileMenu);
    this->menuBar()->addMenu(EditMenu);
    this->menuBar()->addMenu(ViewMenu);
    this->menuBar()->addMenu(HelpMenu);

    this->textEdit = new QTextEdit;
    this->setCentralWidget(textEdit);
    QObject::connect(this->textEdit,SIGNAL(textChanged()),this,SLOT(textChanged()));

    //создаю специально для тулбара действия без иконок, поскольку не все иконки очевидны
    QAction* NewActionText = new QAction("New");
    QAction* OpenActionText = new QAction("Open");
    QAction* AboutActionText = new QAction("About");
    QAction* SaveActionText = new QAction("Save");
    QAction* SaveAsActionText = new QAction("Save As");

    connect(NewActionText, &QAction::triggered, NewAction, &QAction::trigger);
    connect(OpenActionText, &QAction::triggered, OpenAction, &QAction::trigger);
    connect(SaveActionText, &QAction::triggered, SaveAction, &QAction::trigger);
    connect(SaveAsActionText, &QAction::triggered, SaveAsAction, &QAction::trigger);
    connect(AboutActionText, &QAction::triggered, AboutAction, &QAction::trigger);

    QToolBar* toolBar = this->addToolBar(tr("New"));
    toolBar->addAction(NewActionText);
    toolBar->addAction(OpenActionText);
    toolBar->addAction(SaveActionText);
    toolBar->addAction(SaveAsActionText);
    toolBar->addSeparator();
    toolBar->addAction(AboutActionText);

    this->file = nullptr;
    this->currentFileName = currentFileName;
}

MainWindow::~MainWindow()
{
    delete ui;
    if(file) delete file;
}
void MainWindow::NewFileActionSlot()
{
    if (this->TextChanged) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Unsaved Changes", "Do you want to save changes before creating a new file?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Cancel) {
            return;
        } else if (reply == QMessageBox::Yes) {
            SaveFileActionSlot();
        }
    }
    this->textEdit->clear();
    if (this->file) {
        delete this->file;
        this->file = nullptr;
    }
    this->setWindowTitle("New Document");
    this->TextChanged = false;
}
void MainWindow::OpenFileActionSlot()
{
    if(this->file && !this->isSafeToClose())
        return;
    if(this->file)
        this->file->close();
    QString name = QFileDialog::getOpenFileName(this,"Get Open File Name");
    if(name=="")
        return;
    delete this->file;
    this->file = new QFile(name);
    if(!this->file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Error","There was an error while opening file");
        return;
    }
    this->setWindowTitle(this->file->fileName());
    QString text;
    QTextStream fileTextStream(this->file);
    text = fileTextStream.readAll();
    this->textEdit->setPlainText(text);
    this->TextChanged = false;
    this->file->close();
}
bool MainWindow::isSafeToClose()
{
    if (!TextChanged)
        return true;
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Unsaved Changes", "Save changes before closing?",
        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Cancel);
    if(reply == QMessageBox::Yes)
    {
        SaveFileActionSlot();
        return true;
    }
    else if(reply == QMessageBox::No)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::SaveFileActionSlot()
{
     if (this->file) {
            if (this->file->open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream outStream(this->file);
                outStream << this->textEdit->document()->toPlainText();
                this->file->close();
                QMessageBox::information(this, "Saved", "Saved Successfully");
                this->setWindowTitle(this->file->fileName());
                this->TextChanged = false;
            } else {
                QMessageBox::warning(this, "Error", "Cannot open file for writing");
            }
        } else {
            QString fileName = QFileDialog::getSaveFileName(this, "Save as");
            if (fileName.isEmpty()) {
                return;
            }
            if (!fileName.endsWith(".txt")) {
                fileName += ".txt";
            }
            QFile* newFile = new QFile(fileName);
            if (newFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream outStream(newFile);
                outStream << this->textEdit->toPlainText();
                newFile->close();
                delete this->file;
                this->file = newFile;
                this->setWindowTitle(this->file->fileName());
                QMessageBox::information(this, "Saved", "Saved Successfully");
                this->TextChanged = false;
            } else {
                QMessageBox::warning(this, "Error", "Error opening file for writing");
                delete newFile;
            }
        }
}
void MainWindow::SaveAsFileActionSlot()
{
    QString name = QFileDialog::getSaveFileName(this,"Save As");
    if (name.isEmpty()) return;
    if (!name.endsWith(".txt")) name += ".txt";
    if (this->TextChanged) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save Changes", "Do you want to save changes?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel) {
            return;
        }
        if (reply == QMessageBox::Yes) {
            if (this->file && this->file->isOpen()) {
                QTextStream fileTextStream(file);
                fileTextStream << textEdit->document()->toPlainText();
                this->file->close();
            } else {
                QFile saveFile(name);
                if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::warning(this, "Error", "Error opening file for writing");
                    return;
                }
                QTextStream outSaveStream(&saveFile);
                outSaveStream << textEdit->document()->toPlainText();
                saveFile.close();

                this->file = new QFile(name);
                setWindowTitle(name);
            }
            this->TextChanged = false;
        }
    }
}

void MainWindow::SetFontTriggered()
{
    bool ok=false;
    QFont font = QFontDialog::getFont(&ok);
    if(ok){
        this->textEdit->setFont(font);
    }
}

void MainWindow::aboutActionSlot()
{
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QString text = "Программа написана Некрасовой Анжелой Борисовной, студенткой 5 группы 1 курса ФПМИ БГУ\n";
    text += "Разработка простейшего SDI-приложения, иллюстрирующего использование меню, корректировку, сохранение и восстановление текстовой, числовой информации в текстовом (QTextStream) формате.\n";
    QTextBrowser* textBrowser = new QTextBrowser(dialog);
    textBrowser->setText(text);
    layout->addWidget(textBrowser);
    QPushButton* closeAboutButton = new QPushButton("Close About Menu", dialog);
    QObject::connect(closeAboutButton, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(closeAboutButton);
    dialog->resize(400,200);
    dialog->setWindowTitle("About");
    dialog->show();
}
void MainWindow::exitTriggered()
{
    this->close();
}

void MainWindow::textChanged()
{
    if(!this->TextChanged && !this->windowTitle().endsWith("*")){
        this->setWindowTitle(this->windowTitle() + "*");
    }
    this->TextChanged = true;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(!this->TextChanged || this->isSafeToClose()){
        event->accept();
    }else
        event->ignore();
}
