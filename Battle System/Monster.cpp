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

}

void Goblin::attack() {

}

void Slime::attack() {

}

void Bandit::attack() {

}

void Ghost::attack() {

}

void Dragon::attack() {

}
