#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name, int health, int damage, int defense);

private:


};

class Wizard : public Player {
    public: 
        Wizard() : Player("Wizard", 60, 26, 5) {}
};

class Knight : public Player {
    public:
        Knight() : Player("Knight", 100, 30, 10) {}
};

class Archer : public Player {
    public:
        Archer() : Player("Archer", 40, 50, 2) {}
};
#endif
