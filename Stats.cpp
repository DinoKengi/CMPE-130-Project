#include "Stats.h"

// Constructor
Stats::Stats(int health, int damage, int defense)
    : health(health), damage(damage), defense(defense) {}

// Getter functions
int Stats::getHealth() const {
    return health;
}

int Stats::getDamage() const {
    return damage;
}

int Stats::getDefense() const {
    return defense;
}

// Setter functions
void Stats::setHealth(int health) {
    this->health = health;
}

void Stats::setDamage(int damage) {
    this->damage = damage;
}

void Stats::setDefense(int defense) {
    this->defense = defense;
}

// Utility functions
void Stats::increaseHealth(int amount) {
    health += amount;
}

void Stats::increaseDamage(int amount) {
    damage += amount;
}

void Stats::increaseDefense(int amount) {
    defense += amount;
}
