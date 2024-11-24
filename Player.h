#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Stats.h"
#include "Buff.h"

class Player {
public:
    Player(const std::string& name, int health, int damage, int defense, int speed);

    // Getter functions
    std::string getName() const;
    int getHealth() const;
    int getDamage() const;
    int getDefense() const;
    int getSpeed() const;
    bool isAlive() const;

    // Setter functions
    void setHealth(int health);
    void setDamage(int damage);
    void setDefense(int defense);
    void setSpeed(int speed);

    // Buff-related functions
    void applyBuff(const Buff& buff);
    void increaseDamage(int amount);
    
    void takeDamage(int damage);


    virtual std::string getClassType() const = 0; // Pure virtual method

protected:
    std::string name;
    Stats stats; // Composition: Player has Stats
};

// Wizard class
class Wizard : public Player {
public:
    Wizard(const std::string& name)
        : Player(name, 80, 15, 3, 10) {} // Default stats for Wizard

    std::string getClassType() const override {
        return "Wizard";
    }
};

// Knight class
class Knight : public Player {
public:
    Knight(const std::string& name)
        : Player(name, 120, 10, 10, 10) {} // Default stats for Knight

    std::string getClassType() const override {
        return "Knight";
    }
};

// Archer class
class Archer : public Player {
public:
    Archer(const std::string& name)
        : Player(name, 100, 12, 5, 10) {} // Default stats for Archer

    std::string getClassType() const override {
        return "Archer";
    }
};

#endif
