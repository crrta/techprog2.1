#ifndef HEROES_H
#define HEROES_H

#include <string>
#include <fstream>
#include <iostream>

class Heroes {
protected:
    std::string name;
public:
    Heroes();
    Heroes(const std::string& name);
    Heroes(const Heroes& other);
    virtual ~Heroes();

    void setName(const std::string& name);
    std::string getName() const;

    virtual void input() = 0;
    virtual void print() const = 0;
    virtual void edit() = 0;
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual Heroes* clone() const = 0;
};

#endif#pragma once
