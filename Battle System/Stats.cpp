#include "Stats.h"

Stats::Stats(int health, int damage, int defense, int speed)
    : health(health), damage(damage), defense(defense), speed(speed) {}

int Stats::getHealth() const {
    return health;
}

int Stats::getDamage() const {
    return damage;
}

int Stats::getDefense() const {
    return defense;
}

int Stats::getSpeed() const {
    return speed;
}

void Stats::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}
