// Calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdexcept>

class Calculator {
private:
    double a1, b1;
public:
    Calculator() : a1(0), b1(0) {}
    double sum(double a, double b);
    double dif();
    void SetA(double a);
    void SetB(double b);
    double mul(double a, double b);
    double div(double a, double b);
};

#endif // CALCULATOR_H
