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

    while (player.isAlive() && monster->isAlive()) {
        // Display stats
        std::cout << "\n=====================================\n";
        std::cout << "Player's Stats:\n";
        std::cout << "Health: " << player.getHealth()
                  << ", Damage: " << player.getDamage()
                  << ", Defense: " << player.getDefense() << "\n";
        std::cout << "Monster's Stats:\n";
        std::cout << "Health: " << monster->getHealth()
                  << ", Damage: " << monster->getDamage() << "\n";
        std::cout << "=====================================\n";

        // Ask the player for their action
        std::cout << "\nYour turn! Choose an action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Block\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Player attacks the monster
            int damageToMonster = player.getDamage();
            std::cout << player.getName() << " attacks " << monster->getName()
                      << " for " << damageToMonster << " damage.\n";
            monster->takeDamage(damageToMonster);

        } else if (choice == 2) {
            // Player blocks, increasing defense temporarily
            std::cout << player.getName() << " blocks the next attack!\n";
            player.setDefense(player.getDefense() + 5);
        } else {
            std::cout << "Invalid choice! You lose your turn.\n";
        }

        // Check if the monster is still alive for its turn
        if (monster->isAlive()) {
            // Monster attacks the player
            int damageToPlayer = monster->getDamage() - player.getDefense();
            if (damageToPlayer < 0) damageToPlayer = 0; // Ensure non-negative damage

            std::cout << monster->getName() << " attacks " << player.getName()
                      << " for " << damageToPlayer << " damage.\n";
            player.takeDamage(damageToPlayer);

            // Reset the player's temporary defense boost if they blocked
            if (choice == 2) {
                player.setDefense(player.getDefense() - 5);
            }
        }

        // Check victory or defeat conditions
        if (!monster->isAlive()) {
            std::cout << "\n" << monster->getName() << " has been defeated!\n";
        } else if (!player.isAlive()) {
            std::cout << "\n" << player.getName() << " has fallen in battle...\n";
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
