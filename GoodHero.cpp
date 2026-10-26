#include "GoodHero.h"
#include "CustomException.h"

GoodHero::GoodHero() : Heroes(), weapon("Не указано"), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор по умолчанию класса GoodHero\n";
}

GoodHero::GoodHero(const std::string& name, const std::string& weapon, const std::string* skillsList, int count)
    : Heroes(name), weapon(weapon), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор с параметрами класса GoodHero (" << name << ")\n";
    setSkills(skillsList, count);
}

GoodHero::GoodHero(const GoodHero& other)
    : Heroes(other), weapon(other.weapon), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор копирования класса GoodHero (" << name << ")\n";
    setSkills(other.skills, other.skillsCount);
}

GoodHero::~GoodHero() {
    std::cout << " Вызван деструктор класса GoodHero (" << name << ")\n";
    clearSkills();
}

void GoodHero::clearSkills() {
    if (skills != nullptr) {
        delete[] skills;
        skills = nullptr;
    }
    skillsCount = 0;
}

GoodHero& GoodHero::operator=(const GoodHero& other) {
    std::cout << " Вызван оператор присваивания класса GoodHero\n";
    if (this != &other) {
        name = other.name;
        weapon = other.weapon;
        setSkills(other.skills, other.skillsCount);
    }
    return *this;
}

void GoodHero::setWeapon(const std::string& weapon) {
    this->weapon = weapon;
}

std::string GoodHero::getWeapon() const {
    return weapon;
}

void GoodHero::setSkills(const std::string* skillsList, int count) {
    if (count < 0) {
        throw CustomException("Ошибка: количество навыков не может быть отрицательным.");
    }
    clearSkills();
    skillsCount = count;
    if (count > 0 && skillsList != nullptr) {
        skills = new std::string[count];
        for (int i = 0; i < count; ++i) {
            skills[i] = skillsList[i];
        }
    }
}

int GoodHero::getSkillsCount() const {
    return skillsCount;
}

std::string GoodHero::getSkill(int index) const {
    if (index < 0 || index >= skillsCount) {
        throw CustomException("Ошибка: выход за границы массива навыков GoodHero.");
    }
    return skills[index];
}

void GoodHero::input() {
    std::cout << "Введите имя положительного героя: ";
    std::getline(std::cin, name);
    if (name.empty()) throw CustomException("Ошибка: имя героя не может быть пустым.");

    std::cout << "Введите тип оружия: ";
    std::getline(std::cin, weapon);

    std::cout << "Введите количество основных навыков: ";
    int count;
    if (!(std::cin >> count) || count < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw CustomException("Ошибка: некорректное количество навыков.");
    }
    std::cin.ignore(10000, '\n');

    clearSkills();
    skillsCount = count;
    if (skillsCount > 0) {
        skills = new std::string[skillsCount];
        for (int i = 0; i < skillsCount; ++i) {
            std::cout << "  Навык #" << (i + 1) << ": ";
            std::getline(std::cin, skills[i]);
        }
    }
}

void GoodHero::print() const {
    std::cout << "[Положительный герой]\n"
        << "  Имя: " << name << "\n"
        << "  Оружие: " << weapon << "\n"
        << "  Навыки (" << skillsCount << "): ";
    if (skillsCount == 0) {
        std::cout << "нет";
    }
    else {
        for (int i = 0; i < skillsCount; ++i) {
            std::cout << skills[i] << (i < skillsCount - 1 ? ", " : "");
        }
    }
    std::cout << "\n";
}

void GoodHero::edit() {
    std::cout << "Редактирование положительного героя (" << name << "):\n"
        << "1. Изменить имя\n"
        << "2. Изменить тип оружия\n"
        << "3. Изменить список навыков\n"
        << "Ваш выбор: ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw CustomException("Ошибка: введено не число.");
    }
    std::cin.ignore(10000, '\n');

    if (choice == 1) {
        std::cout << "Новое имя: ";
        std::getline(std::cin, name);
    }
    else if (choice == 2) {
        std::cout << "Новое оружие: ";
        std::getline(std::cin, weapon);
    }
    else if (choice == 3) {
        std::cout << "Введите новое количество навыков: ";
        int count;
        if (!(std::cin >> count) || count < 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw CustomException("Ошибка: некорректное количество навыков.");
        }
        std::cin.ignore(10000, '\n');
        clearSkills();
        skillsCount = count;
        if (skillsCount > 0) {
            skills = new std::string[skillsCount];
            for (int i = 0; i < skillsCount; ++i) {
                std::cout << "  Навык #" << (i + 1) << ": ";
                std::getline(std::cin, skills[i]);
            }
        }
    }
    else {
        throw CustomException("Ошибка: неверный пункт меню редактирования.");
    }
}

void GoodHero::save(std::ofstream& out) const {
    out << 1 << "\n"
        << name << "\n"
        << weapon << "\n"
        << skillsCount << "\n";
    for (int i = 0; i < skillsCount; ++i) {
        out << skills[i] << "\n";
    }
}

void GoodHero::load(std::ifstream& in) {
    std::getline(in, name);
    std::getline(in, weapon);
    int count = 0;
    in >> count;
    in.ignore(10000, '\n');
    if (count < 0) throw CustomException("Ошибка чтения файла: отрицательное число навыков.");
    clearSkills();
    skillsCount = count;
    if (skillsCount > 0) {
        skills = new std::string[skillsCount];
        for (int i = 0; i < skillsCount; ++i) {
            std::getline(in, skills[i]);
        }
    }
}

Heroes* GoodHero::clone() const {
    return new GoodHero(*this);
}