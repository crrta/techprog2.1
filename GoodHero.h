#ifndef GOOD_HERO_H
#define GOOD_HERO_H

#include "Heroes.h"

class GoodHero : public Heroes {
private:
    std::string weapon;
    std::string* skills;
    int skillsCount;

    void clearSkills();
public:
    GoodHero();
    GoodHero(const std::string& name, const std::string& weapon, const std::string* skillsList, int count);
    GoodHero(const GoodHero& other);
    ~GoodHero() override;

    GoodHero& operator=(const GoodHero& other);

    void setWeapon(const std::string& weapon);
    std::string getWeapon() const;

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
