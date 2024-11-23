#include "Buff.h"
#include "Player.h" 
#include <iostream>

Buff::Buff(const std::string& desc, int value)
    : desc(desc), value(value) {}

std::string Buff::getDesc() const {
    return desc;
}

int Buff::getValue() const {
    return value;
}


void Buff::applyTo(Player& player) const {
    std::cout << "Applying buff: " << desc << " with value " << value << "\n";
    if (desc.find("Health") != std::string::npos) {
        player.setHealth(player.getHealth() + value);
    } else if (desc.find("Damage") != std::string::npos) {
        player.setDamage(player.getDamage() + value);
    } else if (desc.find("Defense") != std::string::npos) {
        player.setDefense(player.getDefense() + value);
    }
}