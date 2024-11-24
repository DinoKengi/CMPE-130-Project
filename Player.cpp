#include "Player.h"
#include <iostream>

// Constructor
Player::Player(const std::string& name, int health, int damage, int defense, int speed)
    : name(name), stats(health, damage, defense, speed) {}

// Getter functions
std::string Player::getName() const {
    return name;
}

int Player::getHealth() const {
    return stats.getHealth();
}

bool Player::isAlive() const {
    return getHealth() > 0; // Returns true if health is above 0
}

int Player::getDamage() const {
    return stats.getDamage();
}

int Player::getDefense() const {
    return stats.getDefense();
}

int Player::getSpeed() const {
    return stats.getSpeed();
}

// Setter functions
void Player::setHealth(int health) {
    stats.setHealth(health);
}

void Player::setDamage(int damage) {
    stats.setDamage(damage);
}

void Player::setDefense(int defense) {
    stats.setDefense(defense);
}

void Player::setSpeed(int speed) {
    stats.setSpeed(speed);
}

// Buff-related functions
void Player::applyBuff(const Buff& buff) {
    if (buff.getDesc().find("Health") != std::string::npos) {
        stats.increaseHealth(buff.getValue());
    } else if (buff.getDesc().find("Damage") != std::string::npos) {
        stats.increaseDamage(buff.getValue());
    } else if (buff.getDesc().find("Defense") != std::string::npos) {
        stats.increaseDefense(buff.getValue());
    }
}


void Player::increaseDamage(int amount) {
    setDamage(getDamage() + amount);
}

void Player::takeDamage(int damage) {
    stats.takeDamage(damage);
}
