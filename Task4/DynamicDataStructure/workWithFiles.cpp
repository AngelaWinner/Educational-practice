#include "workWithFiles.h" 
using namespace std;
Element::Element(int value) : data(value), next(nullptr), prev(nullptr) {}
List::List() : head(nullptr), tail(nullptr) {}
List::~List() {
    clear();
}
bool List::empty() {
    return (head == nullptr);
}
/*void List::clear() {
    Element* temp = head;
    while (head) {
        head = head->next;
    }
    delete temp;
}*/
void List::clear() {
    Element* current = head;
    while (current != nullptr) {
        Element* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}
void List::push_front(int value) {
    Element* newEl = new Element(value);
    if (!head) { //if there is no head
        head = tail = newEl;
    }
    else {
        head->prev = newEl;
        newEl->next = head;
        head = newEl;
    }
}
void List::push_back(int value) {
    Element* newEl = new Element(value);
    if (!tail) {
        head = tail = newEl;
    }
    else {
        tail->next = newEl;
        newEl->prev = tail;
        tail = newEl;
    }
}
void List::pop_front() {
    if (!head) return;
    Element* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
}
void List::pop_back() {
    if (!tail) return;
    Element* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
}
void List::readFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }
    QTextStream in(&file);
    while (!file.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(QRegularExpression("[\\s]+"), Qt::SkipEmptyParts);
        for (const QString& el : words)
            push_back(el.toInt());  // Append the words from the current line to the list
    }
    file.close();
}
void List::print(QTextStream& out) {
    Element* newEl = head;
    while (newEl) {
        out << newEl->data << " ";
        newEl = newEl->next;
    }
}
QString List::print() {
    Element* newEl = head;
    QString str = "";
    while (newEl) {
        str += QString::number(newEl->data) + " ";
        newEl = newEl->next;
    }
    return str.trimmed();
}
void List::change() {
    Element* newEl = head;
    int add = 0;
    while (newEl) {
        if (newEl->data % 2 == 0) {
            add = newEl->data;
            break;
        }
        newEl = newEl->next;
    }
    newEl = head;
    while (newEl) {
        newEl->data += add;
        newEl = newEl->next;
    }
}
QString List::join(const QString& separator) {
    QString result;
    Element* current = head;
    while (current) {
        result += QString::number(current->data);
        if (current->next) {
            result += separator;
        }
        current = current->next;
    }
    return result;
}
int List::size() const {
    int count = 0;
    Element* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}