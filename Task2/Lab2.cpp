#include "Lab2.h"
void readFromFile(const QString& filename, QStringList& list) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }
    QTextStream in(&file);
    while (!file.atEnd()) {
        QString line = in.readAll();
        QStringList words = line.split(QRegularExpression("[^A-Za-z]+"), Qt::SkipEmptyParts);
        list.append(words);
    }
    file.close();
}
QStringList findWord(QStringList& list, int n) {
    QStringList LenList;
    for (auto el : list) {
        if (el.length() == n) LenList.push_back(el);
    }
    return LenList;
}
void writeToFile(const QString& filename, QStringList& list) {
    QFile outFile(filename);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    QTextStream out(&outFile);
    for (auto el : list) {
        out << el << " ";
    }
    outFile.close();
}
bool isPassWord(QString str) {
    QRegularExpression allowed("^[A-Za-z0-9_]+$");
    if (str.length() >= 8 && allowed.match(str).hasMatch()) return true;
    else return false;
}