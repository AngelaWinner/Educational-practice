#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H
#pragma once
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QRegularExpression>
using namespace std;
class Element {
public:
    int data;
    Element* next;
    Element* prev;
    Element(int value);
};
class List {
private:
    Element* head;
    Element* tail;
public:
    List();
    ~List();
    bool empty();
    void clear();
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    void readFromFile(const QString& filename);
    void print(QTextStream& out);
    void change();
    QString join(const QString& separator);
    QString print();
    int size() const;
};
#endif // WORKWITHFILES_H