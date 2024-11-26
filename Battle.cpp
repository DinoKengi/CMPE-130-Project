#include "Battle.h"
#include <iostream>
#include <cstdlib> // For system()

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux/Mac
#endif
}

// Function to display the health of the player and monster
void displayHeader(const Player& player, const Monster& monster) {
    std::cout << "=====================================\n";
    std::cout << "Player: " << player.getName() << " | HP: " << player.getHealth() << "\n";
    std::cout << "Monster: " << monster.getName() << " | HP: " << monster.getHealth() << "\n";
    std::cout << "=====================================\n\n";
}

// Main battle function
void Battle::engage(Player& player, Monster& monster) {
    int turnCounter = 0; // Track player turns for strong attack

    std::cout << "A wild " << monster.getName() << " appears!\n";

    while (player.getHealth() > 0 && monster.getHealth() > 0) {
        displayHeader(player, monster); // Show the current status before each turn

        bool playerGoesFirst = player.getSpeed() >= monster.getSpeed();

        if (playerGoesFirst) {
            turnCounter++;
            playerTurn(player, monster, turnCounter);
            if (monster.getHealth() <= 0) {
                std::cout << monster.getName() << " has been defeated!\n";
                break;
            }
            monsterTurn(player, monster);
        } else {
            monsterTurn(player, monster);
            if (player.getHealth() <= 0) {
                std::cout << player.getName() << " has fallen in battle.\n";
                break;
            }
            turnCounter++;
            playerTurn(player, monster, turnCounter);
        }
    }

    if (player.getHealth() > 0) {
        std::cout << "Congratulations, " << player.getName() << "! You are victorious.\n";
    } else {
        std::cout << "Game Over.\n";
    }
}

// Player's turn
void Battle::playerTurn(Player& player, Monster& monster, int turnCounter) {
    displayHeader(player, monster);

    std::cout << "\nYour turn:\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Block\n";
    if (turnCounter >= 3) {
        std::cout << "3. Strong Attack (Available!)\n";
    }
    std::cout << "Choose an action: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int damageToMonster = player.getDamage();
        std::cout << player.getName() << " attacks " << monster.getName()
                  << " for " << damageToMonster << " damage.\n";
        monster.takeDamage(damageToMonster);
    } else if (choice == 2) {
        std::cout << player.getName() << " blocks the attack, reducing incoming damage.\n";
        player.setDefense(player.getDefense() + 5); // Temporary block effect
    } else if (choice == 3 && turnCounter >= 3) {
        int strongAttackDamage = player.getDamage() * 3; // Strong attack deals double damage
        std::cout << player.getName() << " unleashes a powerful attack on " << monster.getName()
                  << " for " << strongAttackDamage << " damage!\n";
        monster.takeDamage(strongAttackDamage);
        turnCounter = 0; // Reset turn counter after strong attack
    } else {
        std::cout << "Invalid choice or strong attack not available. You lose your turn.\n";
    }

    if (choice == 2) {
        player.setDefense(player.getDefense() - 5); // Remove block effect
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

// Monster's turn
void Battle::monsterTurn(Player& player, Monster& monster) {
    displayHeader(player, monster);

    std::cout << "\n" << monster.getName() << "'s turn:\n";

    // Calculate damage dealt to the player, ensuring it is at least 0
    int damageToPlayer = std::max(0, monster.getDamage() - player.getDefense());

    // Output the monster's attack
    std::cout << monster.getName() << " attacks " << player.getName()
              << " for " << damageToPlayer << " damage.\n";

    // Apply damage to the player
    player.takeDamage(damageToPlayer);

    // Pause for user interaction
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
