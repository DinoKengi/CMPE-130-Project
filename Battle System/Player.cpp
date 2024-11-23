#include "Player.h"

Player::Player(const std::string& name, int health, int damage, int defense, int speed)
    : Stats(health, damage, defense, speed), name(name) {}

std::string Player::getName() const {
    return name;
}
