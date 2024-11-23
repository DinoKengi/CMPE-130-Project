#ifndef MONSTERS_H
#define MONSTERS_H

#include "Stats.h"
#include <string>

class Monster : public Stats {
public:
    Monster(const std::string& name, int health, int damage, int defense, int speed);

    virtual void attack() = 0;  // each monster has its own attack behavior
    bool isAlive() const;       // checks if the monster is alive
    std::string getName() const;

protected:
    std::string name;
};

// Specific monster classes with speed attributes
class Ogre : public Monster {
public:
    Ogre() : Monster("Ogre", 100, 20, 5, 8) {} // Speed: 8
    void attack() override;
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 40, 10, 2, 12) {} // Speed: 12
    void attack() override;
};

class Slime : public Monster {
public:
    Slime() : Monster("Slime", 30, 5, 1, 6) {} // Speed: 6
    void attack() override;
};

class Bandit : public Monster {
public:
    Bandit() : Monster("Bandit", 70, 15, 5, 14) {} // Speed: 14
    void attack() override;
};

class Ghost : public Monster {
public:
    Ghost() : Monster("Ghost", 50, 15, 2, 10) {} // Speed: 10
    void attack() override;
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 2000, 60, 30, 5) {} // Speed: 5
    void attack() override;
};

#endif
