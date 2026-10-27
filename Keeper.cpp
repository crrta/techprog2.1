#include "Keeper.h"
#include "GoodHero.h"
#include "Villain.h"
#include "Monster.h"
#include "CustomException.h"
#include <iostream>
#include <fstream>

Keeper::Keeper() : data(nullptr), size(0) {
    std::cout << " Вызван конструктор по умолчанию класса Keeper\n";
}

Keeper::Keeper(int initialSize) : data(nullptr), size(0) {
    std::cout << " Вызван конструктор с параметрами класса Keeper\n";
    if (initialSize < 0) {
        throw CustomException("Ошибка: размер контейнера не может быть отрицательным.");
    }
    if (initialSize > 0) {
        data = new Heroes * [initialSize];
        size = initialSize;
        for (int i = 0; i < size; ++i) {
            data[i] = new Monster();
        }
    }
}

Keeper::Keeper(const Keeper& other) : data(nullptr), size(0) {
    std::cout << " Вызван конструктор копирования класса Keeper\n";
    if (other.size > 0) {
        size = other.size;
        data = new Heroes * [size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i]->clone();
        }
    }
}

Keeper::~Keeper() {
    std::cout << " Вызван деструктор класса Keeper\n";
    clear();
}

void Keeper::clear() {
    if (data != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        data = nullptr;
    }
    size = 0;
}

Keeper& Keeper::operator=(const Keeper& other) {
    std::cout << " Вызван оператор присваивания класса Keeper\n";
    if (this != &other) {
        clear();
        if (other.size > 0) {
            size = other.size;
            data = new Heroes * [size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i]->clone();
            }
        }
    }
    return *this;
}

Heroes* Keeper::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw CustomException("Ошибка: индекс выходит за пределы контейнера Keeper.");
    }
    return data[index];
}

int Keeper::getSize() const {
    return size;
}

void Keeper::add(Heroes* item) {
    if (item == nullptr) {
        throw CustomException("Ошибка: попытка добавить пустой указатель в Keeper.");
    }
    Heroes** newData = new Heroes * [size + 1];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    newData[size] = item;
    delete[] data;
    data = newData;
    ++size;
}

void Keeper::remove(int index) {
    if (size == 0) {
        throw CustomException("Ошибка: контейнер пуст, удаление невозможно.");
    }
    if (index < 0 || index >= size) {
        throw CustomException("Ошибка: неверный индекс для удаления.");
    }
    delete data[index];
    if (size == 1) {
        delete[] data;
        data = nullptr;
        size = 0;
        return;
    }
    Heroes** newData = new Heroes * [size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != index) {
            newData[j++] = data[i];
        }
    }
    delete[] data;
    data = newData;
    --size;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Контейнер пуст.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << "Запись #" << (i + 1) << ":\n";
        data[i]->print();
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw CustomException("Ошибка: неверный индекс для редактирования.");
    }
    data[index]->edit();
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw CustomException("Ошибка: не удалось открыть файл для записи (" + filename + ").");
    }
    out << size << "\n";
    for (int i = 0; i < size; ++i) {
        data[i]->save(out);
    }
    out.close();
    std::cout << "Данные успешно сохранены в файл " << filename << ".\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw CustomException("Ошибка: не удалось открыть файл для чтения (" + filename + ").");
    }
    int newSize = 0;
    if (!(in >> newSize) || newSize < 0) {
        throw CustomException("Ошибка: поврежден заголовок файла или неверный формат данных.");
    }
    in.ignore(10000, '\n');

    clear();
    for (int i = 0; i < newSize; ++i) {
        int type = 0;
        if (!(in >> type)) {
            throw CustomException("Ошибка чтения типа объекта из файла.");
        }
        in.ignore(10000, '\n');

        Heroes* item = nullptr;
        if (type == 1) {
            item = new GoodHero();
        }
        else if (type == 2) {
            item = new Villain();
        }
        else if (type == 3) {
            item = new Monster();
        }
        else {
            throw CustomException("Ошибка: неизвестный код типа объекта в файле.");
        }

        try {
            item->load(in);
            add(item);
        }
        catch (...) {
            delete item;
            throw;
        }
    }
    in.close();
    std::cout << "Данные успешно загружены из файла " << filename << ". Загружено объектов: " << size << ".\n";
}