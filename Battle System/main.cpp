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

// Function to allow the player to choose a class
std::unique_ptr<Player> choosePlayerClass() {
    int choice;
    do {
        std::cout << "Choose your class:\n";
        std::cout << "1. Knight - High health and defense.\n";
        std::cout << "2. Wizard - High damage but low health.\n";
        std::cout << "3. Archer - High speed and critical hits.\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                return std::make_unique<Knight>();
            case 2:
                return std::make_unique<Wizard>();
            case 3:
                return std::make_unique<Archer>();
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

int main() {
    // Let the player choose their class
    std::unique_ptr<Player> player = choosePlayerClass();

    // Create a RandomEncounter instance
    RandomEncounter encounterGenerator;

    // Game loop: Multiple encounters
    while (player->getHealth() > 0) {
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
        Battle::engage(*player, *monster);

        // Check if the player survived
        if (player->getHealth() <= 0) {
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
    if (player->getHealth() > 0) {
        std::cout << "Congratulations, " << player->getName()
                  << "! You survived the dungeon.\n";
    } else {
        std::cout << "Game Over. Better luck next time!\n";
    }

    return 0;
}
