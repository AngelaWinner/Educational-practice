#ifndef CHISLA_H
#define CHISLA_H
#pragma once
#include <iostream>
#include <QString>
#include <QStringList>
#include <QDebug>
class Chisla {
private:
    int a, b, c;
public:
    int GetC();
    int GetA();
    int GetB();
    QStringList getList();
    void SetA(int xa);
    void SetB(int xb);
    Chisla();
    Chisla(int);
    Chisla(int, int);
    ~Chisla();
    Chisla(const Chisla& other);

    int Fact();
    friend int SumCifr(int);
    template <typename T> void SumCifr(T n);
    void SumCifr();

    QStringList taskB7(); //Напечатать N автоморфных чисел (напр. 25,625)
    QStringList taskB8(); //Найти N пар взаимно-простых натуральных чисел
    QStringList taskC7(); //Даны натуральные числа а и b, причем b >  0.  Найти частное  и  остаток  при  делении а на b
    QStringList taskC8(); //Дано натуральное n. Подсчитать  количество  решений неравенства  x*x + y*y < n в натуральных (неотрицательных целых) числах
};

int SumCifr(int n);
#endif //CHISLA_H