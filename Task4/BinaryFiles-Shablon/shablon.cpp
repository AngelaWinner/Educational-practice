#include "shablon.h"
void Students::readFromFile(const QString& fileName) {
    QFile inputFile(fileName);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла:" << fileName;
        return;
    }
    QTextStream in(&inputFile);
    QString line;
    students.clear();
    QRegularExpression rgx(R"((\d{5})\s([A-Za-z]+)\s([A-Za-z]+)\s(\d+)\s([\d.]+))");
    while (!in.atEnd()) {
        line = in.readLine();
        QRegularExpressionMatch match = rgx.match(line);
        if (match.hasMatch()) {
            int num = match.captured(1).toLong();
            QString name = match.captured(2) + " " + match.captured(3);
            int group = match.captured(4).toInt();
            double grade = match.captured(5).toDouble();
            Student stud(num, name, group, grade);
            students.push_back(stud);
        }
        else {
            qDebug() << "Error in reading inputFile" << endl;
        }
    }
    inputFile.close();
}
void Students::readFromFileBin(const QString& fileName) {
    QFile inputFile(fileName);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file:" << fileName;
        return;
    }
    QDataStream in(&inputFile);
    students.clear();
    while (!in.atEnd()) {
        Student stud;
        in >> stud;
        students.push_back(stud);
    }
    inputFile.close();
}
void Students::printAll(QTextStream& out) const {
    for (const auto& student : students) {
        student.printOne(out);
    }
    out << endl;
}
Students Students::studUnion(const Students& stud1, QTextStream& out) {
    Students result = stud1;
    for (int i = 0; i < students.size(); ++i) {
        bool k = false;
        for (int j = 0; j < stud1.students.size(); ++j) {
            if (students[i] == stud1.students[j]) {
                k = true;
            }
        }
        if (k == false) result.students.push_back(students[i]);
    }
    for (const auto& el : result.students) {
        el.printOne(out);
    }
    out << endl;
    return result;
}
Students Students::studPeresechenie(const Students& stud2, QTextStream& out) {
    Students result;
    for (int i = 0; i < stud2.students.size(); ++i) {
        for (int j = 0; j < students.size(); ++j) {
            if (stud2.students[i] == students[j]) {
                result.students.push_back(stud2.students[i]);
            }
        }
    }
    for (const auto& el : result.students) {
        el.printOne(out);
    }
    out << endl;
    return result;
}
Students Students::studDiffer(const Students& stud2, QTextStream& out) {
    Students result;
    for (int i = 0; i < students.size(); ++i) {
        bool k = false;
        for (int j = 0; j < stud2.students.size(); ++j) {
            if (stud2.students[j] == students[i]) k = true;
        }
        if (k == false)  result.students.push_back(students[i]);
    }
    for (const auto& el : result.students) {
        el.printOne(out);
    }
    out << endl;
    return result;
}
int Students::count() const {
    return students.size();
}
QVector<Students::Student> Students::GetStudents() const {
    return students;
}
Students& Students::operator=(const Students& other) {
    if (this != &other) {
        this->students = other.students;
    }
    return *this;
}
void Students:: numSort() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.num < b.num;
        });
}
void Students:: groupSort() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.group == b.group) {
            QRegularExpression regex(R"(([A-Za-z]+)\s([A-Za-z]+))");
            QString famA, famB;
            auto matchA = regex.match(a.name);
            if (matchA.hasMatch())  famA = matchA.captured(2);
            else  famA = "";
            auto matchB = regex.match(b.name);
            if (matchB.hasMatch())  famB = matchB.captured(2);
            else  famB = "";

            return famA < famB;
        }
        return a.group < b.group;
        });
}

Stud1::Stud1(QString nameNew, QString addrNew, double priceNew)
    : Name(nameNew), Addr(addrNew), Price(priceNew) {
}

