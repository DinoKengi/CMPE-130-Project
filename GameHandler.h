#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "Story.h"
#include "Encounter.h"
#include "Map.h"
#include "Inventory.h"

class GameManager {
public:
    GameManager(int numRooms);
    
    void startGame();  // main function to begin the game
    void explore();    // handles exploration logic
    void manageInv(); // inventory interactions
    void encounter();  // random encounters in room

private:
    Story story;
    RandomEncounter encounterGen;
    MapExplore exploration;
    Inventory playerInventory;
};

#endif 
