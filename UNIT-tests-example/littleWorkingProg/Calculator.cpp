// Calculator.cpp
#include "Calculator.h"

double Calculator::sum(double a, double b) {
    return a + b;
}

double Calculator::dif() {
    return a1 - b1;
}

double Calculator::mul(double a, double b) {
    return a * b;
}
void Calculator::SetA(double a){
    a1 = a;
}
void Calculator::SetB(double b){
    b1 = b;
}
double Calculator::div(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}
