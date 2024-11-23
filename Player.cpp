#include "Player.h"

// Constructor
Player::Player(const std::string& name, int health, int damage, int defense)
    : name(name), stats(health, damage, defense) {}

// Getter functions
std::string Player::getName() const {
    return name;
}

int Player::getHealth() const {
    return stats.getHealth();
}

int Player::getDamage() const {
    return stats.getDamage();
}

int Player::getDefense() const {
    return stats.getDefense();
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
