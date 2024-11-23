#include "Battle.h"
#include <iostream>

void Battle::engage(Player& player, Monster& monster) {
    std::cout << "A wild " << monster.getName() << " appears!\n";

    while (player.getHealth() > 0 && monster.getHealth() > 0) {
        // Determine turn order based on speed
        bool playerGoesFirst = player.getSpeed() >= monster.getSpeed();

        if (playerGoesFirst) {
            playerTurn(player, monster);
            if (monster.getHealth() <= 0) {
                std::cout << monster.getName() << " is defeated!\n";
                break;
            }
            monsterTurn(player, monster);
        } else {
            monsterTurn(player, monster);
            if (player.getHealth() <= 0) {
                std::cout << player.getName() << " has fallen in battle.\n";
                break;
            }
            playerTurn(player, monster);
        }
    }

    if (player.getHealth() > 0) {
        std::cout << "Congratulations, " << player.getName() << "! You are victorious.\n";
    } else {
        std::cout << "Game Over.\n";
    }
}

void Battle::playerTurn(Player& player, Monster& monster) {
    std::cout << "\nYour turn:\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Block\n";
    std::cout << "Choose an action (1/2): ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Player attacks
        int damageToMonster = player.getDamage();
        std::cout << player.getName() << " attacks " << monster.getName()
                  << " for " << damageToMonster << " damage.\n";
        monster.takeDamage(damageToMonster);
    } else if (choice == 2) {
        // Player blocks
        std::cout << player.getName() << " prepares to block.\n";
        // Blocking logic can reduce monster's damage on the next turn
    } else {
        std::cout << "Invalid choice. You lose your turn.\n";
    }
}

void Battle::monsterTurn(Player& player, Monster& monster) {
    std::cout << "\n" << monster.getName() << "'s turn:\n";
    int damageToPlayer = monster.getDamage();
    std::cout << monster.getName() << " attacks " << player.getName()
              << " for " << damageToPlayer << " damage.\n";
    player.takeDamage(damageToPlayer);
}
