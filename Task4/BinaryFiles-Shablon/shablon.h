#ifndef SHABLON_H
#define SHABLON_H
#pragma once
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QRegularExpression>
#include <QDebug>
using namespace Qt;
class Students {
public:
    struct Student {
        int num;
        QString name;
        int group;
        double grade;
        Student() : num(0), name(""), group(0), grade(0) {}
        Student(int numNew, const QString& nameNew, int groupNew, double gradeNew) : num(numNew), name(nameNew), group(groupNew), grade(gradeNew) {}
        void printOne(QTextStream& out) const {
            out << "Num: " << num << ", Name: " << name << ", Group: " << group << ", Grade: " << grade << endl;
        }
        bool operator==(const Student& someone) const {
            return (num == someone.num) &&
                (name == someone.name) &&
                (group == someone.group) &&
                (grade == someone.grade);
        }
        friend QDataStream& operator<<(QDataStream& out, const Student& student) {
            out << student.num << student.name << student.group << double(student.grade);
            return out;
        }
        friend QDataStream& operator>>(QDataStream& in, Student& student) {
            int num;
            double grade;
            in >> num >> student.name >> student.group >> grade;
            student.num = num;
            student.grade = grade;
            return in;
        }
        QString GetName() {
            return name;
        }
        QString GetNum() {
            return QString::number(num);
        }
        QString GetGroup() {
            return QString::number(group);
        }
        QString GetGrade() {
            return QString::number(grade);
        }
    };
private:
    QVector<Student> students;
public:
    int count() const;
    void readFromFile(const QString& fileName);
    void readFromFileBin(const QString& fileName);
    void printAll(QTextStream& out) const;
    Students studUnion(const Students& stud1, QTextStream& out);
    Students studPeresechenie(const Students& stud2, QTextStream& out);
    Students studDiffer(const Students& stud2, QTextStream& out);
    QVector<Student> GetStudents() const;
    Students& operator=(const Students& other);
    void numSort();
    void groupSort();
};

template <typename T> class STUD {
private:
    int count;
    T* M;
public:
    STUD() {
        count = 0;
        M = nullptr;
    }
    STUD(int count) {
        this->count = count;
        M = new T[count];
    }
    STUD(STUD<T>& stud) {
        this->count = stud.count;
        M = new T[count];
        for (int i = 0; i < count; ++i) {
            M[i] = stud.M[i];
        }
    }
    ~STUD() {
        delete[] M;
    }
    int getCount() { return count; }
    STUD& operator=(STUD other) {
        if (this != other) {
            delete[] M;
            this->count = other.count;
            if (count > 0) {
                M = new T[count];
                for (int i = 0; i < count; ++i) {
                    M[i] = other.M[i];
                }
            }
            else M = nullptr;
        }
        return *this;
    }
    T& operator[](int i) { return M[i]; }
    void ReadFromBinFile(const QString& filename)
    {
        QTextStream out(stdout);
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            out << "Ошибка открытия файла \"" << filename << "\"\n"; out.flush();
            exit(1);
        }
        QDataStream in(&file);
        QList<T> list;
        while (!in.atEnd())
        {
            T stutudent;
            in >> stutudent;
            list.push_back(stutudent);
        }
        file.close();

        delete[] M;
        count = list.size();
        M = new T[count];
        for (int i = 0; i < count; ++i) {
            M[i] = list[i];
        }
    }
    void ReadFromTextFile(const QString& filename) //Чтение из файла
    {
        QTextStream out(stdout);
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            out << "Ошибка открытия файла \"" << filename << "\"\n"; out.flush();
            exit(1);
        }
        QTextStream in(&file);
        QList<T> list;
        while (!in.atEnd())
        {
            T student;
            in >> student;
            list.push_back(student);
        }
        file.close();

        delete[] M;
        count = list.size();
        M = new T[count];
        for (int i = 0; i < count; ++i) {
            M[i] = list[i];
        }
    }
    void WriteToTextFile(QTextStream &fout) //Запись в файл
    {
        for (int i = 0; i < count; ++i) {
            fout << M[i] << '\n';
        }
    }
    friend QTextStream& operator<<(QTextStream& out, STUD<T>& stud) {
        for (int i = 0; i < stud.count; ++i) {
            out << stud.M[i] << '\n'; out.flush();
        }
        return out;
    }
    T* GetM() const {
        return M;
    }
};

struct Stud1 { //"Читатели, взявшие книги"
    QString Name;
    QString Addr;
    double Price;
    Stud1(QString nameNew, QString addrNew, double priceNew);
    Stud1();
    friend QTextStream& operator<<(QTextStream& out, const Stud1& stud);
    friend QTextStream& operator>>(QTextStream& in, Stud1& stud);
    friend QDataStream& operator>>(QDataStream& in, Stud1& stud);
    friend QDataStream& operator<<(QDataStream& out, const Stud1& stud);
    QString GetName() const;
    QString GetAddr() const;
    double GetPrice() const;
    QString GetPriceStr() const;
    //void setPrice(double newPrice);
};
//«Читатели, вернувшие все книги»
struct Stud2 {
    QString Name;

    Stud2(QString nameNew);
    Stud2();
    QString GetName() const;
    friend QTextStream& operator<<(QTextStream& out, const Stud2& stud);
    friend QTextStream& operator>>(QTextStream& in, Stud2& stud);
    friend QDataStream& operator<<(QDataStream& out, const Stud2& stud);
    friend QDataStream& operator>>(QDataStream& in, Stud2& stud);
};

//«Студенты, не сдавшие книги»
struct Stud3 {
    QString Name;
    QString Addr;
    QString ControlDate;
    double Price;
    Stud3();
    Stud3(QString nameNew, QString addrNew, double priceNew);

    friend QTextStream& operator<<(QTextStream& out, const Stud3& stud);
    friend QTextStream& operator>>(QTextStream& in, Stud3& stud);
    friend QDataStream& operator<<(QDataStream& out, const Stud3& stud);
    friend QDataStream& operator>>(QDataStream& in, Stud3& stud);
    QString GetName() const;
    QString GetControlDate() const;
    QString GetAddr() const;
    double GetPrice() const;
    QString GetPriceStr() const;
    void setName(const QString& name);
    void setAddr(const QString& addr);
    void setPrice(double pr);
    void setControlDate(const QString& datestr);
};

STUD<Stud3> findDebtors(STUD<Stud1>& takenBooks, STUD<Stud2>& returnedBooks);
#endif // SHABLON_H