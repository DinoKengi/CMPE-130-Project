#ifndef MONSTERS_H
#define MONSTERS_H

#include "Stats.h"
#include <string>

class Monster : public Stats {
public:
    Monster(const std::string& name, int health, int damage, int defense);

    virtual void attack() = 0;  // each monster has its own attack behavior
    bool isAlive() const;  // check if monster's alive
    std::string getName() const;  

protected:
    std::string name;
};

class Ogre : public Monster {
public:
    Ogre() : Monster("Ogre", 100, 20, 5) {}
    void attack() override;
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 40, 10, 2) {}
    void attack() override;
};

class Slime : public Monster {
public:
    Slime() : Monster("Slime", 30, 5, 1) {}
    void attack() override;
};

class Bandit : public Monster {
public:
    Bandit() : Monster("Bandit", 70, 15, 5) {}
    void attack() override;
};

class Ghost : public Monster {
public:
    Ghost() : Monster("Ghost", 50, 15, 2) {}
    void attack() override;
};

// idea: dragon is final boss
class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 2000, 60, 30) {}
    void attack() override;
};

#endif 
