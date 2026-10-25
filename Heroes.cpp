#include "Heroes.h"

Heroes::Heroes() : name("Безымянный") {
    std::cout << " Вызван конструктор по умолчанию класса Heroes\n";
}

Heroes::Heroes(const std::string& name) : name(name) {
    std::cout << " Вызван конструктор с параметрами класса Heroes (" << name << ")\n";
}

Heroes::Heroes(const Heroes& other) : name(other.name) {
    std::cout << " Вызван конструктор копирования класса Heroes (" << name << ")\n";
}

Heroes::~Heroes() {
    std::cout << " Вызван деструктор класса Heroes (" << name << ")\n";
}

void Heroes::setName(const std::string& name) {
    this->name = name;
}

std::string Heroes::getName() const {
    return name;
}