#ifndef MONSTERS_H
#define MONSTERS_H

#include "Stats.h"
#include <string>

class Monster {
public:
    Monster(const std::string& name, int health, int damage, int defense, int speed);

    virtual void attack() = 0;  // each monster has its own attack behavior
    bool isAlive() const;  // check if monster's alive
    std::string getName() const;  
    void takeDamage(int damage);
    int getHealth() const;
    int getSpeed() const;
    int getDamage() const;

protected:
    Stats stats;
    std::string name;
};

class Ogre : public Monster {
public:
    Ogre() : Monster("Ogre", 100, 20, 5, 2) {}
    void attack() override;
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 40, 10, 2, 2) {}
    void attack() override;
};

class Slime : public Monster {
public:
    Slime() : Monster("Slime", 30, 5, 1, 2) {}
    void attack() override;
};

class Bandit : public Monster {
public:
    Bandit() : Monster("Bandit", 70, 15, 5, 2) {}
    void attack() override;
};

class Ghost : public Monster {
public:
    Ghost() : Monster("Ghost", 50, 15, 2, 2) {}
    void attack() override;
};

// idea: dragon is final boss
class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 2000, 60, 30, 10) {}
    void attack() override;
};

#endif 
