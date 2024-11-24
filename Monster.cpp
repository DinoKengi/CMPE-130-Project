#include "Monster.h"
#include <iostream>

Monster::Monster(const std::string& name, int health, int damage, int defense, int speed)
    : name(name), stats(health, damage, defense, speed) {}

bool Monster::isAlive() const {
    return stats.getHealth() > 0;
}

std::string Monster::getName() const {
    return name;
}

void Monster::takeDamage(int damage) {
    stats.takeDamage(damage);
}

int Monster::getDamage() const {
    return stats.getDamage();
}

int Monster::getHealth() const {
    return stats.getHealth(); // Assuming `stats` is an instance of `Stats` in `Monster`
}


int Monster::getSpeed() const {
    return stats.getSpeed();
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
