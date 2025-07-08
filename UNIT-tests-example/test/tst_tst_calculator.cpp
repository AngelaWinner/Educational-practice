#include <QtTest>
#include "../littleWorkingProg/Calculator.h"
class tst_Calculator : public QObject
{
    Q_OBJECT

public:
    tst_Calculator();
    ~tst_Calculator();

private slots:
    void testSum();
    void testDif();
    void testDif_data();
    void testMul();
    void testDiv();
};

void tst_Calculator::testSum() {
    Calculator calc;
    QCOMPARE(calc.sum(2.0, 3.0), 5.0);
    QCOMPARE(calc.sum(-2.0, 3.0), 1.0);
    QCOMPARE(calc.sum(2.0, -3.0), -1.0);
    QCOMPARE(calc.sum(-2.0, -3.0), -5.0);
    QCOMPARE(calc.sum(0.0, 3.0), 3.0);
    QCOMPARE(calc.sum(3.0, 0.0), 3.0);
    QCOMPARE(calc.sum(0.0, 0.0), 0.0);
}

/*void tst_Calculator::testDif() {
    Calculator calc;
    QCOMPARE(calc.dif(2.0, 3.0), -1.0);
    QCOMPARE(calc.dif(-2.0, 3.0), -5.0);
    QCOMPARE(calc.dif(2.0, -3.0), 5.0);
    QCOMPARE(calc.dif(-2.0, -3.0), 1.0);
    QCOMPARE(calc.dif(0.0, 3.0), -3.0);
    QCOMPARE(calc.dif(3.0, 0.0), 3.0);
    QCOMPARE(calc.dif(0.0, 0.0), 0.0);
}*/
void tst_Calculator::testDif_data() {
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("result");
    QTest::newRow("all 0") << 0 << 0 << 0;
    QTest::newRow("same number") << 10 << 10 << 0;
    QTest::newRow("different positive numbers, first bigger, second smaller") << 15 << 13 << 2;
}
void tst_Calculator::testDif() {
    Calculator mCalc;
    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, result);
    mCalc.SetA(a);
    mCalc.SetB(b);
    QCOMPARE(mCalc.dif(), result);
}
void tst_Calculator::testMul() {
    Calculator calc;
    QCOMPARE(calc.mul(2.0, 3.0), 6.0);
    QCOMPARE(calc.mul(-2.0, 3.0), -6.0);
    QCOMPARE(calc.mul(2.0, -3.0), -6.0);
    QCOMPARE(calc.mul(-2.0, -3.0), 6.0);
    QCOMPARE(calc.mul(0.0, 3.0), 0.0);
    QCOMPARE(calc.mul(3.0, 0.0), 0.0);
    QCOMPARE(calc.mul(0.0, 0.0), 0.0);
}
void tst_Calculator::testDiv() {
    Calculator calc;
    QCOMPARE(calc.div(0.0, 3.0), 0.0);
    QSKIP("Пропуск этой проверки", SkipReason);
    QCOMPARE(calc.div(2.0, 3.0), 0.6);
    QCOMPARE(calc.div(-2.0, 3.0), -0.6);
    QCOMPARE(calc.div(2.0, -3.0), -0.6);
    QCOMPARE(calc.div(-2.0, -3.0), 0.6);
}
tst_Calculator::tst_Calculator() {}

tst_Calculator::~tst_Calculator() {}

QTEST_APPLESS_MAIN(tst_Calculator)

#include "tst_tst_calculator.moc"
