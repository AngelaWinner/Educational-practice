#pragma once
#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QStringList>
using namespace Qt;
class Person {
protected:
    QString* name;
    int age;
    double weight;
public:
    Person();
    Person(QString* name1, int age1, double weight1);
    virtual ~Person();
    virtual QStringList printAll() const;
    virtual void printName() const = 0;//чисто виртуальный метод(не имеет реализации в базовом классе)
    virtual void printAge() const = 0;
    virtual void printWeight() const = 0;
};
class OldPerson : public Person {
    QString number;
public:
    OldPerson();
    OldPerson(QString* name1, QString number1 = "10000", int age1 = 18, double weight1 = 55.5);
    ~OldPerson();
    QStringList printAll() const override;
    void printName() const override;
    void printAge() const override;
    void printWeight() const override;
    void printNumber() const;
    void changeAge(int n);
    QString getName();
    int getAge();
    QString getAgeStr();
    QString getWeightStr();
    QString getNumber();
    void changeNumber(QString str);
    OldPerson& operator=(const OldPerson& other);
};