Stud1::Stud1()
    : Name(""), Addr(""), Price(0.0) {
}
QString Stud1::GetName() const { return Name; }
QString Stud1::GetAddr() const { return Addr; }
double Stud1::GetPrice() const { return Price; }
QTextStream& operator<<(QTextStream& out, const Stud1& stud) {
    out << stud.Name << " " << stud.Addr << " " << stud.Price;
    return out;
}

QTextStream& operator>>(QTextStream& in, Stud1& stud) {
    in >> stud.Name >> stud.Addr >> stud.Price;
    return in;
}

QDataStream& operator<<(QDataStream& out, const Stud1& stud) {
    out << stud.Name << stud.Addr << stud.Price;
    return out;
}

QDataStream& operator>>(QDataStream& in, Stud1& stud) {
    in >> stud.Name >> stud.Addr >> stud.Price;
    return in;
}
QString Stud1::GetPriceStr() const {
    return QString::number(Price);
}
Stud2::Stud2(QString nameNew)
    : Name(nameNew) {
}

Stud2::Stud2()
    : Name("") {
}
QString Stud2::GetName() const { return Name; }
QTextStream& operator<<(QTextStream& out, const Stud2& stud) {
    out << stud.Name;
    return out;
}

QTextStream& operator>>(QTextStream& in, Stud2& stud) {
    in >> stud.Name;
    return in;
}

QDataStream& operator<<(QDataStream& out, const Stud2& stud) {
    out << stud.Name;
    return out;
}

QDataStream& operator>>(QDataStream& in, Stud2& stud) {
    in >> stud.Name;
    return in;
}

Stud3::Stud3(QString nameNew, QString addrNew, double priceNew)
    : Name(nameNew), Addr(addrNew), Price(priceNew) {
}

QTextStream& operator<<(QTextStream& out, const Stud3& stud) {
    out << stud.Name << " " << stud.Addr << " " << stud.Price << " " << stud.ControlDate;
    return out;
}

/*QTextStream& operator>>(QTextStream& in, Stud3& stud) {
    in >> stud.Name >> stud.Addr >> stud.Price>> stud.ControlDate;
    return in;
}*/

QDataStream& operator<<(QDataStream& out, const Stud3& stud) {
    out << stud.Name << stud.Addr << stud.Price << stud.ControlDate;
    return out;
}

QDataStream& operator>>(QDataStream& in, Stud3& stud) {
    in >> stud.Name >> stud.Addr >> stud.Price>> stud.ControlDate;
    return in;
}

QString Stud3::GetName() const { return Name; }
QString Stud3::GetControlDate() const { return ControlDate; }
QString Stud3::GetAddr() const { return Addr; }
double Stud3::GetPrice() const { return Price; }
void Stud3::setName(const QString& name) {
    Name = name;
}
void Stud3::setAddr(const QString& addr) {
    Addr = addr;
}
void Stud3::setPrice(double pr) {
    Price = pr;
}
void Stud3::setControlDate(const QString& datestr) {
    ControlDate = datestr;
}
Stud3::Stud3() : Name(""), Addr(""), Price(0.0) {}
QString Stud3::GetPriceStr() const {
    return QString::number(Price);
}
STUD<Stud3> findDebtors(STUD<Stud1>& takenBooks, STUD<Stud2>& returnedBooks) {
    STUD<Stud3> debtors(takenBooks.getCount() - returnedBooks.getCount() + 1);
    int count = 0;
    for (int i = 0; i < takenBooks.getCount(); ++i) {
        bool isHere = false;
        for (int j = 0; j < returnedBooks.getCount(); ++j) {
            if (takenBooks[i].GetName() == returnedBooks[j].GetName()) isHere = true;
        }
        if (!isHere) {
            debtors[count].setName(takenBooks[i].GetName());
            debtors[count].setAddr(takenBooks[i].GetAddr());
            debtors[count].setPrice(takenBooks[i].GetPrice());
            QString datestr = "21 июня 2007г.";
            debtors[count].setControlDate(datestr);
            count++;
        }
    }
    return debtors;
}