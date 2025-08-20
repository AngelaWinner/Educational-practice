// InfoDialog.h
#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>

class InfoDialog : public QDialog {
    Q_OBJECT
public:
    explicit InfoDialog(QWidget *parent = nullptr);
};

#endif // INFODIALOG_H
