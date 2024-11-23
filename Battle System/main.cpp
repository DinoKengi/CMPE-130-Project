#include "Player.h"
#include "Monster.h"
#include "Battle.h"
#include "Player.cpp"
#include "Monster.cpp"
#include "Battle.cpp"
#include <iostream>

int main() {
    // Create a player (choose a specific subclass, e.g., Knight)
    Knight player;

    // Create a monster (choose a specific subclass, e.g., Goblin)
    Goblin monster;

    // Start a battle
    Battle::engage(player, monster);

    // Game over
    if (player.getHealth() > 0) {
        std::cout << "Congratulations, " << player.getName() << "! You are victorious.\n";
    } else {
        std::cout << "Game Over.\n";
    }

    return 0;
}
