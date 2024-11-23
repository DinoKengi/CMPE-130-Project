#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

class Battle {
public:
    static void engage(Player& player, Monster& monster);

private:
    static void playerTurn(Player& player, Monster& monster); // Declare playerTurn
    static void monsterTurn(Player& player, Monster& monster); // Declare monsterTurn
};

#endif
