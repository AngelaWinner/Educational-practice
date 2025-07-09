#include "chisla.h"
#include <iostream>
int Chisla::GetC() {
    return c;
}
int Chisla::GetA() {
    return a;
}
int Chisla::GetB() {
    return b;
}
void Chisla::SetA(int xa) {
    a = xa;
}
void Chisla::SetB(int xb) {
    b = xb;
}
Chisla::Chisla() {
    a = 1;
    b = 2;
    c = 0;
    std::cout << "the designer volunteered" << std::endl;
}
Chisla::~Chisla() {
    std::cout << "the destructor volunteered" << std::endl;
}
Chisla::Chisla(const Chisla& other) {
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    std::cout << "the copy constructor volunteered " << std::endl;
}
Chisla::Chisla(int xa) {
    a = xa;
    b = 4;
    c = 0;
    std::cout << "the designer volunteered" << std::endl;
}
Chisla::Chisla(int xa, int xb) {
    a = xa;
    b = xb;
    c = 0;
    std::cout << "the designer volunteered " << std::endl;
}
int Chisla::Fact() {
    if (a < 0) {
        std::cout << "Error: The factorial of a negative number is not defined." << std::endl;
        return 0;
    }
    if (a >= 16) {
        std::cout << "Error: Factorial as an integer may have size limitations. The number is too large and the factorial cannot be calculated" << std::endl;
        return 0;
    }
    c = 1;
    for (int i = 1; i <= a; i++) {
        c *= i;
    }
    return c;
}
QStringList Chisla::taskB8() {
    QStringList list;
    auto NOD = [](int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
        };

    if (a <= 0) {
        return list;
    }

    for (int i = 1, count = 0; count < a; ++i) {
        int a1, b1;
        if (i % 2 == 1) {
            a1 = i;
            b1 = i + 2;
        }
        else {
            a1 = i;
            b1 = i + 1;
        }

        if (NOD(a1, b1) == 1) {
            list << QString("%1, %2").arg(a1).arg(b1);
            ++count;
        }
    }
    return list;
}
void Chisla::SumCifr() {
    int n;
    if (a < 0)
        n = (-1) * a;
    else
        n = a;
    c = 0;
    while (n != 0) {
        c += (n % 10);
        n /= 10;
    }
    std::cout << "sum of digits of a number " << a << " by module = ";
}
QStringList Chisla::taskB7() {
    QStringList list;
    if (a <= 0) {
        std::cout << "the number of numbers cannot be <=0" << std::endl;
        return list;
    }
    std::cout << "automorphic numbers of a given quantity" << this->a << ": " << std::endl;
    int number = 0;
    long long i = 1;
    while (number < a) {
        int n = 1;
        int a1 = i;
        while (a1 != 0) {
            a1 = a1 / 10;
            n = n * 10;
        }
        if (i == (i * i) % n)
        {
            list << QString::number(i);
            number++;
        }
        i++;
        n = 1;
    }
    return list;
}
QStringList Chisla::taskC7() {
    QStringList result;

    result << "Значение a: " + QString::number(a);
    result << "Значение b: " + QString::number(b);
    if (b <= 0 || a < 0) {
        result << "Ошибка: одно или оба числа не являются натуральными или равно 0.";
        return result;
    }
    int a1 = a;
    int cel = 0;
    int ost = 0;

    if (a == b) {
        result << "При делении a на b: частное = 1, остаток = 0.";
        return result;
    }

    if (a < b) {
        result << "При делении a на b: частное = 0, остаток = " + QString::number(a) + ".";
        return result;
    }

    while (a1 - b >= 0) {
        a1 -= b;
        ++cel;
    }
    ost = a1;

    result << "При делении a на b: частное = " + QString::number(cel) + ", остаток = " + QString::number(ost) + ".";

    return result;
}




QStringList Chisla::taskC8() {
    QStringList result;
    if (a < 0) {
        result << "Ошибка: число n не может быть меньше 0.";
        return result;
    }
    result << "Дано натуральное число : " + QString::number(a);
    result << "Подсчет количества решений неравенства x*x + y*y < n в натуральных (неотрицательных целых) числах.";

    int s = 0;
    for (int x = 0; x < a; x++) {
        int y = x;
        int k = 0;
        while (y * y < a) {
            if ((x * x) + (y * y) < a)
                k++;
            y++;
        }
        s += k;
    }

    result << "Количество решений: " + QString::number(s) + ".";
    return result;
}
QStringList Chisla::getList() {
    QStringList list;
    list << QString("a : %1").arg(a)
        << QString("b : %1").arg(b)
        << QString("c : %1").arg(c);
    return list;
}
// Дружественная функция
int SumCifr(int n) {
    int sum = 0;
    int r = n;
    while (r != 0) {
        sum += r % 10;
        r /= 10;
    }
    return sum;
}
// Шаблонная функция для вычисления факториала
template <typename T = int>
void Chisla::SumCifr(T n) {
    c = 0;
    int r = n;
    while (r != 0) {
        c += r % 10;
        r /= 10;
    }
}