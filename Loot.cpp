#include "Loot.h"

Loot::Loot(std::string name)
    : name(name) {}

std::string Loot::getName() const {
    return name;
}
