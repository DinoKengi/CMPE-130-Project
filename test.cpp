#include "Monster.h"
#include "Player.h"
#include <iostream>

// Function to simulate a battle between a player and the Dragon
void simulateBattle(Player& player, Monster& monster) {
    std::cout << "\n--- Battle Start ---\n";
    monster.displayEncounterStory();

    while (player.getHealth() > 0 && monster.isAlive()) {
        // Player attacks the monster
        std::cout << player.getName() << " attacks the " << monster.getName() << "!\n";
        monster.setHealth(monster.getHealth() - player.getDamage());
        if (!monster.isAlive()) {
            std::cout << "The " << monster.getName() << " has been defeated!\n";
            break;
        }

        // Monster attacks back
        std::cout << monster.getName() << " attacks back!\n";
        monster.attack(); // Monster-specific attack message
        player.setHealth(player.getHealth() - monster.getDamage());
        if (player.getHealth() <= 0) {
            std::cout << player.getName() << " has been defeated!\n";
            break;
        }

        // Display current health
        std::cout << player.getName() << " Health: " << player.getHealth() << "\n";
        std::cout << monster.getName() << " Health: " << monster.getHealth() << "\n";
    }

    // Post-battle results
    if (player.getHealth() > 0) {
        std::cout << player.getName() << " survived the battle with " << player.getHealth() << " health remaining.\n";
    } else {
        std::cout << player.getName() << " has fallen in battle. Game over.\n";
    }
    std::cout << "--- Battle End ---\n";
}

int main() {
    // Create a player (e.g., Knight)
    Knight player("Arthur");

    // Create the Dragon (Final Boss)
    Dragon dragon;

    // Display player stats
    std::cout << "Player created: " << player.getName() << " (Class: " << player.getClassType() << ")\n";
    std::cout << "Stats - Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";

    // Test battle with the Dragon
    simulateBattle(player, dragon);

    return 0;
}
