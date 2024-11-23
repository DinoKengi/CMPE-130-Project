#include "Monster.h"

Monster::Monster(const std::string& name, int health, int damage, int defense, int speed)
    : Stats(health, damage, defense, speed), name(name) {}

bool Monster::isAlive() const {
    return health > 0;
}

std::string Monster::getName() const {
    return name;
}

void Ogre::attack() {
    // Example attack logic
}

void Goblin::attack() {
    // Example attack logic
}

void Slime::attack() {
    // Example attack logic
}

void Bandit::attack() {
    // Example attack logic
}

void Ghost::attack() {
    // Example attack logic
}

void Dragon::attack() {
    // Example attack logic
}
