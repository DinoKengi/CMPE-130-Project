#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Stats.h"

class Player : public Stats {
public:
    Player(const std::string& name, int health, int damage, int defense, int speed);

    std::string getName() const;

protected:
    std::string name;
};

// Specific player classes
class Wizard : public Player {
public: 
    Wizard() : Player("Wizard", 60, 26, 5, 10) {} // Speed: 10
};

class Knight : public Player {
public:
    Knight() : Player("Knight", 100, 30, 10, 8) {} // Speed: 8
};

class Archer : public Player {
public:
    Archer() : Player("Archer", 40, 50, 2, 15) {} // Speed: 15
};

#endif
