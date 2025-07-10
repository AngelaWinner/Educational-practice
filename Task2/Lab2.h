#pragma once
#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

void readFromFile(const QString& filename, QStringList& list);
QStringList findWord(QStringList& list, int n);
void writeToFile(const QString& filename, QStringList& list);
bool isPassWord(QString str);