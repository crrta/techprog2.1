#ifndef MONSTER_H
#define MONSTER_H

#include "Heroes.h"

class Monster : public Heroes {
private:
    std::string appearance;
public:
    Monster();
    Monster(const std::string& name, const std::string& appearance);
    Monster(const Monster& other);
    ~Monster() override;

    Monster& operator=(const Monster& other);

    void setAppearance(const std::string& appearance);
    std::string getAppearance() const;

    void input() override;
    void print() const override;
    void edit() override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    Heroes* clone() const override;
};

#endif#pragma once
