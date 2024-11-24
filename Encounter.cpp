#include "Encounter.h"
#include <iostream>

// MonsterEncounter Implementation
MonsterEncounter::MonsterEncounter(std::unique_ptr<Monster> monster)
    : monster(std::move(monster)) {}

void MonsterEncounter::trigger(Player& player) {
    if (!player.isAlive()) {
        std::cout << player.getName() << " is already dead and cannot fight!\n";
        return;
    }

    std::cout << "A wild " << monster->getName() << " appears!\n";

    // Simple battle loop
    while (player.isAlive() && monster->isAlive()) {
        // Player attacks monster
        monster->takeDamage(player.getDamage());
        std::cout << player.getName() << " attacks " << monster->getName()
                  << " for " << player.getDamage() << " damage.\n";

        if (!monster->isAlive()) {
            std::cout << monster->getName() << " has been defeated!\n";
            break;
        }

        // Monster attacks player
        player.takeDamage(monster->getDamage());
        std::cout << monster->getName() << " attacks " << player.getName()
                  << " for " << monster->getDamage() << " damage.\n";

        if (!player.isAlive()) {
            std::cout << player.getName() << " has fallen in battle...\n";
            break;
        }
    }
}


// BuffEncounter Implementation
BuffEncounter::BuffEncounter(const Buff& buff)
    : buff(buff) {}

void BuffEncounter::trigger(Player& player) {
    if (!player.isAlive()) {
        std::cout << player.getName() << " is dead and cannot receive buffs.\n";
        return;
    }

    std::cout << "You found a buff: " << buff.getDesc() << "!\n";
    buff.applyTo(player);
    std::cout << "Player's new stats - Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";
}