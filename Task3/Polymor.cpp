#include "Polymor.h"
Person :: Person(QString* name1, int age1, double weight1) {
    name = new QString(*name1);
    age = age1;
    weight = weight1;
}
Person::Person() : name(new QString("")), age(0), weight(0.0) {}
Person:: ~Person() {
    delete name;
    //cout << endl<< "destructor of Person" <<endl<< endl;
}
QStringList Person::printAll() const {
    QStringList list;
    list << "name of the person is : " + *name
        << "age is : " + QString::number(age)
        << "weight is : " + QString::number(weight) + " kg ";
    return list;
}
OldPerson :: OldPerson(QString* name1, QString number1, int age1, double weight1) : Person(name1, age1, weight1) {
    number = number1;
}
OldPerson :: ~OldPerson() {
    //delete name;
}
QStringList OldPerson:: printAll() const {
    QStringList list;
    list << "name of the person is : " + *name
        << "age is : " + QString::number(age)
        << "weight is : " + QString::number(weight) + " kg "
        << "number of passport is : " << number;
    return list;
}
void OldPerson:: printName() const {
    qDebug() << "name of the person is : " << *name << endl;
}
void OldPerson::printAge() const {
    qDebug() << "age of " << *name << " is : " << age << endl;
}
void OldPerson::printWeight() const {
    qDebug() << "weight of " << *name << " is : " << weight << " kg " << endl;
}
void OldPerson::printNumber() const {
    qDebug() << "number of passport of " << *name << " is : " << number << endl;
}
void OldPerson::changeAge(int n) {
    age = n;
}
QString OldPerson::getName() {
    return *name;
}
int OldPerson::getAge() {
    return age;
}
QString OldPerson::getAgeStr() {
    return QString::number(age);
}
QString OldPerson::getWeightStr() {
    return QString::number(weight);
}
QString OldPerson::getNumber() {
    return number;
}
void OldPerson:: changeNumber(QString str) {
    number = str;
}
OldPerson& OldPerson::operator=(const OldPerson& other) {
    if (this != &other) {
        delete name;
        name = new QString(*other.name);
        this->age = other.age;
        this->weight = other.weight;
        this->number = other.number;
    }
    return *this;
}
OldPerson::OldPerson()
    : Person(), number("") {
}