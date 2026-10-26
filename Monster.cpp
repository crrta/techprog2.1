#include "Monster.h"
#include "CustomException.h"

Monster::Monster() : Heroes(), appearance("Неизвестно") {
    std::cout << " Вызван конструктор по умолчанию класса Monster\n";
}

Monster::Monster(const std::string& name, const std::string& appearance)
    : Heroes(name), appearance(appearance) {
    std::cout << " Вызван конструктор с параметрами класса Monster (" << name << ")\n";
}

Monster::Monster(const Monster& other)
    : Heroes(other), appearance(other.appearance) {
    std::cout << " Вызван конструктор копирования класса Monster (" << name << ")\n";
}

Monster::~Monster() {
    std::cout << " Вызван деструктор класса Monster (" << name << ")\n";
}

Monster& Monster::operator=(const Monster& other) {
    std::cout << " Вызван оператор присваивания класса Monster\n";
    if (this != &other) {
        name = other.name;
        appearance = other.appearance;
    }
    return *this;
}

void Monster::setAppearance(const std::string& appearance) {
    this->appearance = appearance;
}

std::string Monster::getAppearance() const {
    return appearance;
}

void Monster::input() {
    std::cout << "Введите наименование монстра: ";
    std::getline(std::cin, name);
    if (name.empty()) throw CustomException("Ошибка: наименование монстра не может быть пустым.");

    std::cout << "Введите описание внешнего вида: ";
    std::getline(std::cin, appearance);
}

void Monster::print() const {
    std::cout << "[Монстр]\n"
        << "  Наименование: " << name << "\n"
        << "  Внешний вид: " << appearance << "\n";
}

void Monster::edit() {
    std::cout << "Редактирование монстра (" << name << "):\n"
        << "1. Изменить наименование\n"
        << "2. Изменить описание внешнего вида\n"
        << "Ваш выбор: ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw CustomException("Ошибка: введено не число.");
    }
    std::cin.ignore(10000, '\n');

    if (choice == 1) {
        std::cout << "Новое наименование: ";
        std::getline(std::cin, name);
    }
    else if (choice == 2) {
        std::cout << "Новое описание внешнего вида: ";
        std::getline(std::cin, appearance);
    }
    else {
        throw CustomException("Ошибка: неверный пункт меню редактирования.");
    }
}

void Monster::save(std::ofstream& out) const {
    out << 3 << "\n"
        << name << "\n"
        << appearance << "\n";
}

void Monster::load(std::ifstream& in) {
    std::getline(in, name);
    std::getline(in, appearance);
}

Heroes* Monster::clone() const {
    return new Monster(*this);
}