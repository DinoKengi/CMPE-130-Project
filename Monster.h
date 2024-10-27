#ifndef MONSTERS_H
#define MONSTERS_H

#include "Stats.h"
#include <string>

class Monster : public Stats {
public:
    Monster(const std::string& name, int health, int damage, int defense);

    virtual void attackPlayer() = 0;  // Each monster has its own attack behavior
    bool isAlive() const;  // Check if the monster is still alive
    std::string getName() const;  

protected:
    std::string name;
};

class Ogre : public Monster {
public:
    Ogre();
    void attackPlayer() override;
};

class Goblin : public Monster {
public:
    Goblin();
    void attackPlayer() override;
};

class Slime : public Monster {
public:
    Slime();
    void attackPlayer() override;
};

class Bandit : public Monster {
public:
    Bandit();
    void attackPlayer() override;
};

class Ghost : public Monster {
public:
    Ghost();
    void attackPlayer() override;
};

// idea: dragon is final boss
class Dragon : public Monster {
public:
    Dragon();
    void attackPlayer() override;
};

#endif 
