#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

// Function declarations
void clearScreen();
void displayHeader(const Player& player, const Monster& monster);

class Battle {
public:
    static void engage(Player& player, Monster& monster);

private:
    static void playerTurn(Player& player, Monster& monster, int turnCounter);
    static void monsterTurn(Player& player, Monster& monster);
};

#endif
