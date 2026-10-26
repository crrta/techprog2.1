#ifndef VILLAIN_H
#define VILLAIN_H

#include "Heroes.h"

class Villain : public Heroes {
private:
    std::string weapon;
    std::string crime;
    std::string habitat;
    std::string* skills;
    int skillsCount;

    void clearSkills();
public:
    Villain();
    Villain(const std::string& name, const std::string& weapon, const std::string& crime,
        const std::string& habitat, const std::string* skillsList, int count);
    Villain(const Villain& other);
    ~Villain() override;

    Villain& operator=(const Villain& other);

    void setWeapon(const std::string& weapon);
    std::string getWeapon() const;

    void setCrime(const std::string& crime);
    std::string getCrime() const;

    void setHabitat(const std::string& habitat);
    std::string getHabitat() const;

    void setSkills(const std::string* skillsList, int count);
    int getSkillsCount() const;
    std::string getSkill(int index) const;

    void input() override;
    void print() const override;
    void edit() override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    Heroes* clone() const override;
};

#endif#pragma once
