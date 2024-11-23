#include "Player.h"
#include "Monster.h"
#include "Battle.h"
#include "Stats.h"
#include "Encounter.h"
#include <iostream>
#include <memory> // For smart pointers

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    // Create a player (e.g., Knight)
    Knight player;

    // Create a RandomEncounter instance
    RandomEncounter encounterGenerator;

    // Game loop: Multiple encounters
    while (player.getHealth() > 0) {
        clearScreen();

        // Generate an encounter
        std::string encounter = encounterGenerator.makeEncounter();
        std::cout << "Exploring the dungeon...\n";
        std::cout << "You encounter a " << encounter << "!\n";

        // Dynamically create the monster based on the encounter
        std::unique_ptr<Monster> monster;
        if (encounter == "Goblin") {
            monster = std::make_unique<Goblin>();
        } else if (encounter == "Slime") {
            monster = std::make_unique<Slime>();
        } else if (encounter == "Ogre") {
            monster = std::make_unique<Ogre>();
        } else if (encounter == "Bandit") {
            monster = std::make_unique<Bandit>();
        } else if (encounter == "Ghost") {
            monster = std::make_unique<Ghost>();
        }

        // Start the battle
        Battle::engage(player, *monster);

        // Check if the player survived
        if (player.getHealth() <= 0) {
            std::cout << "\nYou have fallen in battle...\n";
            break;
        }

        // Prompt to continue or exit
        std::cout << "\nDo you want to keep exploring? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    // Game over or exit
    clearScreen();
    if (player.getHealth() > 0) {
        std::cout << "Congratulations, " << player.getName()
                  << "! You survived the dungeon.\n";
    } else {
        std::cout << "Game Over. Better luck next time!\n";
    }

    return 0;
}
