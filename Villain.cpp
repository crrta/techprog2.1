#include "Villain.h"
#include "CustomException.h"

Villain::Villain()
    : Heroes(), weapon("Не указано"), crime("Не указано"), habitat("Не указано"), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор по умолчанию класса Villain\n";
}

Villain::Villain(const std::string& name, const std::string& weapon, const std::string& crime,
    const std::string& habitat, const std::string* skillsList, int count)
    : Heroes(name), weapon(weapon), crime(crime), habitat(habitat), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор с параметрами класса Villain (" << name << ")\n";
    setSkills(skillsList, count);
}

Villain::Villain(const Villain& other)
    : Heroes(other), weapon(other.weapon), crime(other.crime), habitat(other.habitat), skills(nullptr), skillsCount(0) {
    std::cout << " Вызван конструктор копирования класса Villain (" << name << ")\n";
    setSkills(other.skills, other.skillsCount);
}

Villain::~Villain() {
    std::cout << " Вызван деструктор класса Villain (" << name << ")\n";
    clearSkills();
}

void Villain::clearSkills() {
    if (skills != nullptr) {
        delete[] skills;
        skills = nullptr;
    }
    skillsCount = 0;
}

Villain& Villain::operator=(const Villain& other) {
    std::cout << " Вызван оператор присваивания класса Villain\n";
    if (this != &other) {
        name = other.name;
        weapon = other.weapon;
        crime = other.crime;
        habitat = other.habitat;
        setSkills(other.skills, other.skillsCount);
    }
    return *this;
}

void Villain::setWeapon(const std::string& weapon) { this->weapon = weapon; }
std::string Villain::getWeapon() const { return weapon; }

void Villain::setCrime(const std::string& crime) { this->crime = crime; }
std::string Villain::getCrime() const { return crime; }

void Villain::setHabitat(const std::string& habitat) { this->habitat = habitat; }
std::string Villain::getHabitat() const { return habitat; }

void Villain::setSkills(const std::string* skillsList, int count) {
    if (count < 0) throw CustomException("Ошибка: количество навыков не может быть отрицательным.");
    clearSkills();
    skillsCount = count;
    if (count > 0 && skillsList != nullptr) {
        skills = new std::string[count];
        for (int i = 0; i < count; ++i) {
            skills[i] = skillsList[i];
        }
    }
}

int Villain::getSkillsCount() const { return skillsCount; }

std::string Villain::getSkill(int index) const {
    if (index < 0 || index >= skillsCount) {
        throw CustomException("Ошибка: выход за границы массива навыков Villain.");
    }
    return skills[index];
}

void Villain::input() {
    std::cout << "Введите имя злодея: ";
    std::getline(std::cin, name);
    if (name.empty()) throw CustomException("Ошибка: имя злодея не может быть пустым.");

    std::cout << "Введите тип оружия: ";
    std::getline(std::cin, weapon);

    std::cout << "Введите совершенное злодеяние: ";
    std::getline(std::cin, crime);

    std::cout << "Введите место обитания: ";
    std::getline(std::cin, habitat);

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

void Villain::print() const {
    std::cout << "[Злодей]\n"
        << "  Имя: " << name << "\n"
        << "  Оружие: " << weapon << "\n"
        << "  Злодеяние: " << crime << "\n"
        << "  Место обитания: " << habitat << "\n"
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

void Villain::edit() {
    std::cout << "Редактирование злодея (" << name << "):\n"
        << "1. Изменить имя\n"
        << "2. Изменить оружие\n"
        << "3. Изменить злодеяние\n"
        << "4. Изменить место обитания\n"
        << "5. Изменить список навыков\n"
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
        std::cout << "Новое злодеяние: ";
        std::getline(std::cin, crime);
    }
    else if (choice == 4) {
        std::cout << "Новое место обитания: ";
        std::getline(std::cin, habitat);
    }
    else if (choice == 5) {
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

void Villain::save(std::ofstream& out) const {
    out << 2 << "\n"
        << name << "\n"
        << weapon << "\n"
        << crime << "\n"
        << habitat << "\n"
        << skillsCount << "\n";
    for (int i = 0; i < skillsCount; ++i) {
        out << skills[i] << "\n";
    }
}

void Villain::load(std::ifstream& in) {
    std::getline(in, name);
    std::getline(in, weapon);
    std::getline(in, crime);
    std::getline(in, habitat);
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

Heroes* Villain::clone() const {
    return new Villain(*this);
}