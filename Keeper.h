#ifndef KEEPER_H
#define KEEPER_H

#include "Heroes.h"
#include <string>

class Keeper {
private:
    Heroes** data;
    int size;

    void clear();
public:
    Keeper();
    Keeper(int initialSize);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Heroes* operator[](int index) const;

    int getSize() const;

    void add(Heroes* item);
    void remove(int index);
    void printAll() const;
    void edit(int index);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif#pragma once
