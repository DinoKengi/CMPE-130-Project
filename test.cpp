#include "Player.h"
#include "Map.h"
#include "Room.h"
#include "Buff.h"
#include "Monster.h"
#include "Battle.h"
#include "Encounter.h"
#include <iostream>

int main() {
    Wizard player("Merlin");

    std::cout << "Player created: " << player.getName() << " (Class: " << player.getClassType() << ")\n";
    std::cout << "Stats - Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";

    MapExplore map(8);                    // example map with 8 rooms
    map.shuffleRoom();                    // randomize rooms and encounters

    std::cout << "\nGenerating Minimum Spanning Tree...\n";
    map.genTree();

    std::cout << "\nStarting Player Route:\n";
    map.startPlayerRoute(player);

    // Check player's final stats after traversal
    std::cout << "\nPlayer Stats After Traversal:\n";
    std::cout << "Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";

    return 0;
}
