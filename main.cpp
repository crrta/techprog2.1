#include <iostream>
#include <string>
#include "Keeper.h"
#include "GoodHero.h"
#include "Villain.h"
#include "Monster.h"
#include "CustomException.h"

void printMenu() {
    std::cout << "\nМеню\n"
        << "1. Добавить положительного героя\n"
        << "2. Добавить злодея\n"
        << "3. Добавить монстра\n"
        << "4. Вывести все объекты на экран\n"
        << "5. Редактировать объект\n"
        << "6. Удалить объект\n"
        << "7. Сохранить данные в файл\n"
        << "8. Загрузить данные из файла\n"
        << "9. Продемонстрировать конструктор копирования и операторы\n"
        << "0. Выход\n"
        << "Выберите действие: ";
}

int readInt() {
    int value;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw CustomException("Ошибка ввода: ожидалось целое число.");
    }
    std::cin.ignore(10000, '\n');
    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Keeper keeper;
    bool running = true;

    while (running) {
        try {
            printMenu();
            int choice = readInt();

            switch (choice) {
            case 1: {
                Heroes* hero = new GoodHero();
                try {
                    hero->input();
                    keeper.add(hero);
                }
                catch (...) {
                    delete hero;
                    throw;
                }
                break;
            }
            case 2: {
                Heroes* villain = new Villain();
                try {
                    villain->input();
                    keeper.add(villain);
                }
                catch (...) {
                    delete villain;
                    throw;
                }
                break;
            }
            case 3: {
                Heroes* monster = new Monster();
                try {
                    monster->input();
                    keeper.add(monster);
                }
                catch (...) {
                    delete monster;
                    throw;
                }
                break;
            }
            case 4: {
                keeper.printAll();
                break;
            }
            case 5: {
                std::cout << "Введите номер записи для редактирования (1-" << keeper.getSize() << "): ";
                int idx = readInt();
                keeper.edit(idx - 1);
                break;
            }
            case 6: {
                std::cout << "Введите номер записи для удаления (1-" << keeper.getSize() << "): ";
                int idx = readInt();
                keeper.remove(idx - 1);
                std::cout << "Запись удалена.\n";
                break;
            }
            case 7: {
                std::cout << "Введите имя файла для сохранения: ";
                std::string filename;
                std::getline(std::cin, filename);
                keeper.saveToFile(filename);
                break;
            }
            case 8: {
                std::cout << "Введите имя файла для загрузки: ";
                std::string filename;
                std::getline(std::cin, filename);
                keeper.loadFromFile(filename);
                break;
            }
            case 9: {
                std::cout << "Демонстрация конструкторов с параметрами, копирования и оператора []\n";
                std::cout << "Введите имя демонстрационного монстра: ";
                std::string mName, mApp;
                std::getline(std::cin, mName);
                std::cout << "Введите внешний вид демонстрационного монстра: ";
                std::getline(std::cin, mApp);

                Monster m1(mName, mApp);
                Monster m2(m1); // Конструктор копирования
                Monster m3;
                m3 = m2;        // Оператор присваивания

                std::cout << "Проверка копии контейнера Keeper:\n";
                Keeper keeperCopy(keeper);
                if (keeperCopy.getSize() > 0) {
                    std::cout << "Обращение к первому элементу копии через перегруженный оператор keeperCopy[0]:\n";
                    keeperCopy[0]->print();
                }
                std::cout << "Завершение демонстрации (вызов деструкторов локальных объектов)\n";
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default:
                std::cout << "Неизвестная команда. Повторите ввод.\n";
                break;
            }
        }
        catch (const CustomException& ex) {
            std::cout << "\n[искл] " << ex.getMessage() << "\n";
        }
    }

    return 0;
}